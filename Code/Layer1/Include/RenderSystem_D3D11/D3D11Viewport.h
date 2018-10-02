#pragma once
#include "D3D11ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CViewport
				:public TBaseObject<CViewport>
				,public CConstantBufferContainer
			{
			protected:
				CRenderTarget * const mRenderTarget;
				CCamera * mCamera;
				D3D11_VIEWPORT mInternal;
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
				const D3D11_VIEWPORT & getInternal()const
				{
					return mInternal;
				}
				D3D11_VIEWPORT & getInternalRef()
				{
					return mInternal;
				}
				Boolean isFullViewport()const;
				Void setupMT(ID3D11DeviceContext1 * context);
			protected:
				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}