#pragma once
#include "GLES3ConstantBufferContainer.h"
#include "GLES3Camera.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CRenderTarget;
			class CViewport
				:public TBaseObject<CViewport>
				,public CConstantBufferContainer
			{
			protected:
				CRenderTarget * const mRenderTarget;
				CCamera * mCamera;
				GLint mX,mY;
				GLsizei mWidth,mHeight;
			public:
				CViewport(CRenderTarget * renderTarget);
				~CViewport();
				CRenderTarget * getRenderTarget()const
				{
					return mRenderTarget;
				}
				Void setCamera(CCamera * camera)
				{
					mCamera=camera;
				}
				CCamera * getCamera()const
				{
					return mCamera;
				}
				Void setX(decltype(mX) x)
				{
					mX=x;
				}
				decltype(mX) getX()const
				{
					return mX;
				}
				Void setY(decltype(mY) y)
				{
					mY=y;
				}
				decltype(mY) getY()const
				{
					return mY;
				}
				Void setWidth(decltype(mWidth) width)
				{
					mWidth=width;
				}
				decltype(mWidth) getWidth()const
				{
					return mWidth;
				}
				Void setHeight(decltype(mHeight) height)
				{
					mHeight=height;
				}
				decltype(mHeight) getHeight()const
				{
					return mHeight;
				}
				Boolean isFullViewport()const;
				Void setup();
			protected:
				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}