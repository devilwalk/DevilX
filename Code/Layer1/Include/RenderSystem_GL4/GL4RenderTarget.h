#pragma once
#include "GL4ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CRenderTarget
				:public TBaseObject<CRenderTarget>
				,public CConstantBufferContainer
			{
			protected:
				GLuint mFrameBuffer;
				GLuint mRenderTargets[8];
				GLuint mDepthStencil;
			public:
				CRenderTarget();
				~CRenderTarget();
				Void getSize(GLsizei & width,GLsizei & height);
				Void setRT(UInt32 index,GLuint texture);
				GLuint getRT(UInt32 index)const
				{
					return mRenderTargets[index];
				}
				Void setDS(GLuint texture);
				GLuint getDS()const
				{
					return mDepthStencil;
				}
				Void clear(UInt32 index,const CColour & colour);
				Void clear(Float depth,Int32 stencil);
				Void setup();
			protected:
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}