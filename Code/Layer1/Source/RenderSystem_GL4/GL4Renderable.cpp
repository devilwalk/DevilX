#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CRenderable::CRenderable(IRenderableImp * interfaceImp,CRenderableObject * obj)
	:TInterfaceObject<IRenderableImp>(interfaceImp)
	,mRenderableObject(obj)
	,mGeometry(nullptr)
	,mMaterial(nullptr)
	,mPrimitiveTopology(GL_TRIANGLES)
{
	mMaterial=DEVILX_NEW CMaterial(this);
	_updatePrimitiveTopology();
	getInterfaceImp()->setUserPointer(0,this);
	getInterfaceImp()->addListener(static_cast<TInterfaceObject<IRenderableImp>*>(this),IRenderableImp::EMessage_EndGeometryChange);
	static_cast<IGeometryUsageImp*>(getInterfaceImp()->queryInterface_IGeometryUsage())->addListener(static_cast<TMessageReceiver<IGeometryUsageImp>*>(this),IGeometryUsageImp::EMessage_EndOperationTypeChange);
}

NSDevilX::NSRenderSystem::NSGL4::CRenderable::~CRenderable()
{
	DEVILX_DELETE(mMaterial);
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderable::renderForward(CLight * light,CRenderOperation & operation)
{
	if(getObject()->getScene()->getConstantBufferMT())
		operation.mConstantBuffers.push_back(getObject()->getScene()->getConstantBufferMT());
	if(getObject()->getTransformer()->getConstantBufferMT())
		operation.mConstantBuffers.push_back(getObject()->getTransformer()->getConstantBufferMT());
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

Void NSDevilX::NSRenderSystem::NSGL4::CRenderable::onMessage(IRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IRenderableImp::EMessage_EndGeometryChange:
		mGeometry=CSystemImp::getSingleton().getGeometry(static_cast<IGeometryImp*>(getInterfaceImp()->getGeometry()));
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderable::onMessage(IGeometryUsageImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IGeometryUsageImp::EMessage_EndOperationTypeChange:
		_updatePrimitiveTopology();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderable::_updatePrimitiveTopology()
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
