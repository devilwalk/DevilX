#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

NSDevilX::NSCore::NSOpenGL::CGAEnvironment::CGAEnvironment(EGLNativeWindowType window,Bool isGLES)
	:mDisplay(EGL_NO_DISPLAY)
	,mSurface(EGL_NO_SURFACE)
	,mContext(EGL_NO_CONTEXT)
	,mImp(nullptr)
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	EGLNativeDisplayType native_display=GetDC(window);
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
	mDisplay=eglGetDisplay(native_display);
	CUtility::checkEGLError();
	EGLint major,minor;
	eglInitialize(mDisplay,&major,&minor);
	CUtility::checkEGLError();
	if(isGLES)
		eglBindAPI(EGL_OPENGL_ES_API);
	else
		eglBindAPI(EGL_OPENGL_API);
	CUtility::checkEGLError();
	TMap(GLint,GLint) config_attrs;
	config_attrs[EGL_CONFORMANT]=isGLES?EGL_OPENGL_ES_BIT|EGL_OPENGL_ES2_BIT|EGL_OPENGL_ES3_BIT:EGL_OPENGL_BIT;
	config_attrs[EGL_RENDERABLE_TYPE]=isGLES?EGL_OPENGL_ES_BIT|EGL_OPENGL_ES2_BIT|EGL_OPENGL_ES3_BIT:EGL_OPENGL_BIT;
	EGLConfig config=CUtility::chooseConfig(mDisplay,&config_attrs);
	CUtility::checkEGLError();
	mSurface=eglCreateWindowSurface(mDisplay,config,window,nullptr);
	CUtility::checkEGLError();
	TMap(EGLint,EGLint) config_attr_map;
	config_attr_map[EGL_CONTEXT_MAJOR_VERSION]=4;
	config_attr_map[EGL_CONTEXT_MINOR_VERSION]=5;
	config_attr_map[EGL_CONTEXT_OPENGL_PROFILE_MASK]=EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT;
#if DEVILX_DEBUG
	config_attr_map[EGL_CONTEXT_OPENGL_DEBUG]=EGL_TRUE;
#endif
	TVector(EGLint) context_config_attr_list;
	context_config_attr_list.reserve(config_attr_map.size()*2+1);
	for(const auto& pairs:config_attr_map)
	{
		context_config_attr_list.push_back(pairs.first);
		context_config_attr_list.push_back(pairs.second);
	}
	context_config_attr_list.push_back(EGL_NONE);
	mContext=eglCreateContext(mDisplay,config,EGL_NO_CONTEXT,&context_config_attr_list[0]);
	CUtility::checkEGLError();
	eglMakeCurrent(mDisplay,mSurface,mSurface,mContext);
	CUtility::checkEGLError();
	glewInit();
#if DEVILX_DEBUG
	if(glDebugMessageCallback)
	{
		glEnable(GL_DEBUG_OUTPUT);
		CUtility::checkGLError();
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		CUtility::checkGLError();
		glDebugMessageCallback([](GLenum source,GLenum type,GLuint id,GLenum serverity,GLsizei length,const GLchar*message,const GLvoid*userParam)
			{
				OutputDebugStringA(message);
				OutputDebugStringA("\r\n");
			},nullptr);
		CUtility::checkGLError();
	}
#endif
	if(glCreateFramebuffers)
	{
		mImp.reset(DEVILX_NEW CGAContextGL45);
	}
	else
	{
		mImp.reset(DEVILX_NEW CGAContextCommon);
	}
}

NSDevilX::NSCore::NSOpenGL::CGAEnvironment::~CGAEnvironment()
{
	CUtility::checkGLError();
	eglDestroyContext(mDisplay,mContext);
	CUtility::checkEGLError();
	eglDestroySurface(mDisplay,mSurface);
	CUtility::checkEGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironment::clear(IGADepthStencilViewImp* view,Float depth)
{
	mImp->clear(view,depth);
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironment::clear(IGADepthStencilViewImp* view,UInt8 stencil)
{
	mImp->clear(view,stencil);
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironment::clear(IGADepthStencilViewImp* view,Float depth,UInt8 stencil)
{
	mImp->clear(view,depth,stencil);
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironment::clear(IGARenderTargetViewImp* view,const Float colourRGBA[4])
{
	mImp->clear(view,colourRGBA);
}

NSDevilX::NSCore::NSOpenGL::CGAContextBase::CGAContextBase()
{
}

NSDevilX::NSCore::NSOpenGL::CGAContextBase::~CGAContextBase()
{
	glDeleteFramebuffers(1,&mFrameBufferObject);
}

Void NSDevilX::NSCore::NSOpenGL::CGAContextBase::clear(IGADepthStencilViewImp* view,Float depth)
{
	glBindFramebuffer(GL_FRAMEBUFFER,mFrameBufferObject);
	glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
	glClearBufferfv(GL_DEPTH,0,&depth);
}

Void NSDevilX::NSCore::NSOpenGL::CGAContextBase::clear(IGADepthStencilViewImp* view,UInt8 stencil)
{
	glBindFramebuffer(GL_FRAMEBUFFER,mFrameBufferObject);
	glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
	UInt32 stencil_value_32=stencil;
	glClearBufferuiv(GL_STENCIL,0,&stencil_value_32);
}

Void NSDevilX::NSCore::NSOpenGL::CGAContextBase::clear(IGADepthStencilViewImp* view,Float depth,UInt8 stencil)
{
	glBindFramebuffer(GL_FRAMEBUFFER,mFrameBufferObject);
	glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
	glClearBufferfi(GL_DEPTH_STENCIL,0,depth,stencil);
}

Void NSDevilX::NSCore::NSOpenGL::CGAContextBase::clear(IGARenderTargetViewImp* view,const Float colourRGBA[4])
{
	glBindFramebuffer(GL_FRAMEBUFFER,mFrameBufferObject);
	glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
	Float gl_clear_colour[4]={colourRGBA[0],colourRGBA[1],colourRGBA[2],colourRGBA[3]};
	glClearBufferfv(GL_COLOR,GL_DRAW_BUFFER0,gl_clear_colour);
}

NSDevilX::NSCore::NSOpenGL::CGAContextGL45::CGAContextGL45()
{
	glCreateFramebuffers(1,&mFrameBufferObject);
	CUtility::checkGLError();
}

NSDevilX::NSCore::NSOpenGL::CGAContextGL45::~CGAContextGL45()
{
}

Void NSDevilX::NSCore::NSOpenGL::CGAContextGL45::clear(IGADepthStencilViewImp* view,Float depth)
{
	glNamedFramebufferTextureLayer(mFrameBufferObject,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
	glClearNamedFramebufferfv(mFrameBufferObject,GL_DEPTH,0,&depth);
}

Void NSDevilX::NSCore::NSOpenGL::CGAContextGL45::clear(IGADepthStencilViewImp* view,UInt8 stencil)
{
	glNamedFramebufferTextureLayer(mFrameBufferObject,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
	UInt32 stencil_value_32=stencil;
	glClearNamedFramebufferuiv(mFrameBufferObject,GL_STENCIL,0,&stencil_value_32);
}

Void NSDevilX::NSCore::NSOpenGL::CGAContextGL45::clear(IGADepthStencilViewImp* view,Float depth,UInt8 stencil)
{
	glNamedFramebufferTextureLayer(mFrameBufferObject,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
	glClearNamedFramebufferfi(mFrameBufferObject,GL_DEPTH_STENCIL,0,depth,stencil);
}

Void NSDevilX::NSCore::NSOpenGL::CGAContextGL45::clear(IGARenderTargetViewImp* view,const Float colourRGBA[4])
{
	glNamedFramebufferTextureLayer(mFrameBufferObject,GL_COLOR_ATTACHMENT0,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
	Float gl_clear_colour[4]={colourRGBA[0],colourRGBA[1],colourRGBA[2],colourRGBA[3]};
	glClearNamedFramebufferfv(mFrameBufferObject,GL_COLOR,GL_DRAW_BUFFER0,gl_clear_colour);
}

NSDevilX::NSCore::NSOpenGL::CGAContextCommon::CGAContextCommon()
{
	glGenFramebuffers(1,&mFrameBufferObject);
	CUtility::checkGLError();
}

NSDevilX::NSCore::NSOpenGL::CGAContextCommon::~CGAContextCommon()
{
}
