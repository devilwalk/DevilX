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

				// Í¨¹ý IGASwapChain ¼Ì³Ð
				virtual Void present() override;
			};
		}
	}
}