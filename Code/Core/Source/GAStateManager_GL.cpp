#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

CGAStateManager* NSDevilX::NSCore::NSOpenGL::CGAStateManager::activeInstance()
{
	return CGAEnvironment::activeInstance()->getStateManager();
}

NSDevilX::NSCore::NSOpenGL::CGAStateManager::CGAStateManager()
	:mBindBufferArrayBuffer(0)
	,mBindBufferElementArrayBuffer(0)
	,mBindBufferCopyReadBuffer(0)
	,mBindBufferCopyWriteBuffer(0)
	,mBindBufferDispatchIndirectBuffer(0)
	,mBindBufferDrawIndirectBuffer(0)
	,mBindBufferPixelPackBuffer(0)
	,mBindBufferPixelUnpackBuffer(0)
	,mBindBufferQueryBuffer(0)
	,mBindBufferTextureBuffer(0)
	,mActiveTexture(0)
	,mBindVertexArray(0)
{
	memset(&mBindSamplers[0],0,mBindSamplers.size()*sizeof(mBindSamplers[0]));
}

NSDevilX::NSCore::NSOpenGL::CGAStateManager::~CGAStateManager()
{
}

decltype(glBindBuffer(0,0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::bindBuffer(GLenum target,GLuint buffer)
{
	GLuint* test_buffer=nullptr;
	switch(target)
	{
	case GL_ARRAY_BUFFER:
		test_buffer=&mBindBufferArrayBuffer;
		break;
	case GL_ELEMENT_ARRAY_BUFFER:
		test_buffer=&mBindBufferElementArrayBuffer;
		break;
	case GL_DRAW_INDIRECT_BUFFER:
		test_buffer=&mBindBufferDrawIndirectBuffer;
		break;
	case GL_DISPATCH_INDIRECT_BUFFER:
		test_buffer=&mBindBufferDispatchIndirectBuffer;
		break;
	case GL_TEXTURE_BUFFER:
		test_buffer=&mBindBufferTextureBuffer;
		break;
	case GL_QUERY_BUFFER:
		test_buffer=&mBindBufferQueryBuffer;
		break;
	case GL_COPY_READ_BUFFER:
		test_buffer=&mBindBufferCopyReadBuffer;
		break;
	case GL_COPY_WRITE_BUFFER:
		test_buffer=&mBindBufferCopyWriteBuffer;
		break;
	case GL_PIXEL_PACK_BUFFER:
		test_buffer=&mBindBufferPixelPackBuffer;
		break;
	case GL_PIXEL_UNPACK_BUFFER:
		test_buffer=&mBindBufferPixelUnpackBuffer;
		break;
	default:
		assert(0);
	}
	auto& ref_test_buffer=*test_buffer;
	if(ref_test_buffer!=buffer)
	{
		glBindBuffer(target,buffer);
		CUtility::checkGLError();
		ref_test_buffer=buffer;
	}
}

decltype(glBindBufferBase(0,0,0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::bindBufferBase(GLenum target,GLuint index,GLuint buffer)
{
	SBufferBindData * test_buffer=nullptr;
	switch(target)
	{
	case GL_UNIFORM_BUFFER:
		test_buffer=&mBindBufferUniformBuffers[0];
		break;
	case GL_SHADER_STORAGE_BUFFER:
		test_buffer=&mBindBufferShaderStorageBuffers[0];
		break;
	case GL_ATOMIC_COUNTER_BUFFER:
		test_buffer=&mBindBufferAtomicCounterBuffers[0];
		break;
	case GL_TRANSFORM_FEEDBACK_BUFFER:
		test_buffer=&mBindBufferTransformFeedBackBuffers[0];
		break;
	default:
		assert(0);
	}
	SBufferBindData new_buffer(buffer);
	auto& ref_test_buffer=*(test_buffer+index);
	if(ref_test_buffer!=new_buffer)
	{
		glBindBufferBase(target,index,buffer);
		CUtility::checkGLError();
		ref_test_buffer=new_buffer;
	}
}

decltype(glBindBufferRange(0,0,0,0,0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::bindBufferRange(GLenum target,GLuint index,GLuint buffer,GLintptr offset,GLsizeiptr size)
{
	SBufferBindData* test_buffer=nullptr;
	switch(target)
	{
	case GL_UNIFORM_BUFFER:
		test_buffer=&mBindBufferUniformBuffers[0];
		break;
	case GL_SHADER_STORAGE_BUFFER:
		test_buffer=&mBindBufferShaderStorageBuffers[0];
		break;
	case GL_ATOMIC_COUNTER_BUFFER:
		test_buffer=&mBindBufferAtomicCounterBuffers[0];
		break;
	case GL_TRANSFORM_FEEDBACK_BUFFER:
		test_buffer=&mBindBufferTransformFeedBackBuffers[0];
		break;
	default:
		assert(0);
	}
	SBufferBindData new_buffer(buffer,offset,size);
	auto& ref_test_buffer=*(test_buffer+index);
	if(ref_test_buffer!=new_buffer)
	{
		glBindBufferBase(target,index,buffer);
		CUtility::checkGLError();
		ref_test_buffer=new_buffer;
	}
}

decltype(glBindBuffersBase(0,0,0,0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::bindBuffersBase(GLenum target,GLuint first,GLsizei count,const GLuint* buffers)
{
	SBufferBindData* test_buffer=nullptr;
	switch(target)
	{
	case GL_UNIFORM_BUFFER:
		test_buffer=&mBindBufferUniformBuffers[0];
		break;
	case GL_SHADER_STORAGE_BUFFER:
		test_buffer=&mBindBufferShaderStorageBuffers[0];
		break;
	case GL_ATOMIC_COUNTER_BUFFER:
		test_buffer=&mBindBufferAtomicCounterBuffers[0];
		break;
	case GL_TRANSFORM_FEEDBACK_BUFFER:
		test_buffer=&mBindBufferTransformFeedBackBuffers[0];
		break;
	default:
		assert(0);
	}
	Boolean changed=false;
	for(GLsizei i=0;i<count;++i)
	{
		auto& ref_test_buffer=test_buffer[first+i];
		SBufferBindData new_buffer(buffers[i]);
		if(ref_test_buffer!=new_buffer)
		{
			changed=true;
			break;
		}
	}
	if(changed)
	{
		glBindBuffersBase(target,first,count,buffers);
		CUtility::checkGLError();
		for(GLsizei i=0;i<count;++i)
		{
			auto& ref_test_buffer=test_buffer[first+i];
			ref_test_buffer=SBufferBindData(buffers[i]);
		}
	}
}

decltype(glBindBuffersRange(0,0,0,0,0,0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::bindBuffersRange(GLenum target,GLuint first,GLsizei count,const GLuint* buffers,const GLintptr* offsets,const GLsizeiptr* sizes)
{
	SBufferBindData* test_buffer=nullptr;
	switch(target)
	{
	case GL_UNIFORM_BUFFER:
		test_buffer=&mBindBufferUniformBuffers[0];
		break;
	case GL_SHADER_STORAGE_BUFFER:
		test_buffer=&mBindBufferShaderStorageBuffers[0];
		break;
	case GL_ATOMIC_COUNTER_BUFFER:
		test_buffer=&mBindBufferAtomicCounterBuffers[0];
		break;
	case GL_TRANSFORM_FEEDBACK_BUFFER:
		test_buffer=&mBindBufferTransformFeedBackBuffers[0];
		break;
	default:
		assert(0);
	}
	Boolean changed=false;
	for(GLsizei i=0;i<count;++i)
	{
		auto& ref_test_buffer=test_buffer[first+i];
		SBufferBindData new_buffer(buffers[i],offsets[i],sizes[i]);
		if(ref_test_buffer!=new_buffer)
		{
			changed=true;
			break;
		}
	}
	if(changed)
	{
		glBindBuffersRange(target,first,count,buffers,offsets,sizes);
		CUtility::checkGLError();
		for(GLsizei i=0;i<count;++i)
		{
			auto& ref_test_buffer=test_buffer[first+i];
			ref_test_buffer=SBufferBindData(buffers[i],offsets[i],sizes[i]);
		}
	}
}

decltype(glActiveTexture(0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::activeTexture(GLenum unit)
{
	if(mActiveTexture!=unit)
	{
		glActiveTexture(unit);
		mActiveTexture=unit;
	}
}

decltype(glBindTexture(0,0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::bindTexture(GLenum target,GLuint texture)
{
	STextureUnit new_tex(target,texture);
	auto& ref_test_tex=mTextureUnits[mActiveTexture-GL_TEXTURE0];
	if(ref_test_tex!=new_tex)
	{
		glBindTexture(target,texture);
		CUtility::checkGLError();
		ref_test_tex=new_tex;
	}
}

decltype(glBindTextures(0,0,0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::bindTextures(GLuint first,GLsizei count,const GLuint* textures)
{
	Boolean changed=false;
	for(GLsizei i=0;i<count;++i)
	{
		auto& ref_test_tex=mTextureUnits[first+i];
		if(ref_test_tex.mTexture!=textures[i])
		{
			changed=true;
			break;
		}
	}
	if(changed)
	{
		glBindTextures(first,count,textures);
		CUtility::checkGLError();
		for(GLsizei i=0;i<count;++i)
		{
			auto& ref_test_tex=mTextureUnits[first+i];
			ref_test_tex.mTexture=textures[i];
		}
	}
}

decltype(glBindTextureUnit(0,0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::bindTextureUnit(GLuint unit,GLuint texture)
{
	if(mTextureUnits[unit-GL_TEXTURE0].mTexture!=texture)
	{
		glBindTextureUnit(unit,texture);
		CUtility::checkGLError();
		mTextureUnits[unit-GL_TEXTURE0].mTexture=texture;
	}
}

decltype(glBindVertexArray(0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::bindVertexArray(GLuint vao)
{
	if(mBindVertexArray!=vao)
	{
		glBindVertexArray(vao);
		CUtility::checkGLError();
		mBindVertexArray=vao;
	}
}

decltype(glBindSampler(0,0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::bindSampler(GLuint unit,GLuint sampler)
{
	if(mBindSamplers[unit]!=sampler)
	{
		glBindSampler(unit,sampler);
		CUtility::checkGLError();
		mBindSamplers[unit]=sampler;
	}
}

decltype(glBindSamplers(0,0,0)) NSDevilX::NSCore::NSOpenGL::CGAStateManager::bindSamplers(GLuint first,GLsizei count,const GLuint* samplers)
{
	Boolean changed=false;
	for(GLsizei i=0;i<count;++i)
	{
		if(mBindSamplers[first+i]!=samplers[i])
		{
			changed=true;
			break;
		}
	}
	if(changed)
	{
		glBindSamplers(first,count,samplers);
		CUtility::checkGLError();
		memcpy(&mBindSamplers[first],samplers,count*sizeof(mBindSamplers[0]));
	}
}
