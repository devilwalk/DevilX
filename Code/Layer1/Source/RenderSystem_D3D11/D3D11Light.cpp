#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CLight::CLight(ILightImp * interfaceImp)
	:TInterfaceObject<ILightImp>(interfaceImp)
	,CConstantBufferContainer((interfaceImp->getType()==IEnum::ELightType_Directional)?"cbDirectionLight":((interfaceImp->getType()==IEnum::ELightType_Point)?"cbPointLight":"cbSpotLight"))
	,mScene(CSystemImp::getSingleton().getScene(static_cast<ISceneElementImp*>(interfaceImp->queryInterface_ISceneElement())->getScene()))
{
	getInterfaceImp()->setUserPointer(0,this);
}

NSDevilX::NSRenderSystem::NSD3D11::CLight::~CLight()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CLight::onMessage(ILightImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CLight::_updateConstantBuffer(Byte * buffer)
{
	switch(getInterfaceImp()->getType())
	{
	case IEnum::ELightType_Directional:
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightDiffuseColour").StartOffset;
		memcpy(&buffer[offset],&getInterfaceImp()->getColour(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightSpecularColour").StartOffset;
		memcpy(&buffer[offset],&CFloat3::sOne,sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightDirection").StartOffset;
		memcpy(&buffer[offset],&static_cast<IDirectionLightPropertyImp*>(getInterfaceImp()->queryInterface_IDirectionLightProperty())->getDirectionMT(),sizeof(CFloat3));
	}
	break;
	case IEnum::ELightType_Point:
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightDiffuseColour").StartOffset;
		memcpy(&buffer[offset],&getInterfaceImp()->getColour(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightSpecularColour").StartOffset;
		memcpy(&buffer[offset],&CFloat3::sOne,sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightPosition").StartOffset;
		memcpy(&buffer[offset],&getInterfaceImp()->queryInterface_ISceneElement()->getTransformer()->getPosition(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightReciprocalRange").StartOffset;
		*reinterpret_cast<Float*>(&buffer[offset])=1.0f/getInterfaceImp()->queryInterface_IPointLightProperty()->getRange();
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightStartFallOffDistance").StartOffset;
		*reinterpret_cast<Float*>(&buffer[offset])=0.0f;
	}
	break;
	case IEnum::ELightType_Spot:
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightDiffuseColour").StartOffset;
		memcpy(&buffer[offset],&getInterfaceImp()->getColour(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightSpecularColour").StartOffset;
		memcpy(&buffer[offset],&CFloat3::sOne,sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightPosition").StartOffset;
		memcpy(&buffer[offset],&getInterfaceImp()->queryInterface_ISceneElement()->getTransformer()->getPosition(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightDirection").StartOffset;
		memcpy(&buffer[offset],&static_cast<ISpotLightPropertyImp*>(getInterfaceImp()->queryInterface_ISpotLightProperty())->getDirectionMT(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightReciprocalRange").StartOffset;
		*reinterpret_cast<Float*>(&buffer[offset])=1.0f/getInterfaceImp()->queryInterface_ISpotLightProperty()->getRange();
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightStartFallOffDistance").StartOffset;
		*reinterpret_cast<Float*>(&buffer[offset])=0.0f;
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightCosInnerCornerHalfAngle").StartOffset;
		*reinterpret_cast<Float*>(&buffer[offset])=1.0f;
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightReciprocalDeltaCosHalfAngle").StartOffset;
		*reinterpret_cast<Float*>(&buffer[offset])=1.0f/(1.0f-cos(getInterfaceImp()->queryInterface_ISpotLightProperty()->getAngle().valueRadian()*0.5f));
	}
	break;
	}
}
