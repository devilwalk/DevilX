#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CEntityMaterial::CEntityMaterial(CSubEntityImp * subEntity)
	:CConstantBufferContainer("cbObjectMaterial")
	,mSubEntity(subEntity)
{
	mTechniques[CEnum::ETechniqueType_Forward]=DEVILX_NEW CEntityForwardTechnique(this);
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndAlphaTestValueChange);
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndColourUnitStateCreate);
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndGeometryChange);
}

NSDevilX::NSRenderSystem::NSGL4::CEntityMaterial::~CEntityMaterial()
{
	for(auto technique:mTechniques)
		DEVILX_DELETE(technique);
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityMaterial::onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISubEntityImp::EMessage_EndAlphaTestValueChange:
		needUpdate();
		break;
	case ISubEntityImp::EMessage_EndColourUnitStateCreate:
		static_cast<IColourUnitStateImp*>(data)->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityMaterial::onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IColourUnitStateImp::EMessage_EndValueChange:
		needUpdate();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CEntityMaterial::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gMainColour").mOffsetInBytes;
	if(static_cast<const ISubEntityImp*>(getSubEntity()->getInterfaceImp())->getColourUnitState(IEnum::EEntityColourUnitStateType_Diffuse))
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=getSubEntity()->getInterfaceImp()->getColourUnitState(IEnum::EEntityColourUnitStateType_Diffuse)->getValue().rgb();
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gAlpha").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=1.0f;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gSpecularColour").mOffsetInBytes;
	if(static_cast<const ISubEntityImp*>(getSubEntity()->getInterfaceImp())->getColourUnitState(IEnum::EEntityColourUnitStateType_Specular))
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=getSubEntity()->getInterfaceImp()->getColourUnitState(IEnum::EEntityColourUnitStateType_Specular)->getValue().rgb();
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gSpecularPower").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=10.0f;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gEmissiveColour").mOffsetInBytes;
	if(static_cast<const ISubEntityImp*>(getSubEntity()->getInterfaceImp())->getColourUnitState(IEnum::EEntityColourUnitStateType_Emissive))
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=getSubEntity()->getInterfaceImp()->getColourUnitState(IEnum::EEntityColourUnitStateType_Emissive)->getValue().rgb();
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gAlphaTestValue").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=getSubEntity()->getInterfaceImp()->getAlphaTestValue();
}
