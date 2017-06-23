#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CConstantBufferDescriptionManager::CConstantBufferDescriptionManager()
{}

NSDevilX::NSRenderSystem::NSGLES3::CConstantBufferDescriptionManager::~CConstantBufferDescriptionManager()
{
}

Void NSDevilX::NSRenderSystem::NSGLES3::CConstantBufferDescriptionManager::registerDescription(GLuint program,GLuint index)
{
	String block_name;
	block_name.resize(100);
	GLsizei name_length;
	glGetActiveUniformBlockName(program,index,100,&name_length,&block_name[0]);
	CUtility::checkGLError();
	if(mDescriptions.has(block_name.c_str()))
	{
		CConstantBufferDescription * test_desc=mDescriptions.get(block_name.c_str());

		GLint block_size_in_bytes;
		glGetActiveUniformBlockiv(program,index,GL_UNIFORM_BLOCK_DATA_SIZE,&block_size_in_bytes);
		CUtility::checkGLError();
		GLint block_uniform_count;
		glGetActiveUniformBlockiv(program,index,GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,&block_uniform_count);
		CUtility::checkGLError();
		assert(block_size_in_bytes==test_desc->getSizeInBytes());
		assert(block_uniform_count==test_desc->getConstantDescriptions().size());
		TVector<GLint> uniform_indices;
		uniform_indices.resize(block_uniform_count);
		glGetActiveUniformBlockiv(program,index,GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,&uniform_indices[0]);
		CUtility::checkGLError();
		for(GLint i=0;i<block_uniform_count;++i)
		{
			const auto uniform_index=static_cast<GLuint>(uniform_indices[i]);
			String constant_name;
			constant_name.resize(100);
			GLsizei name_length;
			GLint uniform_size;
			GLenum uniform_type=0;
			glGetActiveUniform(program,uniform_index,static_cast<GLsizei>(constant_name.size()),&name_length,&uniform_size,&uniform_type,&constant_name[0]);
			CUtility::checkGLError();
			GLint uniform_offset=0;
			glGetActiveUniformsiv(program,1,&uniform_index,GL_UNIFORM_OFFSET,&uniform_offset);
			CUtility::checkGLError();
			auto test_const_desc=test_desc->getConstantDesc(constant_name.c_str());
			assert(test_const_desc.mOffsetInBytes==uniform_offset);
			assert(test_const_desc.mType==uniform_type);
		}
	}
	else
	{
		mDescriptions.add(block_name.c_str(),DEVILX_NEW CConstantBufferDescription(program,index));
	}
}

CConstantBufferDescription * NSDevilX::NSRenderSystem::NSGLES3::CConstantBufferDescriptionManager::getDescription(const String & constBufferName) const
{
	return mDescriptions.has(constBufferName)?mDescriptions.get(constBufferName):nullptr;
}
