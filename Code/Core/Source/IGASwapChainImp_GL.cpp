#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;
#if DEVILX_WINDOW_SYSTEM == DEVILX_WINDOW_SYSTEM_WINDOWS
IGASwapChainImp::IGASwapChainImp(HWND wnd)
	:mHDC(GetDC(wnd))
{
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
	wglChoosePixelFormatARB(mHDC,attrib_list,nullptr,1,&pixel_format,&num_formats);
	SetPixelFormat(mHDC,pixel_format,&PIXELFORMATDESCRIPTOR());
}

IGASwapChainImp::~IGASwapChainImp()
{

}

IGARenderTargetView * IGASwapChainImp::getRenderTargetView() const
{
	return const_cast<IGASwapChainImp*>(this);
}

IGADepthStencilView * IGASwapChainImp::getDepthStencilView() const
{
	return const_cast<IGASwapChainImp*>(this);
}

Void IGASwapChainImp::present()
{
	SwapBuffers(mHDC);
}
#endif