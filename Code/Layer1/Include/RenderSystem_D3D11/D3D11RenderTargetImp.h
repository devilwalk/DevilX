#pragma once
#include "D3D11BaseObject.h"
#include "D3D11ViewportImp.h"
#include "D3D11DepthStencil.h"
#include "D3D11RenderTarget.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CRenderTargetImp
				:public TInternalObject<CRenderTarget>
			{
			protected:
				CDepthStencil * mDepthStencil;
				TResourcePtrMap<IViewportImp*const,CViewportImp> mViewports;
			public:
				CRenderTargetImp(ID3D11RenderTargetView * rt);
				virtual ~CRenderTargetImp();
				virtual ID3D11Texture2D * getRenderTargetResource()=0;
				ID3D11DepthStencilView * getDepthStencil()const
				{
					return mDepthStencil->getInternal();
				}
				Void prepare();
				virtual Void render();
			};
		}
	}
}