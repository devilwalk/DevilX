#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			class IGASwapChainImp
				:public TBaseObject<IGASwapChainImp>
				,public IGASwapChain
				,public IGARenderTargetView
				,public IGADepthStencilView
			{
			protected:
				CComPtr<IDXGISwapChain> mInternal;
				CComPtr<ID3D11Texture2D> mBackBuffer11;
				CComPtr<ID3D11RenderTargetView> mRenderTargetView11;
				CComPtr<ID3D11Texture2D> mDepthStencil11;
				CComPtr<ID3D11DepthStencilView> mDepthStencilView11;
			public:
				IGASwapChainImp(ID3D11Device * dev,DXGI_SWAP_CHAIN_DESC && desc);
				~IGASwapChainImp();
				IDXGISwapChain * getInternal()const
				{
					return mInternal;
				}

				// ͨ�� IGASwapChain �̳�
				virtual IGARenderTargetView * getRenderTargetView() const override;
				virtual IGADepthStencilView * getDepthStencilView() const override;
				virtual Void present() override;
			};
		}
	}
}