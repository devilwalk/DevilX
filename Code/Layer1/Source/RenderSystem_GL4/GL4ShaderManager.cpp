#include "Precompiler.h"
NSDevilX::NSRenderSystem::NSGL4::CShaderManager::CShaderManager()
{}

NSDevilX::NSRenderSystem::NSGL4::CShaderManager::~CShaderManager()
{
	for(auto const & code_pair:mShaders)
		glDeleteShader(code_pair.second);
}

GLuint NSDevilX::NSRenderSystem::NSGL4::CShaderManager::registerVertexShader(const String & key,const String & code,const MacroDefines & macros)
{
	String macro_string;
	for(auto macro:macros)
		macro_string+="#define "+macro.first+" "+macro.second+"\r\n\\";
	String final_code=macro_string+code;
	GLuint ret=0;
	ret=glCreateShader(GL_VERTEX_SHADER);
	if(ret)
	{
		const GLchar * code_str=&final_code[0];
		glShaderSource(ret,1,&code_str,nullptr);
		glCompileShader(ret);
		GLint compiler_status=GL_FALSE;
		glGetShaderiv(ret,GL_COMPILE_STATUS,&compiler_status);
		if(GL_TRUE!=compiler_status)
		{
			String shader_log;
			shader_log.resize(1024);
			glGetShaderInfoLog(ret,1024,nullptr,&shader_log[0]);
#ifdef DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
			OutputDebugStringA((key+" log:"+shader_log+"\r\n").c_str());
#endif
#endif
		}
		mShaders.add(key,ret);
	}
	return ret;
}

GLuint NSDevilX::NSRenderSystem::NSGL4::CShaderManager::registerPixelShader(const String & key,const String & code,const MacroDefines & macros)
{
	String macro_string;
	for(auto macro:macros)
		macro_string+="#define "+macro.first+" "+macro.second+"\r\n\\";
	String final_code=macro_string+code;
	GLuint ret=0;
	ret=glCreateShader(GL_FRAGMENT_SHADER);
	if(ret)
	{
		const GLchar * code_str=&final_code[0];
		glShaderSource(ret,1,&code_str,nullptr);
		glCompileShader(ret);
		GLint compiler_status=GL_FALSE;
		glGetShaderiv(ret,GL_COMPILE_STATUS,&compiler_status);
		if(GL_TRUE!=compiler_status)
		{
			String shader_log;
			shader_log.resize(1024);
			glGetShaderInfoLog(ret,1024,nullptr,&shader_log[0]);
#ifdef DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
			OutputDebugStringA((key+" log:"+shader_log+"\r\n").c_str());
#endif
#endif
		}
		mShaders.add(key,ret);
	}
	return ret;
}
