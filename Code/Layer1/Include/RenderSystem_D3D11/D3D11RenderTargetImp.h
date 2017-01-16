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
				ID3D11Texture2D * mRenderTargetResource;
				CDepthStencil * mDepthStencil;
				TResourcePtrContainer<IViewportImp*const,CViewportImp> mViewports;
			public:
				CRenderTargetImp(ID3D11RenderTargetView * rt);
				virtual ~CRenderTargetImp();
				ID3D11Texture2D * getRenderTargetResource()const
				{
					return mRenderTargetResource;
				}
				ID3D11DepthStencilView * getDepthStencil()const
				{
					return mDepthStencil->getInternal();
				}
				Void prepare();
				virtual Void render();
			};
			class CWindowImp
				:public TBaseObject<CWindowImp>
				,public TInterfaceObject<IWindowImp>
				,public CRenderTargetImp
				,public CMessageNotifier
			{
			public:
				enum EMessage
				{
					EMessage_BeginResize,
					EMessage_EndResize
				};
			protected:
				IDXGISwapChain * mSwapChain;
			public:
				CWindowImp(IWindowImp * interfaceImp);
				~CWindowImp();
				IDXGISwapChain * getSwapChain()const
				{
					return mSwapChain;
				}
				virtual Void render() override;
			protected:
				// Inherited via TInterfaceObject
				virtual Void onMessage(IWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}