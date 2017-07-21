#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CSubEntityImp::CSubEntityImp(ISubEntityImp * interfaceImp,CEntityImp * obj)
	:TInterfaceObject<ISubEntityImp>(interfaceImp)
	,mEntity(obj)
	,mGeometry(nullptr)
	,mMaterial(nullptr)
	,mPrimitiveTopology(GL_TRIANGLES)
{
	mMaterial=DEVILX_NEW CEntityMaterial(this);
	_updatePrimitiveTopology();
	getInterfaceImp()->setUserPointer(0,this);
	getInterfaceImp()->addListener(static_cast<TInterfaceObject<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndGeometryChange);
	static_cast<IGeometryUsageImp*>(getInterfaceImp()->queryInterface_IGeometryUsage())->addListener(static_cast<TMessageReceiver<IGeometryUsageImp>*>(this),IGeometryUsageImp::EMessage_EndOperationTypeChange);
}

NSDevilX::NSRenderSystem::NSGLES3::CSubEntityImp::~CSubEntityImp()
{
	DEVILX_DELETE(mMaterial);
}

Void NSDevilX::NSRenderSystem::NSGLES3::CSubEntityImp::renderForward(CLight * light,CRenderOperation & operation)
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
	operation.mVertexArrayObject=static_cast<CEntityPass*>(operation.mPass)->getVertexArrayObject();
	operation.mIndexCount=getInterfaceImp()->queryInterface_IGeometryUsage()->getIndexCount();
	operation.mIndexBufferOffset=getInterfaceImp()->queryInterface_IGeometryUsage()->getIndexBufferOffset();
	operation.mPrimitiveTopology=mPrimitiveTopology;
	operation.mVertexCount=getInterfaceImp()->queryInterface_IGeometryUsage()->getVertexCount();
	operation.mVertexBufferOffset=getInterfaceImp()->queryInterface_IGeometryUsage()->getVertexBufferOffset();
}

Void NSDevilX::NSRenderSystem::NSGLES3::CSubEntityImp::onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISubEntityImp::EMessage_EndGeometryChange:
		mGeometry=CSystemImp::getSingleton().getGeometry(static_cast<IGeometryImp*>(getInterfaceImp()->getGeometry()));
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CSubEntityImp::onMessage(IGeometryUsageImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IGeometryUsageImp::EMessage_EndOperationTypeChange:
		_updatePrimitiveTopology();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CSubEntityImp::_updatePrimitiveTopology()
{
	switch(getInterfaceImp()->queryInterface_IGeometryUsage()->getOperationType())
	{
	case IEnum::EOperationType_TriangleList:
		mPrimitiveTopology=GL_TRIANGLES;
		break;
	case IEnum::EOperationType_TriangleStrip:
		mPrimitiveTopology=GL_TRIANGLE_STRIP;
		break;
	}
}
