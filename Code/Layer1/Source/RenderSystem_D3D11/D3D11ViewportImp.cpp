#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::CViewportImp(IViewportImp * interfaceImp)
	:TInterfaceObject<IViewportImp>(interfaceImp)
	,mRenderTarget(CSystemImp::getSingleton().getWindow(static_cast<IWindowImp*>(interfaceImp->getRenderTarget())))
	,mCamera(nullptr)
	,mRenderTask(nullptr)
	,mQueryTask(nullptr)
	,mOverlayManager(nullptr)
{
	mOverlayManager=DEVILX_NEW COverlayManager(this);
	setInternal(DEVILX_NEW CViewport(getRenderTarget()->getInternal()));
	_updateInternal();
	_updateRenderTask();
	_updateQueryTask();
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndWidthChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndHeightChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndLeftChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndTopChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndClearColourChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndCameraChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndQueryCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_BeginQueryDestroy);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IViewportImp>*>(this),IViewportImp::EMessage_EndQueryDestroy);
	if(dynamic_cast<CWindowImp*>(getRenderTarget()))
	{
		static_cast<CWindowImp*>(getRenderTarget())->addListener(static_cast<TMessageReceiver<CWindowImp>*>(this),CWindowImp::EMessage_BeginResize);
		static_cast<CWindowImp*>(getRenderTarget())->addListener(static_cast<TMessageReceiver<CWindowImp>*>(this),CWindowImp::EMessage_EndResize);
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::~CViewportImp()
{
	DEVILX_DELETE(mQueryTask);
	DEVILX_DELETE(mRenderTask);
	DEVILX_DELETE(getInternal());
	DEVILX_DELETE(mOverlayManager);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::prepare()
{
	process();
	if(mQueryTask)
		mQueryTask->prepare();
	mRenderTask->prepare();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::render()
{
	if(mQueryTask)
		mQueryTask->process();
	mRenderTask->process();
	mOverlayManager->render();
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
			static_cast<CForwardRenderTask*>(mRenderTask)->setClearColour(getInterfaceImp()->getClearColour());
			break;
		}
		break;
	case IViewportImp::EMessage_EndCameraChange:
		mCamera=getInterfaceImp()->getCamera()?CSystemImp::getSingleton().getScene(static_cast<ISceneImp*>(static_cast<ISceneElementImp*>(getInterfaceImp()->getCamera()->queryInterface_ISceneElement())->getScene()))->getCamera(static_cast<ICameraImp*>(getInterfaceImp()->getCamera())):nullptr;
		getInternal()->setCamera(mCamera);
		break;
	case IViewportImp::EMessage_EndQueryCreate:
		_updateQueryTask();
		static_cast<IQueryImp*>(data)->addListener(static_cast<TMessageReceiver<IQueryImp>*>(this),IQueryImp::EMessage_EndAreaChange);
		break;
	case IViewportImp::EMessage_BeginQueryDestroy:
		mQueryTask->removeQueryRange(reinterpret_cast<SizeT>(data));
		break;
	case IViewportImp::EMessage_EndQueryDestroy:
		_updateQueryTask();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::onMessage(CWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CWindowImp::EMessage_BeginResize:
		mRenderTask->clearState();
		if(mQueryTask)
			mQueryTask->clearState();
		break;
	case CWindowImp::EMessage_EndResize:
		_updateInternal();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_EndFrame:
		mQueryTask->postProcess();
		getInterfaceImp()->clearQueryResult();
		for(auto result:mQueryTask->getQueryResults())
		{
			getInterfaceImp()->addQueryResult(result);
		}
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::onMessage(IQueryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IQueryImp::EMessage_EndAreaChange:
		mQueryTask->setQueryRange(reinterpret_cast<SizeT>(notifier),notifier->getStartPosition(),notifier->getEndPosition());
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
	DEVILX_DELETE(mRenderTask);
	mRenderTask=nullptr;
	switch(getInterfaceImp()->getTechnique())
	{
	case IEnum::ERenderTechnique_Forward:
		mRenderTask=DEVILX_NEW CForwardRenderTask(getInternal());
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CViewportImp::_updateQueryTask()
{
	if(getInterfaceImp()->getQueies().empty())
	{
		DEVILX_DELETE(mQueryTask);
		mQueryTask=nullptr;
		CSystemImp::getSingleton().removeListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_EndFrame);
	}
	else
	{
		if(!mQueryTask)
		{
			mQueryTask=DEVILX_NEW CQueryTask(getInternal());
			CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_EndFrame);
		}
	}
}
