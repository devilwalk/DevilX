#pragma once
#include "IGDPhysicalDeviceImp.h"
#include "IGDPhysicalDeviceGroupImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IInstanceImp: public IInstance
			{
			protected:
				const IEnum::EInstance mType;
				TResourcePtrVector(IPhysicalDeviceGroupImp) mPhysicsDeviceGroups;
				TResourcePtrVector(IDeviceImp) mDevices;
			public:
				IInstanceImp(IEnum::EInstance type);
				virtual ~IInstanceImp();

				virtual Boolean initialize()=0;
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D
			{
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
					virtual Boolean initialize() override;
					virtual UInt32 enumPhysicalDevices(IPhysicalDevice** outDevices=nullptr) override;
					virtual UInt32 enumPhysicalDeviceGroups(IPhysicalDeviceGroup** outGroups=nullptr) override;
					virtual IDevice* createDevice(IPhysicalDeviceGroup* deviceGroup) override;

				protected:
					Void _enumPhysicalDevicesAndGroups();
					IDeviceImp* _createDevice12(IPhysicalDeviceGroup* deviceGroup);
					IDeviceImp* _createDevice11(IPhysicalDeviceGroup* deviceGroup);
				};
			}
#endif
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
					virtual Boolean initialize() override;
					virtual UInt32 enumPhysicalDevices(IPhysicalDevice** outDevices=nullptr) override;
					virtual UInt32 enumPhysicalDeviceGroups(IPhysicalDeviceGroup** outGroups=nullptr) override;
					virtual IDevice* createDevice(IPhysicalDeviceGroup* deviceGroup) override;

				protected:
					Void _enumPhysicalDevicesAndGroups();
				};
			}
			namespace NSOpenGL
			{
				class IInstanceImp
					:public NSGraphicsDriver::IInstanceImp
					,public TBaseObject<IInstanceImp>
				{
				protected:
				public:
					IInstanceImp(IEnum::EInstance type);
					virtual ~IInstanceImp();

					// 通过 IInstance 继承
					virtual Boolean initialize() override;
					virtual UInt32 enumPhysicalDevices(IPhysicalDevice** outDevices=nullptr) override;
					virtual UInt32 enumPhysicalDeviceGroups(IPhysicalDeviceGroup** outGroups=nullptr) override;
					virtual IDevice* createDevice(IPhysicalDeviceGroup* deviceGroup) override;

				protected:
					Void _enumPhysicalDevicesAndGroups();
				};
			}
		}
	}
}