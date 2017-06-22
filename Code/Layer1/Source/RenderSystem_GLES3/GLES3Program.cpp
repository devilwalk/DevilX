#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CProgram::CProgram(GLuint vertexShader,GLuint pixelShader)
	:mHandle(0)
{
	memset(mInputSlots,-1,sizeof(mInputSlots));
	mHandle=glCreateProgram();
	CUtility::checkGLError();
	glAttachShader(getInternal(),vertexShader);
	CUtility::checkGLError();
	glAttachShader(getInternal(),pixelShader);
	CUtility::checkGLError();
	glLinkProgram(getInternal());
	CUtility::checkGLError();
	GLint link_status=GL_FALSE;
	glGetProgramiv(getInternal(),GL_LINK_STATUS,&link_status);
	if(GL_TRUE!=link_status)
	{
		String shader_log;
		shader_log.resize(1024);
		glGetProgramInfoLog(getInternal(),1024,nullptr,&shader_log[0]);
		CUtility::checkGLError();
#ifdef DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
		OutputDebugStringA(("program log:"+shader_log).c_str());
		OutputDebugStringA("\r\n");
#endif
#endif
	}
	GLint num=0;
	glGetProgramiv(getInternal(),GL_ACTIVE_ATTRIBUTES,&num);
	CUtility::checkGLError();
	for(GLint i=0;i<num;++i)
	{
		String input_name;
		input_name.resize(100);
		GLsizei name_length=0;;
		GLint size=0;
		GLenum type=0;
		glGetActiveAttrib(getInternal(),i,100,&name_length,&size,&type,&input_name[0]);
		CUtility::checkGLError();
		const String name=input_name.c_str();
		const auto location=glGetProgramResourceLocation(getInternal(),GL_PROGRAM_INPUT,input_name.c_str());
		CUtility::checkGLError();
		if("gPositionVS"==name)
		{
			mInputSlots[location]=CEnum::EVertexBufferType_Position;
		}
		else if("gNormalVS"==name)
		{
			mInputSlots[location]=CEnum::EVertexBufferType_Normal;
		}
		else if("gMainUVVS"==name)
		{
			mInputSlots[location]=CEnum::EVertexBufferType_TextureCoord0;
		}
		else if("gTangentVS"==name)
		{
			mInputSlots[location]=CEnum::EVertexBufferType_Tangent;
		}
		else if("gDiffuseVS"==name)
		{
			mInputSlots[location]=CEnum::EVertexBufferType_Diffuse;
		}
		else if("gl_VertexID"==name)
		{

		}
		else
		{
			assert(0);
		}
	}
	glGetProgramiv(getInternal(),GL_ACTIVE_UNIFORM_BLOCKS,&num);
	CUtility::checkGLError();
	for(GLint i=0;i<num;++i)
	{
		String cbuffer_name;
		cbuffer_name.resize(100);
		GLsizei name_length;
		glGetActiveUniformBlockName(getInternal(),i,100,&name_length,&cbuffer_name[0]);
		CUtility::checkGLError();
		GLint bind_pos=0;
		glGetActiveUniformBlockiv(getInternal(),i,GL_UNIFORM_BLOCK_BINDING,&bind_pos);
		CUtility::checkGLError();
		mResourceSlots[cbuffer_name.c_str()]=static_cast<UInt32>(bind_pos);
		CSystemImp::getSingleton().getConstantBufferDescriptionManager()->registerDescription(getInternal(),i);
	}
	glGetProgramiv(getInternal(),GL_ACTIVE_UNIFORMS,&num);
	CUtility::checkGLError();
	for(GLint i=0;i<num;++i)
	{
		String cbuffer_name;
		cbuffer_name.resize(100);
		GLsizei name_length;
		GLint size;
		GLenum type;
		glGetActiveUniform(getInternal(),i,100,&name_length,&size,&type,&cbuffer_name[0]);
		CUtility::checkGLError();
		switch(type)
		{
		case GL_SAMPLER_2D:
			GLint bind_pos=glGetUniformLocation(getInternal(),cbuffer_name.c_str());
			CUtility::checkGLError();
			mResourceSlots[cbuffer_name.c_str()]=static_cast<UInt32>(bind_pos);
		}
	}
}

NSDevilX::NSRenderSystem::NSGLES3::CProgram::~CProgram()
{
	glDeleteProgram(getInternal());
	CUtility::checkGLError();
}

UInt32 NSDevilX::NSRenderSystem::NSGLES3::CProgram::getSlot(const String & name) const
{
	return mResourceSlots.has(name)?mResourceSlots.get(name):-1;
}