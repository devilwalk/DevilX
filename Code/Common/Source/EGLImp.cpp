#include "Precompiler.h"
#include "GLEW/src/glew.c"
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
struct SEGLConfig
{
	NSDevilX::TMap<int,int> mAttribs;
};
struct SEGLContext
{
	HGLRC mContext;
	NSDevilX::TMap<int,int> mAttribs;
	~SEGLContext()
	{
		destruction();
	}
	BOOL destruction()
	{
		return wglDeleteContext(mContext);
	}
};
struct SEGLSurface
{
	HDC mDC;
	HGLRC mContext;
	NSDevilX::TMap<int,int> mAttribs;
	~SEGLSurface()
	{
		destruction();
	}
	BOOL destruction()
	{
		auto ret=wglDeleteContext(mContext);
		ret&=ReleaseDC(WindowFromDC(mDC),mDC);
		return ret;
	}
};
class CEGL
{
protected:
	NSDevilX::TResourcePtrVector<SEGLConfig> mConfigs;
	NSDevilX::TResourcePtrVector<SEGLContext> mContexts;
	NSDevilX::TResourcePtrVector<SEGLSurface> mSurfaces;
public:
	CEGL()
	{

	}
	~CEGL()
	{

	}
	static NSDevilX::Boolean map(const EGLint* attrib_list,OUT NSDevilX::TMap<int,int>& attrs)
	{
		auto attrib_pt=attrib_list;
		while(attrib_pt&&((*attrib_pt)!=EGL_NONE))
		{
			auto key=*attrib_pt;
			auto value=*(attrib_pt+1);
			switch(key)
			{
			case EGL_BUFFER_SIZE:
				attrs[WGL_COLOR_BITS_ARB]=value;
				break;
			case EGL_RED_SIZE:
				attrs[WGL_RED_BITS_ARB]=value;
				break;
			case EGL_GREEN_SIZE:
				attrs[WGL_GREEN_BITS_ARB]=value;
				break;
			case EGL_BLUE_SIZE:
				attrs[WGL_BLUE_BITS_ARB]=value;
				break;
			case EGL_ALPHA_SIZE:
				attrs[WGL_ALPHA_BITS_ARB]=value;
				break;
			case EGL_BIND_TO_TEXTURE_RGB:
			case EGL_BIND_TO_TEXTURE_RGBA:
				attrs[WGL_DRAW_TO_BITMAP_ARB]=value;
				break;
			case EGL_COLOR_BUFFER_TYPE:
				switch(value)
				{
				case EGL_RGB_BUFFER:
					attrs[WGL_PIXEL_TYPE_ARB]=WGL_TYPE_RGBA_ARB;
					break;
				case EGL_LUMINANCE_BUFFER:
					attrs[WGL_PIXEL_TYPE_ARB]=WGL_TYPE_COLORINDEX_ARB;
					break;
				}
				break;
			case EGL_DEPTH_SIZE:
				attrs[WGL_DEPTH_BITS_ARB]=value;
				break;
			case EGL_STENCIL_SIZE:
				attrs[WGL_STENCIL_BITS_ARB]=value;
				break;
			case EGL_GL_COLORSPACE:
				switch(value)
				{
				case EGL_GL_COLORSPACE_SRGB:
					attrs[WGL_COLORSPACE_EXT]=WGL_COLORSPACE_SRGB_EXT;
					break;
				}
				break;
			case EGL_RENDER_BUFFER:
				switch(value)
				{
				case EGL_SINGLE_BUFFER:
					attrs[WGL_DOUBLE_BUFFER_ARB]=GL_FALSE;
					break;
				}
				break;
			}
			attrib_pt+=2;
		}
		return true;
	}
	static NSDevilX::TVector<int> toWGLArray(const NSDevilX::TMap<int,int>& attrs,NSDevilX::Boolean addNone=false)
	{
		NSDevilX::TVector<int> ret;
		ret.reserve(attrs.size()+(addNone?1:0));
		for(auto& v:attrs)
		{
			ret.push_back(v.first);
			ret.push_back(v.second);
		}
		if(addNone)
		{
			ret.push_back(GL_NONE);
		}
		return ret;
	}
	SEGLConfig* createConfig()
	{
		auto ret=new SEGLConfig();
		mConfigs.push_back(ret);
		return ret;
	}
	SEGLContext constructContext(HDC dc,const SEGLConfig& cfg,const EGLint* attrib_list)
	{
		SEGLContext ret={};
		ret.mAttribs=cfg.mAttribs;
		map(attrib_list,ret.mAttribs);
		int fmt=0;
		UINT num=0;
		wglChoosePixelFormatARB(dc,&toWGLArray(ret.mAttribs,true)[0],nullptr,1,&fmt,&num);
		SetPixelFormat(dc,fmt,nullptr);
		ret.mContext=wglCreateContext(dc);
		auto success=wglMakeCurrent(dc,ret.mContext);
		return ret;
	}
	SEGLContext* createContext(HDC dc,const SEGLConfig& cfg,const EGLint* attrib_list)
	{
		auto ctx=constructContext(dc,cfg,attrib_list);
		if(!ctx.mContext)
		{
			return nullptr;
		}
		auto ret=new SEGLContext(ctx);
		mContexts.push_back(ret);
		return ret;
	}
	SEGLSurface* createSurface(HDC dc,const SEGLConfig& cfg,const EGLint* attrib_list)
	{
		auto ctx=constructContext(dc,cfg,attrib_list);
		if(!ctx.mContext)
		{
			return nullptr;
		}
		auto success=wglMakeCurrent(dc,ctx.mContext);
		auto ret=new SEGLSurface();
		ret->mAttribs=ctx.mAttribs;
		ret->mContext=ctx.mContext;
		ret->mDC=dc;
		mSurfaces.push_back(ret);
		return ret;
	}
	BOOL destroyContext(SEGLContext* context)
	{
		auto ret=context->destruction();
		mContexts.destroy(context);
		return ret;
	}
	BOOL destroySurface(SEGLSurface* surface)
	{
		auto ret=surface->destruction();
		mSurfaces.destroy(surface);
		return ret;
	}
};
static CEGL* gEGL=nullptr;
static HDC gEGLDC=NULL;
static auto _eglGetDC(EGLDisplay dpy)
{
	return (dpy==EGL_DEFAULT_DISPLAY)?gEGLDC:static_cast<HDC>(dpy);
}
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
	CEGL::map(attrib_list,pfd);
	auto attribs=CEGL::toWGLArray(pfd,true);
	int fmt;
	UINT num;
	auto ret=wglChoosePixelFormatARB(_eglGetDC(dpy),&attribs[0],nullptr,1,&fmt,&num);
	if(num_config)
	{
		*num_config=ret?1:0;
	}
	if(configs&&config_size)
	{
		auto cfg=gEGL->createConfig();
		cfg->mAttribs=pfd;
		configs[0]=cfg;
	}
	return ret;
}
EGLAPI EGLContext EGLAPIENTRY eglCreateContext(EGLDisplay dpy,EGLConfig config,EGLContext share_context,const EGLint* attrib_list)
{
	EGLContext ret=EGL_NO_CONTEXT;
	HGLRC rc=NULL;
	HWND wnd=CreateWindow("GLEW","GLEW_CONTEXT",0,CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,
		GetModuleHandle(NULL),NULL);
	if(NULL==wnd)
		return EGL_NO_CONTEXT;
	HDC dc=GetDC(wnd);

	auto context=gEGL->createContext(dc,*static_cast<const SEGLConfig*>(config),attrib_list);

	ReleaseDC(wnd,dc);
	DestroyWindow(wnd);
	return context;
}
EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface(EGLDisplay dpy,EGLConfig config,EGLNativeWindowType win,const EGLint* attrib_list)
{
	return gEGL->createSurface(GetDC(win),*static_cast<SEGLConfig*>(config),attrib_list);
}
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext(EGLDisplay dpy,EGLContext ctx)
{
	return gEGL->destroyContext(static_cast<SEGLContext*>(ctx));
}
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy,EGLSurface surface)
{
	return gEGL->destroySurface(static_cast<SEGLSurface*>(surface));
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
	return display_id;
}
EGLAPI EGLint EGLAPIENTRY eglGetError(void)
{
	return GetLastError();
}
EGLAPI EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy,EGLint* major,EGLint* minor)
{
	gEGL=new CEGL();
	auto ret=EGL_TRUE;
	WNDCLASS wc;
	PIXELFORMATDESCRIPTOR pfd;
	int visual=0;
	HDC dc=NULL;
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
		wglMakeCurrent(NULL,rc);
		wglDeleteContext(rc);
	}
	if(dpy==EGL_DEFAULT_DISPLAY)
	{
		gEGLDC=dc;
	}
	else
	{
		if(dc)
		{
			ReleaseDC(wnd,dc);
		}
		if(wnd)
		{
			DestroyWindow(wnd);
			UnregisterClass("GLEW",GetModuleHandle(NULL));
		}
	}
	return ret;
}
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent(EGLDisplay dpy,EGLSurface draw,EGLSurface read,EGLContext ctx)
{
	HDC draw_dc=NULL;
	HDC read_dc=NULL;
	HGLRC context=NULL;
	if(draw)
	{
		draw_dc=static_cast<SEGLSurface*>(draw)->mDC;
	}
	if(read)
	{
		read_dc=static_cast<SEGLSurface*>(read)->mDC;
	}
	if(ctx)
	{
		context=static_cast<SEGLContext*>(ctx)->mContext;
	}
	if(FALSE==wglMakeCurrent(draw_dc,context))
	{
		if(draw)
		{
			context=static_cast<SEGLSurface*>(draw)->mContext;
		}
		else if(read)
		{
			context=static_cast<SEGLSurface*>(read)->mContext;
		}
		return wglMakeCurrent(draw_dc,context);
	}
	return EGL_FALSE;
}
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers(EGLDisplay dpy,EGLSurface surface)
{
	return SwapBuffers(static_cast<HDC>(surface))?EGL_TRUE:EGL_FALSE;
}
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate(EGLDisplay dpy)
{
	HWND wnd=NULL;
	if(gEGLDC)
	{
		wnd=WindowFromDC(gEGLDC);
		ReleaseDC(wnd,gEGLDC);
	}
	if(wnd)
	{
		DestroyWindow(wnd);
		UnregisterClass("GLEW",GetModuleHandle(NULL));
	}
	delete gEGL;
	gEGL=nullptr;
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