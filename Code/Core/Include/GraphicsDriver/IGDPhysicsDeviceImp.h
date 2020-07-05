#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IPhysicsDeviceImp: public IPhysicsDevice
			{
			protected:
			public:
				IPhysicsDeviceImp();
				virtual ~IPhysicsDeviceImp();
			};
			namespace NSDXGI
			{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
				class IPhysicsDeviceImp: public NSGraphicsDriver::IPhysicsDeviceImp
				{
				protected:
					CComPtr<IDXGIAdapter> mInternal;
				public:
					IPhysicsDeviceImp(IDXGIAdapter* adapter);
					virtual ~IPhysicsDeviceImp();
				};
#endif
			}
			namespace NSVulkan
			{
				class IPhysicsDeviceImp: public NSGraphicsDriver::IPhysicsDeviceImp
				{
				protected:
					VkPhysicalDevice mInternal;
					uint32_t mGroupIndex;
				public:
					IPhysicsDeviceImp(VkPhysicalDevice dev,uint32_t groupIndex);
					virtual ~IPhysicsDeviceImp();
				};
			}
		}
	}
}