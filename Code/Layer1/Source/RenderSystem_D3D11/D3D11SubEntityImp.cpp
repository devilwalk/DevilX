#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CSubEntityImp::CSubEntityImp(ISubEntityImp * interfaceImp,CEntityImp * obj)
	:TInterfaceObject<ISubEntityImp>(interfaceImp)
	,mEntity(obj)
	,mGeometry(nullptr)
	,mMaterial(nullptr)
	,mPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	,mQueryDataBuffer(nullptr)
{
	mMaterial=DEVILX_NEW CEntityMaterial(this);
	_updatePrimitiveTopology();
	getInterfaceImp()->setUserPointer(0,this);
	getInterfaceImp()->addListener(static_cast<TInterfaceObject<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndGeometryChange);
	getInterfaceImp()->addListener(static_cast<TInterfaceObject<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndQueriableChange);
	static_cast<IGeometryUsageImp*>(getInterfaceImp()->queryInterface_IGeometryUsage())->addListener(static_cast<TMessageReceiver<IGeometryUsageImp>*>(this),IGeometryUsageImp::EMessage_EndOperationTypeChange);
}

NSDevilX::NSRenderSystem::NSD3D11::CSubEntityImp::~CSubEntityImp()
{
	DEVILX_DELETE(mQueryDataBuffer);
	DEVILX_DELETE(mMaterial);
}

CEntityImp * NSDevilX::NSRenderSystem::NSD3D11::CSubEntityImp::getEntity() const
{
	return mEntity;
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSubEntityImp::renderForward(CLight * light,CRenderOperation & operation)
{
	if(getEntity()->getScene()->getConstantBufferMT())
		operation.mConstantBuffers.push_back(getEntity()->getScene()->getConstantBufferMT());
	if(getEntity()->getTransformer()->getConstantBufferMT())
		operation.mConstantBuffers.push_back(getEntity()->getTransformer()->getConstantBufferMT());
	if(mMaterial->getConstantBufferMT())
		operation.mConstantBuffers.push_back(mMaterial->getConstantBufferMT());
	if(light)
	{
		switch(light->getInterfaceImp()->getType())
		{
		case IEnum::ELightType_Directional:
			operation.mPass=mMaterial->getTechnique(CEnum::ETechniqueType_Forward)->getPasses()[CEnum::EForwardPassType_DirectionLight];
			break;
		case IEnum::ELightType_Point:
			operation.mPass=mMaterial->getTechnique(CEnum::ETechniqueType_Forward)->getPasses()[CEnum::EForwardPassType_PointLight];
			break;
		case IEnum::ELightType_Spot:
			operation.mPass=mMaterial->getTechnique(CEnum::ETechniqueType_Forward)->getPasses()[CEnum::EForwardPassType_SpotLight];
			break;
		default:
			assert(0);
		}
	}
	else
	{
		operation.mPass=mMaterial->getTechnique(CEnum::ETechniqueType_Forward)->getPasses()[CEnum::EForwardPassType_Ambient];
	}
	operation.mGeometry=mGeometry;
	operation.mIndexCount=getInterfaceImp()->queryInterface_IGeometryUsage()->getIndexCount();
	operation.mIndexBufferOffset=getInterfaceImp()->queryInterface_IGeometryUsage()->getIndexBufferOffset();
	operation.mPrimitiveTopology=mPrimitiveTopology;
	operation.mVertexCount=getInterfaceImp()->queryInterface_IGeometryUsage()->getVertexCount();
	operation.mVertexBufferOffset=getInterfaceImp()->queryInterface_IGeometryUsage()->getVertexBufferOffset();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSubEntityImp::query(CRenderOperation & operation)
{
	if(getEntity()->getScene()->getConstantBufferMT())
		operation.mConstantBuffers.push_back(getEntity()->getScene()->getConstantBufferMT());
	if(getEntity()->getTransformer()->getConstantBufferMT())
		operation.mConstantBuffers.push_back(getEntity()->getTransformer()->getConstantBufferMT());
	if(mMaterial->getConstantBufferMT())
		operation.mConstantBuffers.push_back(mMaterial->getConstantBufferMT());
	operation.mPass=mMaterial->getTechnique(CEnum::ETechniqueType_Query)->getPasses()[0];
	operation.mGeometry=mGeometry;
	operation.mIndexCount=getInterfaceImp()->queryInterface_IGeometryUsage()->getIndexCount();
	operation.mIndexBufferOffset=getInterfaceImp()->queryInterface_IGeometryUsage()->getIndexBufferOffset();
	operation.mPrimitiveTopology=mPrimitiveTopology;
	operation.mVertexCount=getInterfaceImp()->queryInterface_IGeometryUsage()->getVertexCount();
	operation.mVertexBufferOffset=getInterfaceImp()->queryInterface_IGeometryUsage()->getVertexBufferOffset();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSubEntityImp::onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISubEntityImp::EMessage_EndGeometryChange:
		mGeometry=CSystemImp::getSingleton().getGeometry(static_cast<IGeometryImp*>(getInterfaceImp()->getGeometry()));
		break;
	case ISubEntityImp::EMessage_EndQueriableChange:
		if(getInterfaceImp()->isQueriable())
		{
			mQueryDataBuffer=DEVILX_NEW CBufferUpdater(sizeof(UInt32));
			mQueryDataBuffer->setDataSource(reinterpret_cast<const ConstVoidPtr*>(&getInterfaceImp()->getQueryDatasRef()));
			mQueryDataBuffer->setDirtyRanges(&getInterfaceImp()->getQueryDatasDirties());
			CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
		}
		else
		{
			DEVILX_DELETE(mQueryDataBuffer);
			mQueryDataBuffer=nullptr;
			CSystemImp::getSingleton().removeListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
		}
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSubEntityImp::onMessage(IGeometryUsageImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IGeometryUsageImp::EMessage_EndOperationTypeChange:
		_updatePrimitiveTopology();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSubEntityImp::_updatePrimitiveTopology()
{
	switch(getInterfaceImp()->queryInterface_IGeometryUsage()->getOperationType())
	{
	case IEnum::EOperationType_TriangleList:
		mPrimitiveTopology=D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	case IEnum::EOperationType_TriangleStrip:
		mPrimitiveTopology=D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSubEntityImp::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		if((!mQueryDataBuffer->get())&&getInterfaceImp()->getQueryDatas())
		{
			CComPtr<ID3D11Buffer> buf;
			D3D11_BUFFER_DESC desc;
			desc.BindFlags=D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags=0;
			desc.MiscFlags=0;
			desc.StructureByteStride=sizeof(UInt32);
			desc.ByteWidth=getInterfaceImp()->getGeometry()->getVertexBuffer()->getCount()*desc.StructureByteStride;
			desc.Usage=D3D11_USAGE_DEFAULT;
			CSystemImp::getSingleton().getDevice()->CreateBuffer(&desc,nullptr,&buf);
			mQueryDataBuffer->setBuffer(buf);
		}
		mQueryDataBuffer->update();
		break;
	}
}
