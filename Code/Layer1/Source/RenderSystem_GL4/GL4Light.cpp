#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CLight::CLight(ILightImp * interfaceImp)
	:TInterfaceObject<ILightImp>(interfaceImp)
	,CConstantBufferContainer((interfaceImp->getType()==IEnum::ELightType_Directional)?"cbDirectionLight":((interfaceImp->getType()==IEnum::ELightType_Point)?"cbPointLight":"cbSpotLight"))
	,mScene(CSystemImp::getSingleton().getScene(static_cast<ISceneElementImp*>(interfaceImp->queryInterface_ISceneElement())->getScene()))
{
	getInterfaceImp()->setUserPointer(0,this);
}

NSDevilX::NSRenderSystem::NSGL4::CLight::~CLight()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CLight::onMessage(ILightImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
}

Void NSDevilX::NSRenderSystem::NSGL4::CLight::_updateConstantBuffer(Byte * buffer)
{
	switch(getInterfaceImp()->getType())
	{
	case IEnum::ELightType_Directional:
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightDiffuseColour").mOffsetInBytes;
		memcpy(&buffer[offset],&getInterfaceImp()->getColour(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightSpecularColour").mOffsetInBytes;
		memcpy(&buffer[offset],&CFloat3::sOne,sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightDirection").mOffsetInBytes;
		memcpy(&buffer[offset],&static_cast<IDirectionLightPropertyImp*>(getInterfaceImp()->queryInterface_IDirectionLightProperty())->getDirectionMT(),sizeof(CFloat3));
	}
	break;
	case IEnum::ELightType_Point:
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightDiffuseColour").mOffsetInBytes;
		memcpy(&buffer[offset],&getInterfaceImp()->getColour(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightSpecularColour").mOffsetInBytes;
		memcpy(&buffer[offset],&CFloat3::sOne,sizeof(CFloat3));
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
		memcpy(&buffer[offset],&getInterfaceImp()->getColour(),sizeof(CFloat3));
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightSpecularColour").mOffsetInBytes;
		memcpy(&buffer[offset],&CFloat3::sOne,sizeof(CFloat3));
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
