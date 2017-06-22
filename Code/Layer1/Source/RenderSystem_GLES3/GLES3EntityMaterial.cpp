#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CEntityMaterial::CEntityMaterial(CEntityRenderableImp * renderable)
	:CConstantBufferContainer("cbObjectMaterial")
	,mRenderable(renderable)
{
	mTechniques[CEnum::ETechniqueType_Forward]=DEVILX_NEW CEntityForwardTechnique(this);
	getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndAlphaTestValueChange);
	getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndColourUnitStateCreate);
	getRenderable()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityRenderableImp>*>(this),IEntityRenderableImp::EMessage_EndGeometryChange);
}

NSDevilX::NSRenderSystem::NSGLES3::CEntityMaterial::~CEntityMaterial()
{
	for(auto technique:mTechniques)
		DEVILX_DELETE(technique);
}

Void NSDevilX::NSRenderSystem::NSGLES3::CEntityMaterial::onMessage(IEntityRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IEntityRenderableImp::EMessage_EndAlphaTestValueChange:
		needUpdate();
		break;
	case IEntityRenderableImp::EMessage_EndColourUnitStateCreate:
		static_cast<IColourUnitStateImp*>(data)->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CEntityMaterial::onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IColourUnitStateImp::EMessage_EndValueChange:
		needUpdate();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CEntityMaterial::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gMainColour").mOffsetInBytes;
	if(static_cast<const IEntityRenderableImp*>(getRenderable()->getInterfaceImp())->getColourUnitState(IEnum::EEntityColourUnitStateType_Diffuse))
	{
		memcpy(&buffer[offset],&getRenderable()->getInterfaceImp()->getColourUnitState(IEnum::EEntityColourUnitStateType_Diffuse)->getValue(),sizeof(CFloat3));
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gAlpha").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=1.0f;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gSpecularColour").mOffsetInBytes;
	if(static_cast<const IEntityRenderableImp*>(getRenderable()->getInterfaceImp())->getColourUnitState(IEnum::EEntityColourUnitStateType_Specular))
	{
		memcpy(&buffer[offset],&getRenderable()->getInterfaceImp()->getColourUnitState(IEnum::EEntityColourUnitStateType_Specular)->getValue(),sizeof(CFloat3));
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gSpecularPower").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=10.0f;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gEmissiveColour").mOffsetInBytes;
	if(static_cast<const IEntityRenderableImp*>(getRenderable()->getInterfaceImp())->getColourUnitState(IEnum::EEntityColourUnitStateType_Emissive))
	{
		memcpy(&buffer[offset],&getRenderable()->getInterfaceImp()->getColourUnitState(IEnum::EEntityColourUnitStateType_Emissive)->getValue(),sizeof(CFloat3));
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gAlphaTestValue").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=getRenderable()->getInterfaceImp()->getAlphaTestValue();
}
