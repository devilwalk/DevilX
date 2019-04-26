#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

NSDevilX::NSCore::NSOpenGL::CGAEnvironment::CGAEnvironment(EGLNativeWindowType window,Bool isGLES)
	:mDisplay(EGL_NO_DISPLAY)
	,mSurface(EGL_NO_SURFACE)
	,mContext(EGL_NO_CONTEXT)
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	EGLNativeDisplayType native_display=GetDC(window);
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
	mDisplay=eglGetDisplay(native_display);
	CUtility::checkEGLError();
	eglInitialize(mDisplay,nullptr,nullptr);
	CUtility::checkEGLError();
	if(isGLES)
		eglBindAPI(EGL_OPENGL_ES_API);
	else
		eglBindAPI(EGL_OPENGL_API);
	CUtility::checkEGLError();
	EGLConfig config=CUtility::chooseConfig(mDisplay);
	CUtility::checkEGLError();
	const EGLint attrib_list[]={
		EGL_GL_COLORSPACE,EGL_GL_COLORSPACE_SRGB,
		EGL_NONE
	};
	mSurface=eglCreateWindowSurface(mDisplay,config,window,attrib_list);
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
	mContext=eglCreateContext(mDisplay,config,EGL_NO_CONTEXT,&context_config_attr_list[0]);
	CUtility::checkEGLError();
#if DEVILX_DEBUG
	if(glDebugMessageCallback)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback([](GLenum source,GLenum type,GLuint id,GLenum serverity,GLsizei length,const GLchar*message,const GLvoid*userParam)
			{
				OutputDebugStringA(message);
				OutputDebugStringA("\r\n");
			},nullptr);
	}
#endif
	eglMakeCurrent(mDisplay,mSurface,mSurface,mContext);
	CUtility::checkEGLError();
}

NSDevilX::NSCore::NSOpenGL::CGAEnvironment::~CGAEnvironment()
{
	eglDestroyContext(mDisplay,mContext);
	eglDestroySurface(mDisplay,mSurface);
}
