#pragma once
#include "IGDPhysicalDeviceImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IInstanceImp;
			class IPhysicalDeviceGroupImp
				:public IPhysicalDeviceGroup
			{
			protected:
				IInstanceImp* const mInstance;
				TResourcePtrVector(IPhysicalDeviceImp) mDevices;
			public:
				IPhysicalDeviceGroupImp(IInstanceImp* instance);
				virtual ~IPhysicalDeviceGroupImp();

				auto getInstance()const
				{
					return mInstance;
				}
				void addDevice(IPhysicalDeviceImp* device)
				{
					mDevices.push_back(device);
				}
				auto& getDevices()const
				{
					return mDevices;
				}

				// Í¨¹ý IPhysicsDeviceGroup ¼Ì³Ð
				virtual UInt32 getDeviceCount() const override;
				virtual IPhysicalDevice* getDevice(UInt32 index) const override;
			};
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			namespace NSD3D
			{
				class IInstanceImp;
				class IPhysicalDeviceGroupImp
					:public NSGraphicsDriver::IPhysicalDeviceGroupImp
					,public TBaseObject<IPhysicalDeviceGroupImp>
				{
				protected:
					CComPtr<IDXGIAdapter> mInternal;
				public:
					IPhysicalDeviceGroupImp(IDXGIAdapter* adapter,IInstanceImp* instance);
					~IPhysicalDeviceGroupImp();

					IDXGIAdapter* getInternal()const
					{
						return mInternal;
					}
				};
			}
#endif
			namespace NSVulkan
			{
				class IInstanceImp;
				class IPhysicalDeviceGroupImp
					:public NSGraphicsDriver::IPhysicalDeviceGroupImp
					,public TBaseObject<IPhysicalDeviceGroupImp>
				{
				protected:
					const UInt32 mInternal;
				public:
					IPhysicalDeviceGroupImp(UInt32 group,IInstanceImp* instance);
					~IPhysicalDeviceGroupImp();
				};
			}
			namespace NSOpenGL
			{
				class IInstanceImp;
				class IPhysicalDeviceGroupImp
					:public NSGraphicsDriver::IPhysicalDeviceGroupImp
					,public TBaseObject<IPhysicalDeviceGroupImp>
				{
				protected:
				public:
					IPhysicalDeviceGroupImp(IInstanceImp* instance);
					~IPhysicalDeviceGroupImp();
				};
			}
		}
	}
}