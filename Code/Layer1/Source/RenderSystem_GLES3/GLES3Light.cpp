#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CLight::CLight(ILightImp * interfaceImp)
	:TInterfaceObject<ILightImp>(interfaceImp)
	,CConstantBufferContainer((interfaceImp->getType()==IEnum::ELightType_Directional)?"cbDirectionLight":((interfaceImp->getType()==IEnum::ELightType_Point)?"cbPointLight":"cbSpotLight"))
	,mScene(CSystemImp::getSingleton().getScene(static_cast<ISceneImp*>(static_cast<ISceneElementImp*>(interfaceImp->queryInterface_ISceneElement())->getScene())))
{
	getInterfaceImp()->setUserPointer(0,this);
}

NSDevilX::NSRenderSystem::NSGLES3::CLight::~CLight()
{}

Void NSDevilX::NSRenderSystem::NSGLES3::CLight::onMessage(ILightImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
}

Void NSDevilX::NSRenderSystem::NSGLES3::CLight::_updateConstantBuffer(Byte * buffer)
{
	switch(getInterfaceImp()->getType())
	{
	case IEnum::ELightType_Directional:
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightDiffuseColour").mOffsetInBytes;
		if(const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Diffuse)
			&&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Diffuse)->getEnable()
			)
			memcpy(&buffer[offset],&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Diffuse)->getValue(),sizeof(CFloatRGB));
		else
			memcpy(&buffer[offset],&CFloatRGB::sBlack,sizeof(CFloatRGB));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightSpecularColour").mOffsetInBytes;
		if(const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Specular)
			&&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Specular)->getEnable()
			)
			memcpy(&buffer[offset],&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Specular)->getValue(),sizeof(CFloatRGB));
		else
			memcpy(&buffer[offset],&CFloatRGB::sBlack,sizeof(CFloatRGB));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightDirection").mOffsetInBytes;
		memcpy(&buffer[offset],&static_cast<IDirectionLightPropertyImp*>(getInterfaceImp()->queryInterface_IDirectionLightProperty())->getDirectionMT(),sizeof(CFloat3));
	}
	break;
	case IEnum::ELightType_Point:
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightDiffuseColour").mOffsetInBytes;
		if(const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Diffuse)
			&&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Diffuse)->getEnable()
			)
			memcpy(&buffer[offset],&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Diffuse)->getValue(),sizeof(CFloatRGB));
		else
			memcpy(&buffer[offset],&CFloatRGB::sBlack,sizeof(CFloatRGB));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightSpecularColour").mOffsetInBytes;
		if(const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Specular)
			&&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Specular)->getEnable()
			)
			memcpy(&buffer[offset],&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Specular)->getValue(),sizeof(CFloatRGB));
		else
			memcpy(&buffer[offset],&CFloatRGB::sBlack,sizeof(CFloatRGB));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightPosition").mOffsetInBytes;
		memcpy(&buffer[offset],&getInterfaceImp()->queryInterface_ISceneElement()->getTransformer()->getPosition(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightReciprocalRange").mOffsetInBytes;
		*reinterpret_cast<Float*>(&buffer[offset])=1.0f/getInterfaceImp()->queryInterface_IPointLightProperty()->getRange();
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightStartFallOffDistance").mOffsetInBytes;
		*reinterpret_cast<Float*>(&buffer[offset])=0.0f;
	}
	break;
	case IEnum::ELightType_Spot:
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightDiffuseColour").mOffsetInBytes;
		if(const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Diffuse)
			&&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Diffuse)->getEnable()
			)
			memcpy(&buffer[offset],&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Diffuse)->getValue(),sizeof(CFloatRGB));
		else
			memcpy(&buffer[offset],&CFloatRGB::sBlack,sizeof(CFloatRGB));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightSpecularColour").mOffsetInBytes;
		if(const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Specular)
			&&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Specular)->getEnable()
			)
			memcpy(&buffer[offset],&const_cast<const ILightImp*>(getInterfaceImp())->getColourUnitState(IEnum::ELightColourUnitStateType_Specular)->getValue(),sizeof(CFloatRGB));
		else
			memcpy(&buffer[offset],&CFloatRGB::sBlack,sizeof(CFloatRGB));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightPosition").mOffsetInBytes;
		memcpy(&buffer[offset],&getInterfaceImp()->queryInterface_ISceneElement()->getTransformer()->getPosition(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightDirection").mOffsetInBytes;
		memcpy(&buffer[offset],&static_cast<ISpotLightPropertyImp*>(getInterfaceImp()->queryInterface_ISpotLightProperty())->getDirectionMT(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightReciprocalRange").mOffsetInBytes;
		*reinterpret_cast<Float*>(&buffer[offset])=1.0f/getInterfaceImp()->queryInterface_ISpotLightProperty()->getRange();
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightStartFallOffDistance").mOffsetInBytes;
		*reinterpret_cast<Float*>(&buffer[offset])=0.0f;
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightCosInnerCornerHalfAngle").mOffsetInBytes;
		*reinterpret_cast<Float*>(&buffer[offset])=1.0f;
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightReciprocalDeltaCosHalfAngle").mOffsetInBytes;
		*reinterpret_cast<Float*>(&buffer[offset])=1.0f/(1.0f-cos(getInterfaceImp()->queryInterface_ISpotLightProperty()->getAngle().valueRadian()*0.5f));
	}
	break;
	}
}
