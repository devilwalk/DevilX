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
				const IEnum::EInstanceMajorType mMajorType;
				const Int32 mMinorType;
				TResourcePtrVector(IPhysicalDeviceGroupImp) mPhysicsDeviceGroups;
				TResourcePtrVector(IDeviceImp) mDevices;
			public:
				IInstanceImp(IEnum::EInstanceMajorType majorType,Int32 minorType);
				virtual ~IInstanceImp();

				virtual Boolean initialize()=0;

				virtual IEnum::EInstanceMajorType getMajorType() const override;
				virtual Int32 getMinorType() const override;
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
					CComPtr<IDXGIFactory1> mInternal1;
					CComPtr<IDXGIFactory2> mInternal2;
					CComPtr<IDXGIFactory3> mInternal3;
					CComPtr<IDXGIFactory4> mInternal4;
					CComPtr<IDXGIFactory5> mInternal5;
					CComPtr<IDXGIFactory6> mInternal6;
					CComPtr<IDXGIFactory7> mInternal7;
				public:
					IInstanceImp(IEnum::EInstanceMinorType_D3D minorType);
					virtual ~IInstanceImp();

					IDXGIFactory* getInternal()const
					{
						return mInternal;
					}
					IDXGIFactory1* getInternal1()const
					{
						return mInternal1;
					}
					IDXGIFactory2* getInternal2()const
					{
						return mInternal2;
					}
					IDXGIFactory3* getInternal3()const
					{
						return mInternal3;
					}
					IDXGIFactory4* getInternal4()const
					{
						return mInternal4;
					}
					IDXGIFactory5* getInternal5()const
					{
						return mInternal5;
					}
					IDXGIFactory6* getInternal6()const
					{
						return mInternal6;
					}
					IDXGIFactory7* getInternal7()const
					{
						return mInternal7;
					}
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

					auto getInternal()const
					{
						return mInternal;
					}

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
					EGLDisplay mDisplay;
				public:
					IInstanceImp(IEnum::EInstanceMinorType_GL minorType);
					virtual ~IInstanceImp();

					auto getDisplay()const
					{
						return mDisplay;
					}
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