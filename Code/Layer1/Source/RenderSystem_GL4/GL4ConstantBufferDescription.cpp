#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CConstantBufferDescription::CConstantBufferDescription(GLuint program,GLuint index)
{
	{
		String block_name;
		block_name.resize(100);
		GLsizei name_length;
		glGetActiveUniformBlockName(program,index,100,&name_length,&block_name[0]);
		mName=block_name.c_str();
	}
	{
		GLint block_size_in_bytes;
		glGetActiveUniformBlockiv(program,index,GL_UNIFORM_BLOCK_DATA_SIZE,&block_size_in_bytes);
		mSizeInBytes=static_cast<UInt32>(block_size_in_bytes);
		GLint block_uniform_count;
		glGetActiveUniformBlockiv(program,index,GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,&block_uniform_count);
		TVector<GLint> uniform_indices;
		uniform_indices.resize(block_uniform_count);
		glGetActiveUniformBlockiv(program,index,GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,&uniform_indices[0]);
		for(GLint i=0;i<block_uniform_count;++i)
		{
			const auto uniform_index=static_cast<GLuint>(uniform_indices[i]);
			String constant_name;
			constant_name.resize(100);
			GLsizei name_length;
			glGetActiveUniformName(program,uniform_index,static_cast<GLsizei>(constant_name.size()),&name_length,&constant_name[0]);
			GLint uniform_offset=0;
			glGetActiveUniformsiv(program,1,&uniform_index,GL_UNIFORM_OFFSET,&uniform_offset);
			GLint uniform_type=0;
			glGetActiveUniformsiv(program,1,&uniform_index,GL_UNIFORM_TYPE,&uniform_type);
			SConstant constant;
			constant.mName=constant_name.c_str();
			constant.mOffsetInBytes=static_cast<decltype(constant.mOffsetInBytes)>(uniform_offset);
			constant.mType=static_cast<decltype(constant.mType)>(uniform_type);
			mConstantDescriptions.add(constant.mName,constant);
		}
	}
}

NSDevilX::NSRenderSystem::NSGL4::CConstantBufferDescription::~CConstantBufferDescription()
{}
