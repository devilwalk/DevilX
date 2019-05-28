#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

NSDevilX::NSCore::NSOpenGL::CGAEnvironment::CGAEnvironment(EGLNativeWindowType window,Bool isGLES)
	:mDisplay(EGL_NO_DISPLAY)
	,mSurface(EGL_NO_SURFACE)
	,mContext(EGL_NO_CONTEXT)
	,mMultiImp(nullptr)
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
	if(GLEW_VERSION_4_0)
	{
		config_attr_map[EGL_CONTEXT_MAJOR_VERSION]=4;
	}
	else if(GLEW_VERSION_3_0)
	{
		config_attr_map[EGL_CONTEXT_MAJOR_VERSION]=3;
	}
	else if(GLEW_VERSION_2_0)
	{
		config_attr_map[EGL_CONTEXT_MAJOR_VERSION]=2;
	}
	else
	{
		config_attr_map[EGL_CONTEXT_MAJOR_VERSION]=1;
	}
	if(GLEW_VERSION_4_6)
	{
		config_attr_map[EGL_CONTEXT_MINOR_VERSION]=6;
	}
	else if(GLEW_VERSION_1_5||GLEW_VERSION_4_5)
	{
		config_attr_map[EGL_CONTEXT_MINOR_VERSION]=5;
	}
	else if(GLEW_VERSION_1_4||GLEW_VERSION_4_4)
	{
		config_attr_map[EGL_CONTEXT_MINOR_VERSION]=4;
	}
	else if(GLEW_VERSION_1_3||GLEW_VERSION_3_3||GLEW_VERSION_4_3)
	{
		config_attr_map[EGL_CONTEXT_MINOR_VERSION]=3;
	}
	else if(GLEW_VERSION_1_2||GLEW_VERSION_3_2||GLEW_VERSION_4_2)
	{
		config_attr_map[EGL_CONTEXT_MINOR_VERSION]=2;
	}
	else if(GLEW_VERSION_1_1||GLEW_VERSION_2_1||GLEW_VERSION_3_1||GLEW_VERSION_4_1)
	{
		config_attr_map[EGL_CONTEXT_MINOR_VERSION]=1;
	}
	else if(GLEW_VERSION_2_0||GLEW_VERSION_3_0||GLEW_VERSION_4_0)
	{
		config_attr_map[EGL_CONTEXT_MINOR_VERSION]=0;
	}

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
	if(GLEW_VERSION_4_5)
	{
		mMultiImp.reset(DEVILX_NEW CGAEnvironmentGL45(this));
	}
	else if(GLEW_VERSION_4_1)
	{
		mMultiImp.reset(DEVILX_NEW CGAEnvironmentGL41(this));
	}
	else
	{
		mMultiImp.reset(DEVILX_NEW CGAEnvironmentCommon(this));
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

NSDevilX::NSCore::NSOpenGL::CGAEnvironmentMultiImp::CGAEnvironmentMultiImp(CGAEnvironment* environment)
	:mEnvironment(environment)
	,mFrameBufferObject(0)
{
	glGenFramebuffers(1,&mFrameBufferObject);
	CUtility::checkGLError();
}

NSDevilX::NSCore::NSOpenGL::CGAEnvironmentMultiImp::~CGAEnvironmentMultiImp()
{
	glDeleteFramebuffers(1,&mFrameBufferObject);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentMultiImp::clear(IGADepthStencilViewImp* view,Float depth)
{
	if(view)
	{
		glBindFramebuffer(GL_FRAMEBUFFER,mFrameBufferObject);
		CUtility::checkGLError();
		glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
		CUtility::checkGLError();
	}
	glClearBufferfv(GL_DEPTH,0,&depth);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentMultiImp::clear(IGADepthStencilViewImp* view,UInt8 stencil)
{
	if(view)
	{
		glBindFramebuffer(GL_FRAMEBUFFER,mFrameBufferObject);
		CUtility::checkGLError();
		glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
		CUtility::checkGLError();
	}
	UInt32 stencil_value_32=stencil;
	glClearBufferuiv(GL_STENCIL,0,&stencil_value_32);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentMultiImp::clear(IGADepthStencilViewImp* view,Float depth,UInt8 stencil)
{
	if(view)
	{
		glBindFramebuffer(GL_FRAMEBUFFER,mFrameBufferObject);
		CUtility::checkGLError();
		glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
		CUtility::checkGLError();
	}
	glClearBufferfi(GL_DEPTH_STENCIL,0,depth,stencil);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentMultiImp::clear(IGARenderTargetViewImp* view,const Float colourRGBA[4])
{
	if(view)
	{
		glBindFramebuffer(GL_FRAMEBUFFER,mFrameBufferObject);
		CUtility::checkGLError();
		glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
		CUtility::checkGLError();
	}
	Float gl_clear_colour[4]={colourRGBA[0],colourRGBA[1],colourRGBA[2],colourRGBA[3]};
	glClearBufferfv(GL_COLOR,0,gl_clear_colour);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentMultiImp::setRenderTarget(UInt32 index,IGARenderTargetViewImp* view)
{
	glBindFramebuffer(GL_FRAMEBUFFER,mFrameBufferObject);
	CUtility::checkGLError();
	glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0+index,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentMultiImp::setDepthStencil(IGADepthStencilViewImp* view)
{
	glBindFramebuffer(GL_FRAMEBUFFER,mFrameBufferObject);
	CUtility::checkGLError();
	glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentMultiImp::setShader(IGAShaderImp* shader,IGAProgramParameterImp* parameter)
{
	assert(0);
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentMultiImp::setProgram(CGAProgramImp* program,IGAProgramParameterImp* parameter)
{
	glUseProgram(program->getInternal());
	CUtility::checkGLError();
	glBindBuffersBase(GL_UNIFORM_BUFFER,0,static_cast<GLsizei>(parameter->getConstantBuffers().size()),&parameter->getConstantBuffers()[0]);
	CUtility::checkGLError();
	glBindSamplers(0, static_cast<GLsizei>(parameter->getSamplers().size()),&parameter->getSamplers()[0]);
	CUtility::checkGLError();
	glBindTextures(0, static_cast<GLsizei>(parameter->getTextures().size()),&parameter->getTextures()[0]);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentMultiImp::update(IGABufferImp* buffer,ConstVoidPtr data,UInt32 updateOffsetInBytes,UInt32 updateSizeInBytes)
{
	glBindBuffer(GL_ARRAY_BUFFER,static_cast<IGABufferImp*>(buffer)->getInternal());
	CUtility::checkGLError();
	glBufferSubData(GL_ARRAY_BUFFER,updateOffsetInBytes,updateSizeInBytes,data);
	CUtility::checkGLError();
	glBindBuffer(GL_ARRAY_BUFFER,0);
	CUtility::checkGLError();
}

NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL45Base::CGAEnvironmentGL45Base(CGAEnvironment* environment)
	:CGAEnvironmentGL41Base(environment)
{
	glDeleteProgramPipelines(1,&mPipeline);
	CUtility::checkGLError();
	glCreateProgramPipelines(1,&mPipeline);
	CUtility::checkGLError();
	glDeleteFramebuffers(1,&mFrameBufferObject);
	CUtility::checkGLError();
	glCreateFramebuffers(1,&mFrameBufferObject);
	CUtility::checkGLError();
}

NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL45Base::~CGAEnvironmentGL45Base()
{
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL45Base::clear(IGADepthStencilViewImp* view,Float depth)
{
	GLuint fbo=0;
	if(view)
	{
		fbo=mFrameBufferObject;
		glNamedFramebufferTextureLayer(fbo,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
		CUtility::checkGLError();
	}
	glClearNamedFramebufferfv(fbo,GL_DEPTH,0,&depth);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL45Base::clear(IGADepthStencilViewImp* view,UInt8 stencil)
{
	GLuint fbo=0;
	if(view)
	{
		fbo=mFrameBufferObject;
		glNamedFramebufferTextureLayer(fbo,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
		CUtility::checkGLError();
	}
	UInt32 stencil_value_32=stencil;
	glClearNamedFramebufferuiv(fbo,GL_STENCIL,0,&stencil_value_32);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL45Base::clear(IGADepthStencilViewImp* view,Float depth,UInt8 stencil)
{
	GLuint fbo=0;
	if(view)
	{
		fbo=mFrameBufferObject;
		glNamedFramebufferTextureLayer(fbo,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
		CUtility::checkGLError();
	}
	glClearNamedFramebufferfi(fbo,GL_DEPTH_STENCIL,0,depth,stencil);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL45Base::clear(IGARenderTargetViewImp* view,const Float colourRGBA[4])
{
	Float gl_clear_colour[4]={colourRGBA[0],colourRGBA[1],colourRGBA[2],colourRGBA[3]};
	GLuint fbo=0;
	if(view)
	{
		fbo=mFrameBufferObject;
		glNamedFramebufferTextureLayer(fbo,GL_COLOR_ATTACHMENT0,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
		CUtility::checkGLError();
	}
	glClearNamedFramebufferfv(fbo,GL_COLOR,0,gl_clear_colour);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL45Base::setRenderTarget(UInt32 index,IGARenderTargetViewImp* view)
{
	GLuint fbo=0;
	if(view)
	{
		fbo=mFrameBufferObject;
		glNamedFramebufferTextureLayer(fbo,GL_COLOR_ATTACHMENT0+index,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
		CUtility::checkGLError();
	}
	glBindFramebuffer(GL_FRAMEBUFFER,fbo);
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL45Base::setDepthStencil(IGADepthStencilViewImp* view)
{
	GLuint fbo=0;
	if(view)
	{
		fbo=mFrameBufferObject;
		glNamedFramebufferTextureLayer(fbo,GL_DEPTH_STENCIL_ATTACHMENT,view->getTexture(),view->getMipLevel(),view->getArrayIndex());
		CUtility::checkGLError();
	}
	glBindFramebuffer(GL_FRAMEBUFFER,fbo);
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL45Base::setShader(IGAShaderImp* shader,IGAProgramParameterImp* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL45Base::update(IGABufferImp* buffer,ConstVoidPtr data,UInt32 updateOffsetInBytes,UInt32 updateSizeInBytes)
{
	glNamedBufferSubData(static_cast<IGABufferImp*>(buffer)->getInternal(),updateOffsetInBytes,updateSizeInBytes,data);
	CUtility::checkGLError();
}

NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL41Base::CGAEnvironmentGL41Base(CGAEnvironment* environment)
	:CGAEnvironmentMultiImp(environment)
	,mPipeline(0)
{
	glGenProgramPipelines(1,&mPipeline);
	CUtility::checkGLError();
}

NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL41Base::~CGAEnvironmentGL41Base()
{
	glDeleteProgramPipelines(1,&mPipeline);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGAEnvironmentGL41Base::setShader(IGAShaderImp* shader,IGAProgramParameterImp* parameter)
{
	return Void();
}
