#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
#if DEVILX_WINDOW_SYSTEM == DEVILX_WINDOW_SYSTEM_WINDOWS
			class IGASwapChainImp
				:public TBaseObject<IGASwapChainImp>
				,public IGASwapChain
				,public IGARenderTargetView
				,public IGADepthStencilView
			{
			protected:
				HDC mHDC;
			public:
				IGASwapChainImp(HWND wnd);
				~IGASwapChainImp();

				virtual IGARenderTargetView * getRenderTargetView() const override;
				virtual IGADepthStencilView * getDepthStencilView() const override;
				virtual Void present() override;
			};
#endif
		}
	}
}