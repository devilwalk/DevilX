#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CWindowImp::CWindowImp(IWindowImp * interfaceImp)
	:TInterfaceObject<IWindowImp>(interfaceImp)
	,CRenderTargetImp(0)
	,mDC(EGL_DEFAULT_DISPLAY)
	,mDisplay(EGL_NO_DISPLAY)
	,mSurface(EGL_NO_SURFACE)
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	mDC=GetDC(static_cast<HWND>(getInterfaceImp()->getWindow()->getHandle()));
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
	mDisplay=eglGetDisplay(getDC());
	const EGLint config_attr[]={
		EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
		EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
		EGL_RED_SIZE,8,
		EGL_GREEN_SIZE,8,
		EGL_BLUE_SIZE,8,
		EGL_ALPHA_SIZE,8,
		EGL_DEPTH_SIZE,24,
		EGL_STENCIL_SIZE,8,
		EGL_NONE
	};
	EGLConfig config=0;
	EGLint num_config=0;
	eglChooseConfig(mDisplay,config_attr,&config,1,&num_config);
	mSurface=eglCreateWindowSurface(mDisplay,config,static_cast<HWND>(getInterfaceImp()->getWindow()->getHandle()),nullptr);
	eglMakeCurrent(mDisplay,mSurface,mSurface,CSystemImp::getSingleton().getContext());
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	RECT rc;
	GetClientRect(static_cast<HWND>(getInterfaceImp()->getWindow()->getHandle()),&rc);
	getInternal()->setSize(rc.right-rc.left,rc.bottom-rc.top);
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
	getInternal()->needUpdate();
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IWindowImp>*>(this),IWindowImp::EMessage_EndViewportCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IWindowImp>*>(this),IWindowImp::EMessage_BeginViewportDestroy);
}

NSDevilX::NSRenderSystem::NSGLES3::CWindowImp::~CWindowImp()
{
	ReleaseDC(static_cast<HWND>(getInterfaceImp()->getWindow()->getHandle()),static_cast<HDC>(getDC()));
}

Void NSDevilX::NSRenderSystem::NSGLES3::CWindowImp::prepare()
{
	RECT rc;
	GetClientRect(static_cast<HWND>(getInterfaceImp()->getWindow()->getHandle()),&rc);
	auto new_size=CUInt2(rc.right-rc.left,rc.bottom-rc.top);
	if(new_size!=CUInt2(getInternal()->getWidth(),getInternal()->getHeight()))
	{
		getInternal()->setSize(new_size.x,new_size.y);
		_resize();
	}
	CRenderTargetImp::prepare();
}

Void NSDevilX::NSRenderSystem::NSGLES3::CWindowImp::render()
{
	eglMakeCurrent(mDisplay,mSurface,mSurface,CSystemImp::getSingleton().getContext());
	CRenderTargetImp::render();
	eglSwapBuffers(mDisplay,mSurface);
}

Void NSDevilX::NSRenderSystem::NSGLES3::CWindowImp::_resize()
{
	notify(EMessage_BeginResize);
	getInternal()->needUpdate();
	notify(EMessage_EndResize);
}

Void NSDevilX::NSRenderSystem::NSGLES3::CWindowImp::onMessage(IWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IWindowImp::EMessage_EndViewportCreate:
	{
		CViewportImp * vp=DEVILX_NEW CViewportImp(static_cast<IViewportImp*>(data));
		mViewports[static_cast<IViewportImp*>(data)]=vp;
	}
	break;
	case IWindowImp::EMessage_BeginViewportDestroy:
		mViewports.destroy(static_cast<IViewportImp*>(data));
		break;
	}
}
