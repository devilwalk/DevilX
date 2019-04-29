#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			class IGADeviceImp;
			class CGAEnvironment;
			class IGASwapChainImp
				:public TBaseObject<IGASwapChainImp>
				,public IGASwapChain
			{
			protected:
				std::auto_ptr<CGAEnvironment> mEnvironment;
			public:
				IGASwapChainImp(IGADeviceImp * device,EGLNativeWindowType window);
				~IGASwapChainImp();

				CGAEnvironment* getEnvironment()const
				{
					return mEnvironment.get();
				}

				virtual IGARenderTargetView * getRenderTargetView() const override;
				virtual IGADepthStencilView * getDepthStencilView() const override;
				virtual Void present() override;
			};
		}
	}
}