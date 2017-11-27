#include "Precompiler.h"
NSDevilX::NSRenderSystem::NSGLES3::CShaderManager::CShaderManager()
{}

NSDevilX::NSRenderSystem::NSGLES3::CShaderManager::~CShaderManager()
{
	for(auto const & code_pair:mShaders)
	{
		glDeleteShader(code_pair.second);
		CUtility::checkGLError();
	}
}

GLuint NSDevilX::NSRenderSystem::NSGLES3::CShaderManager::registerVertexShader(const String & key,const String & code,const MacroDefines & macros)
{
	String macro_string="#version 310 es\r\n";
	macro_string+="#define GLSLES_VERSION 310\r\n";
	for(auto macro:macros)
		macro_string+="#define "+macro.first+" "+macro.second+"\r\n";
	String final_code=macro_string+code;
	GLuint ret=0;
	ret=glCreateShader(GL_VERTEX_SHADER);
	CUtility::checkGLError();
	if(ret)
	{
		const GLchar * code_str=&final_code[0];
		glShaderSource(ret,1,&code_str,nullptr);
		CUtility::checkGLError();
		glCompileShader(ret);
		CUtility::checkGLError();
		GLint compiler_status=GL_FALSE;
		glGetShaderiv(ret,GL_COMPILE_STATUS,&compiler_status);
		CUtility::checkGLError();
		if(GL_TRUE!=compiler_status)
		{
			String shader_log;
			shader_log.resize(1024);
			glGetShaderInfoLog(ret,1024,nullptr,&shader_log[0]);
			CUtility::checkGLError();
#if DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
			OutputDebugStringA((key+" log:"+shader_log).c_str());
			OutputDebugStringA("\r\n");
#endif
#endif
		}
		mShaders.add(key,ret);
	}
	return ret;
}

GLuint NSDevilX::NSRenderSystem::NSGLES3::CShaderManager::registerPixelShader(const String & key,const String & code,const MacroDefines & macros)
{
	String macro_string="#version 310 es\r\n";
	macro_string+="#define GLSLES_VERSION 310\r\n";
	macro_string+="precision highp float;\r\n";
	for(auto macro:macros)
		macro_string+="#define "+macro.first+" "+macro.second+"\r\n";
	String final_code=macro_string+code;
	GLuint ret=0;
	ret=glCreateShader(GL_FRAGMENT_SHADER);
	CUtility::checkGLError();
	if(ret)
	{
		const GLchar * code_str=&final_code[0];
		glShaderSource(ret,1,&code_str,nullptr);
		CUtility::checkGLError();
		glCompileShader(ret);
		CUtility::checkGLError();
		GLint compiler_status=GL_FALSE;
		glGetShaderiv(ret,GL_COMPILE_STATUS,&compiler_status);
		CUtility::checkGLError();
		if(GL_TRUE!=compiler_status)
		{
			String shader_log;
			shader_log.resize(1024);
			glGetShaderInfoLog(ret,1024,nullptr,&shader_log[0]);
			CUtility::checkGLError();
#if DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
			OutputDebugStringA((key+" log:"+shader_log).c_str());
			OutputDebugStringA("\r\n");
#endif
#endif
		}
		mShaders.add(key,ret);
	}
	return ret;
}
