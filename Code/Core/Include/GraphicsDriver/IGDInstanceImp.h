#pragma once
#include "IGDPhysicsDeviceImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IInstanceImp: public IInstance
			{
			protected:
				TResourcePtrVector(IPhysicsDeviceImp) mPhysicsDevices;
			public:
				IInstanceImp();
				virtual ~IInstanceImp();
			};
			namespace NSDXGI
			{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
				class IInstanceImp: public NSGraphicsDriver::IInstanceImp
				{
				protected:
					CComPtr<IDXGIFactory> mInternal;
				public:
					IInstanceImp();
					virtual ~IInstanceImp();

					// 通过 IInstance 继承
					virtual UInt32 enumPhysicsDevices(IPhysicsDevice** outDevices=nullptr) override;
				};
#endif
			}
			namespace NSVulkan
			{
				class IInstanceImp: public NSGraphicsDriver::IInstanceImp
				{
				protected:
					VkInstance mInternal;
				public:
					IInstanceImp();
					virtual ~IInstanceImp();

					// 通过 IInstance 继承
					virtual UInt32 enumPhysicsDevices(IPhysicsDevice** outDevices=nullptr) override;
				};
			}
		}
	}
}