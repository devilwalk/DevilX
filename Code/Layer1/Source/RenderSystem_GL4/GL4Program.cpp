#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CProgram::CProgram(GLuint vertexShader,GLuint pixelShader)
	:mHandle(0)
{
	memset(mInputSlots,-1,sizeof(mInputSlots));
	mHandle=glCreateProgram();
	glAttachShader(getInternal(),vertexShader);
	glAttachShader(getInternal(),pixelShader);
	glLinkProgram(getInternal());
	GLint link_status=GL_FALSE;
	glGetProgramiv(getInternal(),GL_LINK_STATUS,&link_status);
	if(GL_TRUE!=link_status)
	{
		String shader_log;
		shader_log.resize(1024);
		glGetProgramInfoLog(getInternal(),1024,nullptr,&shader_log[0]);
#ifdef DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
		OutputDebugStringA(("program log:"+shader_log+"\r\n").c_str());
#endif
#endif
	}
	GLint num=0;
	glGetProgramiv(getInternal(),GL_ACTIVE_ATTRIBUTES,&num);
	for(GLint i=0;i<num;++i)
	{
		String input_name;
		input_name.resize(100);
		GLsizei name_length=0;;
		GLint size=0;
		GLenum type=0;
		glGetActiveAttrib(getInternal(),i,100,&name_length,&size,&type,&input_name[0]);
		const String name=input_name.c_str();
		const auto location=glGetProgramResourceLocation(getInternal(),GL_PROGRAM_INPUT,input_name.c_str());
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
	for(GLint i=0;i<num;++i)
	{
		String cbuffer_name;
		cbuffer_name.resize(100);
		GLsizei name_length;
		glGetActiveUniformBlockName(getInternal(),i,100,&name_length,&cbuffer_name[0]);
		GLint bind_pos=0;
		glGetActiveUniformBlockiv(getInternal(),i,GL_UNIFORM_BLOCK_BINDING,&bind_pos);
		mResourceSlots[cbuffer_name.c_str()]=static_cast<UInt32>(bind_pos);
		CSystemImp::getSingleton().getConstantBufferDescriptionManager()->registerDescription(getInternal(),i);
	}
}

NSDevilX::NSRenderSystem::NSGL4::CProgram::~CProgram()
{
	glDeleteProgram(getInternal());
}

UInt32 NSDevilX::NSRenderSystem::NSGL4::CProgram::getSlot(const String & name) const
{
	return mResourceSlots.has(name)?mResourceSlots.get(name):-1;
}