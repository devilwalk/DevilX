#pragma once
#include "IInputVirtualDeviceImp.h"
#include "IInputVirtualDeviceImp.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IVirtualDeviceManagerImp
			:public IVirtualDeviceManager
			,public TBaseObject<IVirtualDeviceManagerImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginDeviceCreate,
				EMessage_EndDeviceCreate,
				EMessage_BeginDeviceDestroy,
				EMessage_EndDeviceDestroy
			};
			typedef TNamedResourcePtrMap<IVirtualDeviceImp> DeviceList;
		protected:
			DeviceList mDeviceList;
		public:
			IVirtualDeviceManagerImp();
			virtual ~IVirtualDeviceManagerImp();

			// Inherited via IVirtualDeviceManager
			virtual IVirtualDevice * createDevice(const String & name,IPhysicalDevice * device) override;
			virtual Void destroyDevice(IVirtualDevice * device) override;
			virtual IVirtualDevice * getDevice(const String & name) const override;
		};
	}
}