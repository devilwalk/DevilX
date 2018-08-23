#pragma once
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
namespace NSDevilX
{
	namespace NSCore
	{
		class CDirectXManager
			:public TBaseObject<CDirectXManager>
			,public TSingleton<CDirectXManager>
		{
		protected:
			IDXGIFactory*mDXGIFactory;
		public:
			CDirectXManager();
			~CDirectXManager();
			IDXGIFactory * getDXGIFactory()const { return mDXGIFactory; }
		};
	}
}
#endif