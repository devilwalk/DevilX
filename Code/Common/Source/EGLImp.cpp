#include "Precompiler.h"
#include "GLEW/src/glew.c"
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
//EGL 1.0
EGLAPI EGLBoolean EGLAPIENTRY eglChooseConfig(EGLDisplay dpy,const EGLint* attrib_list,EGLConfig* configs,EGLint config_size,EGLint* num_config)
{
	static NSDevilX::TMap<int,int> pfd;
	pfd.clear();
	pfd.add(WGL_DRAW_TO_WINDOW_ARB,GL_TRUE);
	pfd.add(WGL_SUPPORT_OPENGL_ARB,GL_TRUE);
	pfd.add(WGL_DOUBLE_BUFFER_ARB,GL_TRUE);
	pfd.add(WGL_PIXEL_TYPE_ARB,WGL_TYPE_RGBA_ARB);
	pfd.add(WGL_COLOR_BITS_ARB,32);
	pfd.add(WGL_DEPTH_BITS_ARB,24);
	pfd.add(WGL_STENCIL_BITS_ARB,8);
	pfd.add(WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB);
	auto attrib_pt=attrib_list;
	while(attrib_pt&&((*attrib_pt)!=EGL_NONE))
	{
		auto key=*attrib_pt;
		auto value=*(attrib_pt+1);
		switch(key)
		{
		case EGL_BUFFER_SIZE:
			pfd[WGL_COLOR_BITS_ARB]=value;
			break;
		case EGL_RED_SIZE:
			pfd[WGL_RED_BITS_ARB]=value;
			break;
		case EGL_GREEN_SIZE:
			pfd[WGL_GREEN_BITS_ARB]=value;
			break;
		case EGL_BLUE_SIZE:
			pfd[WGL_BLUE_BITS_ARB]=value;
			break;
		case EGL_ALPHA_SIZE:
			pfd[WGL_ALPHA_BITS_ARB]=value;
			break;
		case EGL_BIND_TO_TEXTURE_RGB:
		case EGL_BIND_TO_TEXTURE_RGBA:
			pfd[WGL_DRAW_TO_BITMAP_ARB]=value;
			break;
		case EGL_COLOR_BUFFER_TYPE:
			switch(value)
			{
			case EGL_RGB_BUFFER:
				pfd[WGL_PIXEL_TYPE_ARB]=WGL_TYPE_RGBA_ARB;
				break;
			case EGL_LUMINANCE_BUFFER:
				pfd[WGL_PIXEL_TYPE_ARB]=WGL_TYPE_COLORINDEX_ARB;
				break;
			}
			break;
		case EGL_DEPTH_SIZE:
			pfd[WGL_DEPTH_BITS_ARB]=value;
			break;
		case EGL_STENCIL_SIZE:
			pfd[WGL_STENCIL_BITS_ARB]=value;
			break;
		}
		attrib_pt+=2;
	}
	NSDevilX::TVector<int> attribs;
	attribs.reserve(pfd.size()+1);
	for(const auto& attr:pfd)
	{
		attribs.push_back(attr.first);
		attribs.push_back(attr.second);
	}
	attribs.push_back(GL_NONE);
	int fmt;
	UINT num;
	auto ret=wglChoosePixelFormatARB(static_cast<HDC>(dpy),&attribs[0],nullptr,1,&fmt,&num);
	if(num_config)
	{
		*num_config=ret?1:0;
	}
	if(configs&&config_size)
	{
		configs[0]=&pfd;
	}
	return ret;
}
EGLAPI EGLContext EGLAPIENTRY eglCreateContext(EGLDisplay dpy,EGLConfig config,EGLContext share_context,const EGLint* attrib_list)
{
	if(share_context!=EGL_NO_CONTEXT)
		return EGL_NO_CONTEXT;
	NSDevilX::TVector<int> attribs;
	attribs.reserve(static_cast<NSDevilX::TMap<int,int>*>(config)->size()+1);
	for(const auto& attr:*static_cast<NSDevilX::TMap<int,int>*>(config))
	{
		attribs.push_back(attr.first);
		attribs.push_back(attr.second);
	}
	attribs.push_back(GL_NONE);
	int fmt;
	UINT num;
	auto success=wglChoosePixelFormatARB(static_cast<HDC>(dpy),&attribs[0],nullptr,1,&fmt,&num);
	if((!success)||(!SetPixelFormat(static_cast<HDC>(dpy),fmt,nullptr)))
	{
		return EGL_NO_SURFACE;
	}
	auto context=wglCreateContext(static_cast<HDC>(dpy));
	return context;
}
EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface(EGLDisplay dpy,EGLConfig config,EGLNativeWindowType win,const EGLint* attrib_list)
{
	auto pfd=*static_cast<NSDevilX::TMap<int,int>*>(config);
	auto attrb_pt=attrib_list;
	while(attrb_pt&&((*attrb_pt)!=EGL_NONE))
	{
		auto key=*attrb_pt;
		auto value=*(attrb_pt+1);

		switch(key)
		{
		case EGL_GL_COLORSPACE:
			switch(value)
			{
			case EGL_GL_COLORSPACE_SRGB:
				pfd[WGL_COLORSPACE_EXT]=WGL_COLORSPACE_SRGB_EXT;
				break;
			}
			break;
		case EGL_RENDER_BUFFER:
			switch(value)
			{
			case EGL_SINGLE_BUFFER:
				pfd[WGL_DOUBLE_BUFFER_ARB]=GL_FALSE;
				break;
			}
			break;
		}

		attrb_pt+=2;
	}
	NSDevilX::TVector<int> attribs;
	attribs.reserve(pfd.size()+1);
	for(const auto& attr:pfd)
	{
		attribs.push_back(attr.first);
		attribs.push_back(attr.second);
	}
	attribs.push_back(GL_NONE);
	auto dc=GetDC(win);
	int fmt;
	UINT num;
	auto success=wglChoosePixelFormatARB(dc,&attribs[0],nullptr,1,&fmt,&num);
	if(!success)
	{
		ReleaseDC(win,dc);
		return EGL_NO_SURFACE;
	}
	if(!SetPixelFormat(dc,fmt,nullptr))
	{
		ReleaseDC(win,dc);
		return EGL_NO_SURFACE;
	}
	return dc;
}
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext(EGLDisplay dpy,EGLContext ctx)
{
	return wglDeleteContext(static_cast<HGLRC>(ctx))?EGL_TRUE:EGL_FALSE;
}
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy,EGLSurface surface)
{
	return ReleaseDC(WindowFromDC(static_cast<HDC>(surface)),static_cast<HDC>(surface))?EGL_TRUE:EGL_FALSE;
}
EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay(void)
{
	return EGL_NO_DISPLAY;
}
EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface(EGLint readdraw)
{
	return EGL_NO_SURFACE;
}
EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay(EGLNativeDisplayType display_id)
{
	if(EGL_DEFAULT_DISPLAY==display_id)
	{
		display_id=GetDC(NULL);
	}
	return display_id;
}
EGLAPI EGLint EGLAPIENTRY eglGetError(void)
{
	return GetLastError();
}
EGLAPI EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy,EGLint* major,EGLint* minor)
{
	auto ret=EGL_TRUE;
	WNDCLASS wc;
	PIXELFORMATDESCRIPTOR pfd;
	HDC dc=NULL;
	int visual=0;
	HGLRC rc=NULL;
	HWND wnd=NULL;
	ZeroMemory(&wc,sizeof(WNDCLASS));
	wc.hInstance=GetModuleHandle(NULL);
	wc.lpfnWndProc=DefWindowProc;
	wc.lpszClassName="GLEW";
	if(0==RegisterClass(&wc)) goto FINISH;
	wnd=CreateWindow("GLEW","GLEW",0,CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,
		GetModuleHandle(NULL),NULL);
	if(NULL==wnd) goto FINISH;
	dc=GetDC(wnd);
	if(NULL==dc) goto FINISH;
	ZeroMemory(&pfd,sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion=1;
	pfd.dwFlags=PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL;
	visual=ChoosePixelFormat(dc,&pfd);
	if(0==visual) goto FINISH;
	if(FALSE==SetPixelFormat(dc,visual,&pfd)) goto FINISH;
	rc=wglCreateContext(dc);
	if(NULL==rc) goto FINISH;
	if(FALSE==wglMakeCurrent(dc,rc)) goto FINISH;
	ret&=glewInit()>=0;
FINISH:
	if(rc)
	{
		wglMakeCurrent(dc,NULL);
		wglDeleteContext(rc);
	}
	if(dc)
	{
		ReleaseDC(wnd,dc);
	}
	if(wnd)
	{
		DestroyWindow(wnd);
		UnregisterClass(wc.lpszClassName,wc.hInstance);
	}
	return ret;
}
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent(EGLDisplay dpy,EGLSurface draw,EGLSurface read,EGLContext ctx)
{
	return wglMakeContextCurrentARB(static_cast<HDC>(draw),static_cast<HDC>(read),static_cast<HGLRC>(ctx))?EGL_TRUE:EGL_FALSE;
}
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers(EGLDisplay dpy,EGLSurface surface)
{
	return SwapBuffers(static_cast<HDC>(surface))?EGL_TRUE:EGL_FALSE;
}
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate(EGLDisplay dpy)
{
	return EGL_TRUE;
}
//EGL 1.2
EGLAPI EGLBoolean EGLAPIENTRY eglBindAPI(EGLenum api)
{
	return EGL_TRUE;
}
//EGL 1.5
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformWindowSurface(EGLDisplay dpy,EGLConfig config,void* native_window,const EGLAttrib* attrib_list)
{
	return eglCreateWindowSurface(dpy,config,static_cast<EGLNativeWindowType>(native_window),attrib_list);
}
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
//EGL 1.0
EGLAPI EGLBoolean EGLAPIENTRY eglChooseConfig(EGLDisplay dpy,const EGLint* attrib_list,EGLConfig* configs,EGLint config_size,EGLint* num_config)
{
	return EGL_FALSE;
}
EGLAPI EGLContext EGLAPIENTRY eglCreateContext(EGLDisplay dpy,EGLConfig config,EGLContext share_context,const EGLint* attrib_list)
{
	return EGL_NO_CONTEXT;
}
EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface(EGLDisplay dpy,EGLConfig config,EGLNativeWindowType win,const EGLint* attrib_list)
{
	return EGL_NO_SURFACE;
}
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext(EGLDisplay dpy,EGLContext ctx)
{
	return EGL_FALSE;
}
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy,EGLSurface surface)
{
	return EGL_FALSE;
}
EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay(void)
{
	return EGL_NO_DISPLAY;
}
EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface(EGLint readdraw)
{
	return EGL_NO_SURFACE;
}
EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay(EGLNativeDisplayType display_id)
{
	return EGL_NO_DISPLAY;
}
EGLAPI EGLint EGLAPIENTRY eglGetError(void)
{
	return 0;
}
EGLAPI EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy,EGLint* major,EGLint* minor)
{
	return EGL_FALSE;
}
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent(EGLDisplay dpy,EGLSurface draw,EGLSurface read,EGLContext ctx)
{
	return EGL_FALSE;
}
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers(EGLDisplay dpy,EGLSurface surface)
{
	return EGL_FALSE;
}
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate(EGLDisplay dpy)
{
	return EGL_FALSE;
}
//EGL 1.2
EGLAPI EGLBoolean EGLAPIENTRY eglBindAPI(EGLenum api)
{
	return EGL_FALSE;
}
//EGL 1.5
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformWindowSurface(EGLDisplay dpy,EGLConfig config,void* native_window,const EGLAttrib* attrib_list)
{
	return EGL_NO_SURFACE;
}
#endif