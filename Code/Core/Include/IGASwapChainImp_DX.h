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
			{
			protected:
				CComPtr<IDXGISwapChain> mInternal;
			public:
				IGASwapChainImp(IUnknown * dev,DXGI_SWAP_CHAIN_DESC && desc);
				~IGASwapChainImp();
				IDXGISwapChain * getInternal()const
				{
					return mInternal;
				}

				// ͨ�� IGASwapChain �̳�
				virtual Void present() override;
			};
		}
	}
}