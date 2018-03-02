#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CLight::CLight(ILightImp * interfaceImp)
	:TInterfaceObject<ILightImp>(interfaceImp)
	,CConstantBufferContainer((interfaceImp->getType()==IEnum::ELightType_Directional)?"cbDirectionLight":((interfaceImp->getType()==IEnum::ELightType_Point)?"cbPointLight":"cbSpotLight"))
	,mScene(CSystemImp::getSingleton().getScene(static_cast<ISceneImp*>(static_cast<ISceneElementImp*>(interfaceImp->queryInterface_ISceneElement())->getScene())))
{
	getInterfaceImp()->setUserPointer(0,this);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ILightImp>*>(this),ILightImp::EMessage_EndDiffuseCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ILightImp>*>(this),ILightImp::EMessage_EndSpecularCreate);
}

NSDevilX::NSRenderSystem::NSD3D11::CLight::~CLight()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CLight::onMessage(ILightImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ILightImp::EMessage_EndDiffuseCreate:
		getInterfaceImp()->getDiffuse()->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
		getInterfaceImp()->getDiffuse()->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndEnableChange);
		break;
	case ILightImp::EMessage_EndSpecularCreate:
		getInterfaceImp()->getSpecular()->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
		getInterfaceImp()->getSpecular()->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndEnableChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CLight::onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IColourUnitStateImp::EMessage_EndValueChange:
	case IColourUnitStateImp::EMessage_EndEnableChange:
		needUpdate();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CLight::_updateConstantBuffer(Byte * buffer)
{
	switch(getInterfaceImp()->getType())
	{
	case IEnum::ELightType_Directional:
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightDiffuseColour").StartOffset;
		if(getInterfaceImp()->getDiffuse()&&getInterfaceImp()->getDiffuse()->getEnable())
			*reinterpret_cast<CFloat3*>(&buffer[offset])=static_cast<CFloatRGB>(getInterfaceImp()->getDiffuse()->getValue());
		else
			*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloatRGB::sBlack;
		offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightSpecularColour").StartOffset;
		if(getInterfaceImp()->getSpecular()&&getInterfaceImp()->getSpecular()->getEnable())
			*reinterpret_cast<CFloat3*>(&buffer[offset])=static_cast<CFloatRGB>(getInterfaceImp()->getSpecular()->getValue());
		else
			*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloatRGB::sBlack;
		offset=mConstantBuffer->getDescription()->getConstantDesc("gDirectionLightDirection").StartOffset;
		*reinterpret_cast<CFloat3*>(&buffer[offset])=static_cast<IDirectionLightPropertyImp*>(getInterfaceImp()->queryInterface_IDirectionLightProperty())->getDirectionMT();
	}
	break;
	case IEnum::ELightType_Point:
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightDiffuseColour").StartOffset;
		if(getInterfaceImp()->getDiffuse()&&getInterfaceImp()->getDiffuse()->getEnable())
			*reinterpret_cast<CFloat3*>(&buffer[offset])=static_cast<CFloatRGB>(getInterfaceImp()->getDiffuse()->getValue());
		else
			*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloatRGB::sBlack;
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightSpecularColour").StartOffset;
		if(getInterfaceImp()->getSpecular()&&getInterfaceImp()->getSpecular()->getEnable())
			*reinterpret_cast<CFloat3*>(&buffer[offset])=static_cast<CFloatRGB>(getInterfaceImp()->getSpecular()->getValue());
		else
			*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloatRGB::sBlack;
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightPosition").StartOffset;
		*reinterpret_cast<CFloat3*>(&buffer[offset])=getInterfaceImp()->queryInterface_ISceneElement()->getTransformer()->getPosition();
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightReciprocalRange").StartOffset;
		*reinterpret_cast<Float*>(&buffer[offset])=1.0f/getInterfaceImp()->queryInterface_IPointLightProperty()->getRange();
		offset=mConstantBuffer->getDescription()->getConstantDesc("gPointLightStartFallOffDistance").StartOffset;
		*reinterpret_cast<Float*>(&buffer[offset])=0.0f;
	}
	break;
	case IEnum::ELightType_Spot:
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightDiffuseColour").StartOffset;
		if(getInterfaceImp()->getDiffuse()&&getInterfaceImp()->getDiffuse()->getEnable())
			*reinterpret_cast<CFloat3*>(&buffer[offset])=static_cast<CFloatRGB>(getInterfaceImp()->getDiffuse()->getValue());
		else
			*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloatRGB::sBlack;
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightSpecularColour").StartOffset;
		if(getInterfaceImp()->getSpecular()&&getInterfaceImp()->getSpecular()->getEnable())
			*reinterpret_cast<CFloat3*>(&buffer[offset])=static_cast<CFloatRGB>(getInterfaceImp()->getSpecular()->getValue());
		else
			*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloatRGB::sBlack;
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightPosition").StartOffset;
		*reinterpret_cast<CFloat3*>(&buffer[offset])=getInterfaceImp()->queryInterface_ISceneElement()->getTransformer()->getPosition();
		offset=mConstantBuffer->getDescription()->getConstantDesc("gSpotLightDirection").StartOffset;
		*reinterpret_cast<CFloat3*>(&buffer[offset])=static_cast<ISpotLightPropertyImp*>(getInterfaceImp()->queryInterface_ISpotLightProperty())->getDirectionMT();
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
