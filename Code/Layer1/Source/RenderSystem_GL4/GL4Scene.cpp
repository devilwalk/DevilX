#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CScene::CScene(ISceneImp * interfaceImp)
	:TInterfaceObject<ISceneImp>(interfaceImp)
	,CConstantBufferContainer("cbScene")
{
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_EndRenderableObjectCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_BeginRenderableObjectDestroy);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_EndCameraCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_BeginCameraDestroy);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_EndLightCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_BeginLightDestroy);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_EndAmbientColourChange);
}

NSDevilX::NSRenderSystem::NSGL4::CScene::~CScene()
{
}

Void NSDevilX::NSRenderSystem::NSGL4::CScene::onMessage(ISceneImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISceneImp::EMessage_EndRenderableObjectCreate:
	{
		auto obj=DEVILX_NEW CRenderableObject(static_cast<IRenderableObjectImp*>(data));
		mRenderableObjects[static_cast<IRenderableObjectImp*>(data)]=obj;
	}
	break;
	case ISceneImp::EMessage_BeginRenderableObjectDestroy:
		mRenderableObjects.destroy(static_cast<IRenderableObjectImp*>(data));
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

Void NSDevilX::NSRenderSystem::NSGL4::CScene::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gAmbientColour").StartOffset;
	memcpy(&buffer[offset],&getInterfaceImp()->getAmbientColour(),sizeof(CFloat3));
}
