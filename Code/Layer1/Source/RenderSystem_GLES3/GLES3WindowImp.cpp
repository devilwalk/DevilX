#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CWindowImp::CWindowImp(IWindowImp * interfaceImp)
	:TInterfaceObject<IWindowImp>(interfaceImp)
	,CRenderTargetImp(0)
	,mDC(EGL_DEFAULT_DISPLAY)
	,mSurface(EGL_NO_SURFACE)
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	mDC=GetDC(static_cast<HWND>(getInterfaceImp()->getWindow()->getHandle()));
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
	const EGLint config_attr[]=
	{
		EGL_RED_SIZE,8,
		EGL_GREEN_SIZE,8,
		EGL_BLUE_SIZE,8,
		EGL_ALPHA_SIZE,8,
		EGL_COLOR_BUFFER_TYPE,EGL_RGB_BUFFER,
		EGL_DEPTH_SIZE,24,
		EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
		EGL_STENCIL_SIZE,8,
		EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
		EGL_NONE
	};
	EGLConfig config=0;
	EGLint num_config=0;
	eglChooseConfig(CSystemImp::getSingleton().getDisplay(),config_attr,&config,1,&num_config);
	CUtility::checkEGLError();
	mSurface=eglCreateWindowSurface(CSystemImp::getSingleton().getDisplay(),config,static_cast<HWND>(getInterfaceImp()->getWindow()->getHandle()),nullptr);
	CUtility::checkEGLError();
	const EGLint context_attr[]={
		EGL_CONTEXT_MAJOR_VERSION,3,
		EGL_CONTEXT_MINOR_VERSION,2,
		EGL_NONE
	};
	CUtility::checkEGLError();
	eglMakeCurrent(CSystemImp::getSingleton().getDisplay(),mSurface,mSurface,CSystemImp::getSingleton().getContext());
	CUtility::checkEGLError();
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
	eglDestroySurface(CSystemImp::getSingleton().getDisplay(),mSurface);
	CUtility::checkEGLError();
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
	eglMakeCurrent(CSystemImp::getSingleton().getDisplay(),mSurface,mSurface,CSystemImp::getSingleton().getContext());
	CUtility::checkEGLError();
	CRenderTargetImp::render();
	eglSwapBuffers(CSystemImp::getSingleton().getDisplay(),mSurface);
	CUtility::checkEGLError();
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
