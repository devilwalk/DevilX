#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CMaterial::CMaterial(CRenderable * renderable)
	:TInterfaceObject<IMaterialImp>(static_cast<IMaterialImp*>(renderable->getInterfaceImp()->queryInterface_IMaterial()))
	,CConstantBufferContainer("cbObjectMaterial")
	,mRenderable(renderable)
{
	mTechniques[CEnum::ETechniqueType_Forward]=DEVILX_NEW CForwardTechnique(this);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndAlphaTestValueChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IMaterialImp>*>(this),IMaterialImp::EMessage_EndColourUnitStateCreate);
	getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IRenderableImp>*>(this),IRenderableImp::EMessage_EndGeometryChange);
}

NSDevilX::NSRenderSystem::NSGL4::CMaterial::~CMaterial()
{
	for(auto technique:mTechniques)
		DEVILX_DELETE(technique);
}

Void NSDevilX::NSRenderSystem::NSGL4::CMaterial::onMessage(IMaterialImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IMaterialImp::EMessage_EndAlphaTestValueChange:
		needUpdate();
		break;
	case IMaterialImp::EMessage_EndColourUnitStateCreate:
		static_cast<IColourUnitStateImp*>(data)->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CMaterial::onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IColourUnitStateImp::EMessage_EndValueChange:
		needUpdate();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CMaterial::onMessage(IRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IRenderableImp::EMessage_EndGeometryChange:
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CMaterial::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gMainColour").mOffsetInBytes;
	if(static_cast<const IMaterialImp*>(getInterfaceImp())->getColourUnitState(IEnum::EColourUnitStateType_Diffuse))
	{
		memcpy(&buffer[offset],&getInterfaceImp()->getColourUnitState(IEnum::EColourUnitStateType_Diffuse)->getValue(),sizeof(CFloat3));
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gAlpha").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=1.0f;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gSpecularColour").mOffsetInBytes;
	if(static_cast<const IMaterialImp*>(getInterfaceImp())->getColourUnitState(IEnum::EColourUnitStateType_Specular))
	{
		memcpy(&buffer[offset],&getInterfaceImp()->getColourUnitState(IEnum::EColourUnitStateType_Specular)->getValue(),sizeof(CFloat3));
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gSpecularPower").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=10.0f;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gEmissiveColour").mOffsetInBytes;
	if(static_cast<const IMaterialImp*>(getInterfaceImp())->getColourUnitState(IEnum::EColourUnitStateType_Emissive))
	{
		memcpy(&buffer[offset],&getInterfaceImp()->getColourUnitState(IEnum::EColourUnitStateType_Emissive)->getValue(),sizeof(CFloat3));
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gAlphaTestValue").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=getInterfaceImp()->getAlphaTestValue();
}
