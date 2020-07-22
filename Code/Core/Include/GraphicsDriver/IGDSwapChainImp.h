#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class ISwapChainImp
				:public ISwapChain
			{
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D
			{
				class ISwapChainImp
					:public NSGraphicsDriver::ISwapChainImp
					,public TBaseObject<ISwapChainImp>
				{
				protected:
					CComPtr<IDXGISwapChain> mInternal;
				public:
					ISwapChainImp(IDXGISwapChain* v);
					virtual ~ISwapChainImp();
				};
			}
#endif
		}
	}
}