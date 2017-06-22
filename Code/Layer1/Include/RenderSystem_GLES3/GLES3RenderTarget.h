#pragma once
#include "GLES3ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CRenderTarget
				:public TBaseObject<CRenderTarget>
				,public CConstantBufferContainer
			{
			protected:
				GLuint mFrameBuffer;
				GLuint mRenderTargets[8];
				GLuint mDepthStencil;
				GLsizei mWidth;
				GLsizei mHeight;
			public:
				CRenderTarget();
				~CRenderTarget();
				GLuint getFrameBuffer()const
				{
					return mFrameBuffer;
				}
				Void setSize(GLsizei width,GLsizei height)
				{
					mWidth=width;
					mHeight=height;
				}
				GLsizei getWidth()const
				{
					return mWidth;
				}
				GLsizei getHeight()const
				{
					return mHeight;
				}
				Void setRT(UInt32 index,GLuint texture);
				GLuint getRT(UInt32 index)const
				{
					return mRenderTargets[index];
				}
				Void setDS(GLuint ds);
				GLuint getDS()const
				{
					return mDepthStencil;
				}
				Void clear(UInt32 index,const CColour & colour);
				Void clear(Float depth,Int32 stencil);
				Void setup();
			protected:
				Void _updateFrameBuffer();
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}