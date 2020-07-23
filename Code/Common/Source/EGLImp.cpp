#include "Precompiler.h"
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
	attribs.push_back(EGL_NONE);
	int fmt;
	UINT num;
	wglChoosePixelFormatARB(static_cast<HDC>(dpy),&attribs[0],nullptr,1,&fmt,&num);
	auto ret=fmt>0;
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
	attribs.push_back(EGL_NONE);
	int fmt;
	UINT num;
	wglChoosePixelFormatARB(static_cast<HDC>(dpy),&attribs[0],nullptr,1,&fmt,&num);
	if(!SetPixelFormat(static_cast<HDC>(dpy),fmt,nullptr))
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
			case EGL_GL_COLORSPACE_LINEAR:
				break;
			case EGL_GL_COLORSPACE_SRGB:
				pfd[WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB]=EGL_TRUE;
				break;
			}
			break;
		case EGL_RENDER_BUFFER:
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
	attribs.push_back(EGL_NONE);
	int fmt;
	UINT num;
	wglChoosePixelFormatARB(static_cast<HDC>(dpy),&attribs[0],nullptr,1,&fmt,&num);
	auto dc=GetDC(win);
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
	return EGL_TRUE;
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