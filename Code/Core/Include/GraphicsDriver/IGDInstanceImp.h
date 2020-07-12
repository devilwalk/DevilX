#pragma once
#include "IGDPhysicsDeviceImp.h"
#include "IGDPhysicsDeviceGroupImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IInstanceImp: public IInstance
			{
			protected:
				IEnum::EInstance mType;
				TResourcePtrVector(IPhysicsDeviceGroupImp) mPhysicsDeviceGroups;
			public:
				IInstanceImp(IEnum::EInstance type);
				virtual ~IInstanceImp();

				virtual Boolean initialize()=0;
			};
			namespace NSDXGI
			{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
				class IInstanceImp
					:public NSGraphicsDriver::IInstanceImp
					,public TBaseObject<IInstanceImp>
				{
				protected:
					CComPtr<IDXGIFactory> mInternal;
				public:
					IInstanceImp(IEnum::EInstance type);
					virtual ~IInstanceImp();

					// 通过 IInstance 继承
					virtual UInt32 enumPhysicsDevices(IPhysicsDevice** outDevices=nullptr) override;
					virtual UInt32 enumPhysicsDeviceGroups(IPhysicsDeviceGroup** outGroups=nullptr) override;
					// 通过 IInstanceImp 继承
					virtual Boolean initialize() override;

				protected:
					Void _enumPhysicsDevicesAndGroups();
				};
#endif
			}
			namespace NSVulkan
			{
				class IInstanceImp
					:public NSGraphicsDriver::IInstanceImp
					,public TBaseObject<IInstanceImp>
				{
				protected:
					VkInstance mInternal;
				public:
					IInstanceImp();
					virtual ~IInstanceImp();

					// 通过 IInstance 继承
					virtual UInt32 enumPhysicsDevices(IPhysicsDevice** outDevices=nullptr) override;
					virtual UInt32 enumPhysicsDeviceGroups(IPhysicsDeviceGroup** outGroups=nullptr) override;

					// 通过 IInstanceImp 继承
					virtual Boolean initialize() override;

				protected:
					Void _enumPhysicsDevicesAndGroups();
				};
			}
		}
	}
}