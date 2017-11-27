#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CSceneImp::CSceneImp(ISceneImp * interfaceImp)
	:TInterfaceObject<ISceneImp>(interfaceImp)
	,CConstantBufferContainer("cbScene")
{
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_EndEntityCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_BeginEntityDestroy);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_EndSkyCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_BeginSkyDestroy);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_EndCameraCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_BeginCameraDestroy);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_EndLightCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_BeginLightDestroy);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_EndAmbientColourChange);
}

NSDevilX::NSRenderSystem::NSD3D11::CSceneImp::~CSceneImp()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSceneImp::onMessage(ISceneImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISceneImp::EMessage_EndEntityCreate:
	{
		auto obj=DEVILX_NEW CEntityImp(static_cast<IEntityImp*>(data));
		mEntities[static_cast<IEntityImp*>(data)]=obj;
	}
	break;
	case ISceneImp::EMessage_BeginEntityDestroy:
		mEntities.destroy(static_cast<IEntityImp*>(data));
		break;
	case ISceneImp::EMessage_EndCameraCreate:
	{
		auto obj=DEVILX_NEW CCamera(static_cast<ICameraImp*>(data));
		mCameras[static_cast<ICameraImp*>(data)]=obj;
	}
	break;
	case ISceneImp::EMessage_BeginCameraDestroy:
		mCameras.destroy(static_cast<ICameraImp*>(data));
		break;
	case ISceneImp::EMessage_EndLightCreate:
	{
		auto obj=DEVILX_NEW CLight(static_cast<ILightImp*>(data));
		mLights[static_cast<ILightImp*>(data)]=obj;
	}
	break;
	case ISceneImp::EMessage_BeginLightDestroy:
		mLights.destroy(static_cast<ILightImp*>(data));
		break;
	case ISceneImp::EMessage_EndAmbientColourChange:
		needUpdate();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSceneImp::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gAmbientColour").StartOffset;
	*reinterpret_cast<CFloat3*>(&buffer[offset])=getInterfaceImp()->getAmbientColour().rgb();
}
