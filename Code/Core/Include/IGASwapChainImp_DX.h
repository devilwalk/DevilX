#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			namespace NSVersion11
			{
				class IGARenderTargetViewImp;
				class IGADepthStencilViewImp;
			}
			class IGASwapChainImp
				:public TBaseObject<IGASwapChainImp>
				,public IGASwapChain
			{
			protected:
				CComPtr<IDXGISwapChain> mInternal;
				CComPtr<ID3D11Texture2D> mBackBuffer11;
				CComPtr<ID3D11Texture2D> mDepthStencil11;
				std::auto_ptr<NSVersion11::IGARenderTargetViewImp> mRenderTargetView11;
				std::auto_ptr<NSVersion11::IGADepthStencilViewImp> mDepthStencilView11;
			public:
				IGASwapChainImp(ID3D11Device * dev,DXGI_SWAP_CHAIN_DESC && desc);
				~IGASwapChainImp();
				IDXGISwapChain * getInternal()const
				{
					return mInternal;
				}

				// Í¨¹ý IGASwapChain ¼Ì³Ð
				virtual IGARenderTargetView * getRenderTargetView() const override;
				virtual IGADepthStencilView * getDepthStencilView() const override;
				virtual Void present() override;
			};
		}
	}
}