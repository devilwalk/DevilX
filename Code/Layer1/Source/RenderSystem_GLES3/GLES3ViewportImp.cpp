#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CViewportImp::CViewportImp(IViewportImp * interfaceImp)
	:TInterfaceObject<IViewportImp>(interfaceImp)
	,mRenderTarget(CSystemImp::getSingleton().getWindow(static_cast<IWindowImp*>(interfaceImp->getRenderTarget())))
	,mCamera(nullptr)
	,mTask(nullptr)
	,mOverlayManager(nullptr)
{
	mOverlayManager=DEVILX_NEW COverlayManager(this);
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

NSDevilX::NSRenderSystem::NSGLES3::CViewportImp::~CViewportImp()
{
	DEVILX_DELETE(mOverlayManager);
	DEVILX_DELETE(mTask);
	DEVILX_DELETE(getInternal());
}

Void NSDevilX::NSRenderSystem::NSGLES3::CViewportImp::prepare()
{
	process();
	mTask->prepare();
}

Void NSDevilX::NSRenderSystem::NSGLES3::CViewportImp::render()
{
	mTask->process();
	mOverlayManager->render();
}

Void NSDevilX::NSRenderSystem::NSGLES3::CViewportImp::onMessage(IViewportImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
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

Void NSDevilX::NSRenderSystem::NSGLES3::CViewportImp::onMessage(CWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
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

Boolean NSDevilX::NSRenderSystem::NSGLES3::CViewportImp::_process(UInt32 flagIndex,OUT Bool & needNextProcess)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Size:
		_updateInternal();
		return true;
	}
	return false;
}

Void NSDevilX::NSRenderSystem::NSGLES3::CViewportImp::_updateInternal()
{
	getInternal()->setX(static_cast<GLint>(getInterfaceImp()->getLeft()*getRenderTarget()->getInternal()->getWidth()));
	getInternal()->setY(static_cast<GLint>(getInterfaceImp()->getTop()*getRenderTarget()->getInternal()->getHeight()));
	getInternal()->setWidth(static_cast<GLsizei>(getInterfaceImp()->getWidth()*getRenderTarget()->getInternal()->getWidth()));
	getInternal()->setHeight(static_cast<GLsizei>(getRenderTarget()->getInternal()->getHeight()*getInterfaceImp()->getHeight()));
	getInternal()->needUpdate();
}

Void NSDevilX::NSRenderSystem::NSGLES3::CViewportImp::_updateRenderTask()
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