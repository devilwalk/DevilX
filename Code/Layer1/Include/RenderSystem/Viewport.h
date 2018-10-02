#pragma once
#include "Camera.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CRenderTarget;
		class CViewport
		{
		protected:
			CRenderTarget * const mRenderTarget;
			CCamera * mCamera;
		public:
			CViewport(CRenderTarget * renderTarget);
			virtual ~CViewport();
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
		};
	}
}