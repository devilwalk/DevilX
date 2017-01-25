#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::CViewportImp(IViewportImp * interfaceImp)
	:TInterfaceObject<IViewportImp>(interfaceImp)
	,mRenderTarget(CSystemImp::getSingleton().getWindow(static_cast<IWindowImp*>(interfaceImp->getRenderTarget())))
	,mCamera(nullptr)
	,mTask(nullptr)
{
	setInternal(DEVILX_NEW CViewport(getRenderTarget()->getInternal()));
	_updateInternal();
	_updateRenderTask();
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndWidthChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndHeightChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndLeftChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndTopChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndClearColourChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndCameraChange);
	if(dynamic_cast<CWindowImp*>(getRenderTarget()))
	{
		static_cast<CWindowImp*>(getRenderTarget())->addListener(static_cast<TMessageReceiver<CWindowImp>*>(this),CWindowImp::EMessage_BeginResize);
		static_cast<CWindowImp*>(getRenderTarget())->addListener(static_cast<TMessageReceiver<CWindowImp>*>(this),CWindowImp::EMessage_EndResize);
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::~CViewportImp()
{
	DEVILX_DELETE(mTask);
	DEVILX_DELETE(getInternal());
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::prepare()
{
	process();
	mTask->prepare();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::render()
{
	mTask->process();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::onMessage(IViewportImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IViewportImp::EMessage_EndWidthChange:
	case IViewportImp::EMessage_EndHeightChange:
	case IViewportImp::EMessage_EndLeftChange:
	case IViewportImp::EMessage_EndTopChange:
		addDirtyFlag(EDirtyFlag_Size);
		break;
	case IViewportImp::EMessage_EndClearColourChange:
		switch(getInterfaceImp()->getTechnique())
		{
		case IEnum::ERenderTechnique_Forward:
			static_cast<CForwardRenderTask*>(mTask)->setClearColour(getInterfaceImp()->getClearColour());
			break;
		}
		break;
	case IViewportImp::EMessage_EndCameraChange:
		mCamera=getInterfaceImp()->getCamera()?CSystemImp::getSingleton().getScene(static_cast<ISceneImp*>(static_cast<ISceneElementImp*>(getInterfaceImp()->getCamera()->queryInterface_ISceneElement())->getScene()))->getCamera(static_cast<ICameraImp*>(getInterfaceImp()->getCamera())):nullptr;
		getInternal()->setCamera(mCamera);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::onMessage(CWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CWindowImp::EMessage_BeginResize:
		mTask->clearState();
		break;
	case CWindowImp::EMessage_EndResize:
		_updateInternal();
		break;
	}
}

Boolean NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::_process(UInt32 flagIndex,OUT Bool & needNextProcess)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Size:
		_updateInternal();
		return true;
	}
	return false;
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::_updateInternal()
{
	D3D11_TEXTURE2D_DESC desc;
	getRenderTarget()->getRenderTargetResource()->GetDesc(&desc);
	getInternal()->getInternalRef().Height=desc.Height*getInterfaceImp()->getHeight();
	getInternal()->getInternalRef().MaxDepth=1.0f;
	getInternal()->getInternalRef().MinDepth=0.0f;
	getInternal()->getInternalRef().TopLeftX=getInterfaceImp()->getLeft()*desc.Width;
	getInternal()->getInternalRef().TopLeftY=getInterfaceImp()->getTop()*desc.Height;
	getInternal()->getInternalRef().Width=getInterfaceImp()->getWidth()*desc.Width;
	getInternal()->needUpdate();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::_updateRenderTask()
{
	DEVILX_DELETE(mTask);
	mTask=nullptr;
	switch(getInterfaceImp()->getTechnique())
	{
	case IEnum::ERenderTechnique_Forward:
		mTask=DEVILX_NEW CForwardRenderTask(getInternal());
		break;
	}
}