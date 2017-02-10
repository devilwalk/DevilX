#pragma once
#include "D3D11RenderTargetImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
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
				ID3D11Texture2D * mRenderTargetResource;
				IDXGISwapChain * mSwapChain;
			public:
				CWindowImp(IWindowImp * interfaceImp);
				~CWindowImp();
				virtual ID3D11Texture2D * getRenderTargetResource() override
				{
					return mRenderTargetResource;
				}
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