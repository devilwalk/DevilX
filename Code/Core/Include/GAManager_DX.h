#pragma once
#include "IGADeviceImp_DX11.h"
#include "IGASwapChainImp_DX.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			class CGAManager
				:public TBaseObject<CGAManager>
				,public TSingleton<CGAManager>
			{
			protected:
				IDXGIFactory * mFactory;
				TResourcePtrVector<NSVersion11::IGADeviceImp> mDevices11;
				TResourcePtrVector<IGASwapChainImp> mSwapChains;
			public:
				CGAManager();
				~CGAManager();

				IDXGIFactory * getFactory()const
				{
					return mFactory;
				}

				NSVersion11::IGADeviceImp * createDevice11();
				IGASwapChainImp * createSwapChain(NSVersion11::IGADeviceImp * device,const IGAStruct::SGISwapChainDesc & desc);
			};
		}
	}
}