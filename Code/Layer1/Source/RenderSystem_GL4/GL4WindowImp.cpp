#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CWindowImp::CWindowImp(IWindowImp * interfaceImp)
	:TInterfaceObject<IWindowImp>(interfaceImp)
	,CRenderTargetImp(0)
	,mDC(nullptr)
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	mDC=GetDC(static_cast<HWND>(getInterfaceImp()->getWindow()->getHandle()));
	const Int32 attrib_list[]=
	{
		WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB,GL_TRUE,
		WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB,WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,32,
		WGL_DEPTH_BITS_ARB,24,
		WGL_STENCIL_BITS_ARB,8,
		0,        //End
	};
	Int32 pixel_format=0;
	UInt32 num_formats=0;
	wglChoosePixelFormatARB(static_cast<HDC>(getDC()),attrib_list,nullptr,1,&pixel_format,&num_formats);
	SetPixelFormat(static_cast<HDC>(getDC()),pixel_format,&PIXELFORMATDESCRIPTOR());
	wglMakeCurrent(static_cast<HDC>(getDC()),CSystemImp::getSingleton().getContext());
	RECT rc;
	GetClientRect(static_cast<HWND>(getInterfaceImp()->getWindow()->getHandle()),&rc);
	auto width=rc.right-rc.left;
	auto height=rc.bottom-rc.top;
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
	glGenTextures(1,&mRenderTargetResource);
	glTextureImage2DEXT(getRenderTargetResource(),GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
	getInternal()->setRT(0,getRenderTargetResource());
	mDepthStencil->reserve(width,height);
	getInternal()->setDS(mDepthStencil->getInternal());
	getInternal()->needUpdate();
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IWindowImp>*>(this),IWindowImp::EMessage_EndViewportCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IWindowImp>*>(this),IWindowImp::EMessage_BeginViewportDestroy);
}

NSDevilX::NSRenderSystem::NSGL4::CWindowImp::~CWindowImp()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CWindowImp::prepare()
{
	GLint width,height;
	glGetTextureLevelParameteriv(getRenderTargetResource(),0,GL_TEXTURE_WIDTH,&width);
	glGetTextureLevelParameteriv(getRenderTargetResource(),0,GL_TEXTURE_HEIGHT,&height);
	if(getInterfaceImp()->getWindow()->getSize()!=CUInt2(width,height))
	{
		_resize();
	}
	CRenderTargetImp::prepare();
}

Void NSDevilX::NSRenderSystem::NSGL4::CWindowImp::render()
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	wglMakeCurrent(static_cast<HDC>(getDC()),CSystemImp::getSingleton().getContext());
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
	CRenderTargetImp::render();
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	SwapBuffers(static_cast<HDC>(getDC()));
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
}

Void NSDevilX::NSRenderSystem::NSGL4::CWindowImp::_resize()
{
	notify(EMessage_BeginResize);
	getInternal()->setRT(0,0);
	glDeleteTextures(1,&mRenderTargetResource);
	glGenTextures(1,&mRenderTargetResource);
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	RECT rc;
	GetClientRect(static_cast<HWND>(getInterfaceImp()->getWindow()->getHandle()),&rc);
	auto width=rc.right-rc.left;
	auto height=rc.bottom-rc.top;
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
	glTextureImage2DEXT(getRenderTargetResource(),GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
	getInternal()->setRT(0,getRenderTargetResource());
	mDepthStencil->reserve(width,height);
	getInternal()->setDS(mDepthStencil->getInternal());
	getInternal()->needUpdate();
	notify(EMessage_EndResize);
}

Void NSDevilX::NSRenderSystem::NSGL4::CWindowImp::onMessage(IWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
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
