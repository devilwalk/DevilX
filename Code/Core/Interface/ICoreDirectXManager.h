#pragma once
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
namespace NSDevilX
{
	namespace NSCore
	{
		class IDirectXManager
		{
		protected:
			~IDirectXManager();
		public:
			IDXGIFactory*getDXGIFactory()const;
		};
	}
}
#endif