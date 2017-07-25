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
	,mQueryBuffer(nullptr)
{
	mMaterial=DEVILX_NEW CEntityMaterial(this);
	_updatePrimitiveTopology();
	getInterfaceImp()->setUserPointer(0,this);
	getInterfaceImp()->addListener(static_cast<TInterfaceObject<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndGeometryChange);
	getInterfaceImp()->addListener(static_cast<TInterfaceObject<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndQueryBufferChange);
	static_cast<IGeometryUsageImp*>(getInterfaceImp()->queryInterface_IGeometryUsage())->addListener(static_cast<TMessageReceiver<IGeometryUsageImp>*>(this),IGeometryUsageImp::EMessage_EndOperationTypeChange);
}

NSDevilX::NSRenderSystem::NSD3D11::CSubEntityImp::~CSubEntityImp()
{
	if(mQueryBuffer)
		mQueryBuffer->release();
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
	operation.mVertexBuffers.resize(operation.mPass->getVertexShader()->getInputElementDescs().size());
	operation.mVertexStrides.resize(operation.mPass->getVertexShader()->getInputElementDescs().size());
	for(decltype(operation.mPass->getVertexShader()->getInputElementDescs().size()) i=0;i<operation.mPass->getVertexShader()->getInputElementDescs().size();++i)
	{
		operation.mVertexBuffers[i]=mGeometry->getVertexBuffer()->getBuffers()[operation.mPass->getVertexShader()->getInputSlots()[i]]->getInternal();
		operation.mVertexStrides[i]=CUtility::getStride((CEnum::EVertexBufferType)operation.mPass->getVertexShader()->getInputSlots()[i]);
	}
	operation.mIndexBuffer=mGeometry->getIndexBuffer()->getBuffer();
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
	operation.mVertexBuffers.resize(operation.mPass->getVertexShader()->getInputElementDescs().size());
	operation.mVertexStrides.resize(operation.mPass->getVertexShader()->getInputElementDescs().size());
	for(decltype(operation.mPass->getVertexShader()->getInputElementDescs().size()) i=0;i<operation.mPass->getVertexShader()->getInputElementDescs().size();++i)
	{
		if(CEnum::EVertexBufferType_Query==operation.mPass->getVertexShader()->getInputSlots()[i])
		{
			operation.mVertexBuffers[i]=mQueryBuffer->getInternal();
			operation.mVertexStrides[i]=sizeof(UInt32);
		}
		else
		{
			operation.mVertexBuffers[i]=mGeometry->getVertexBuffer()->getBuffers()[operation.mPass->getVertexShader()->getInputSlots()[i]]->getInternal();
			operation.mVertexStrides[i]=CUtility::getStride((CEnum::EVertexBufferType)operation.mPass->getVertexShader()->getInputSlots()[i]);
		}
	}
	operation.mIndexBuffer=mGeometry->getIndexBuffer()->getBuffer();
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
	case ISubEntityImp::EMessage_EndQueryBufferChange:
		if(getInterfaceImp()->getQueryBuffer())
		{
			mQueryBuffer=CSystemImp::getSingleton().getBuffer(static_cast<IBufferImp*>(getInterfaceImp()->getQueryBuffer()));
			mQueryBuffer->addRef();
		}
		else
		{
			if(mQueryBuffer)
			{
				mQueryBuffer->release();
				mQueryBuffer=nullptr;
			}
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