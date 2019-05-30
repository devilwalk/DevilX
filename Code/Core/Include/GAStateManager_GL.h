#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			class CGAStateManager
				:public TBaseObject<CGAStateManager>
			{
			public:
				struct SBufferBindData
					:public TBaseObject<SBufferBindData>
				{
					GLuint mBuffer;
					GLintptr mOffset;
					GLsizeiptr mSize;
					SBufferBindData()
						:mBuffer(0)
						,mOffset(0)
						,mSize(0)
					{ }
					SBufferBindData(GLuint buffer,GLintptr offset=0,GLsizeiptr size=0)
						:mBuffer(buffer)
						,mOffset(offset)
						,mSize(size)
					{
					}
					Boolean operator==(const SBufferBindData& test)const
					{
						return (mBuffer==test.mBuffer)
							&&(mOffset==test.mOffset)
							&&(mSize==test.mSize);
					}
					Boolean operator!=(const SBufferBindData& test)const
					{
						return !(*this==test);
					}
				};
				struct STextureUnit
				{
					GLenum mTarget;
					GLuint mTexture;
					STextureUnit()
						:mTarget(0)
						,mTexture(0)
					{ }
					STextureUnit(GLenum target,GLuint texture)
						:mTarget(target)
						,mTexture(texture)
					{ }
					Boolean operator==(const STextureUnit& test)const
					{
						return (mTarget==test.mTarget)
							&&(mTexture==test.mTexture);
					}
					Boolean operator!=(const STextureUnit& test)const
					{
						return !(*this==test);
					}
				};
			protected:
				GLuint mBindBufferArrayBuffer;
				GLuint mBindBufferElementArrayBuffer;
				GLuint mBindBufferCopyReadBuffer;
				GLuint mBindBufferCopyWriteBuffer;
				GLuint mBindBufferDispatchIndirectBuffer;
				GLuint mBindBufferDrawIndirectBuffer;
				GLuint mBindBufferPixelPackBuffer;
				GLuint mBindBufferPixelUnpackBuffer;
				GLuint mBindBufferQueryBuffer;
				GLuint mBindBufferTextureBuffer;
				std::array<SBufferBindData,128> mBindBufferUniformBuffers;
				std::array<SBufferBindData,128> mBindBufferShaderStorageBuffers;
				std::array<SBufferBindData,128> mBindBufferAtomicCounterBuffers;
				std::array<SBufferBindData,128> mBindBufferTransformFeedBackBuffers;

				GLuint mActiveTexture;
				std::array<STextureUnit,128> mTextureUnits;

				GLuint mBindVertexArray;

				std::array<GLuint,128> mBindSamplers;
			public:
				static CGAStateManager* activeInstance();
				CGAStateManager();
				~CGAStateManager();

				decltype(glBindBuffer(0,0)) bindBuffer(GLenum target,GLuint buffer);
				decltype(glBindBufferBase(0,0,0)) bindBufferBase(GLenum target,GLuint index,GLuint buffer);
				decltype(glBindBufferRange(0,0,0,0,0)) bindBufferRange(GLenum target,GLuint index,GLuint buffer,GLintptr offset,GLsizeiptr size);
				decltype(glBindBuffersBase(0,0,0,0)) bindBuffersBase(GLenum target,GLuint first,GLsizei count,const GLuint* buffers);
				decltype(glBindBuffersRange(0,0,0,0,0,0)) bindBuffersRange(GLenum target,GLuint first,GLsizei count,const GLuint* buffers,const GLintptr* offsets,const GLsizeiptr* sizes);

				decltype(glActiveTexture(0)) activeTexture(GLenum unit);
				decltype(glBindTexture(0,0)) bindTexture(GLenum target,GLuint texture);
				decltype(glBindTextures(0,0,0)) bindTextures(GLuint first,GLsizei count,const GLuint* textures);
				decltype(glBindTextureUnit(0,0)) bindTextureUnit(GLuint unit,GLuint texture);

				decltype(glBindVertexArray(0)) bindVertexArray(GLuint vao);

				decltype(glBindSampler(0,0)) bindSampler(GLuint unit,GLuint sampler);
				decltype(glBindSamplers(0,0,0)) bindSamplers(GLuint first,GLsizei count,const GLuint* samplers);
			};
		}
	}
}