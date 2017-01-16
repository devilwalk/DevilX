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
	const GLchar * code_str=&final_code[0];
	glShaderSource(ret,1,&code_str,nullptr);
	glCompileShader(ret);
	if(ret)
	{
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
	const GLchar * code_str=&final_code[0];
	glShaderSource(ret,1,&code_str,nullptr);
	glCompileShader(ret);
	if(ret)
	{
		mShaders.add(key,ret);
	}
	return ret;
}
