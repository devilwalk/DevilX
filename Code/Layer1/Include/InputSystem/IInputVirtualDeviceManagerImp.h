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
			typedef TNamedResourcePtrMap(IVirtualDeviceImp) DeviceList;
		protected:
			DeviceList mDeviceList;
		public:
			IVirtualDeviceManagerImp();
			virtual ~IVirtualDeviceManagerImp();
			Void update();
			// Inherited via IVirtualDeviceManager
			virtual IMouse * createMouse(const String & name,IPhysicalDevice * device,CWindow * window) override;
			virtual IKeyboard * createKeyboard(const String & name,IPhysicalDevice * device,CWindow * window) override;
			virtual Void destroyDevice(IVirtualDevice * device) override;
			virtual IVirtualDevice * getDevice(const String & name) const override;
		protected:
			IVirtualDeviceImp * _createDevice(const String & name,IPhysicalDevice * device,CWindow * window);
		};
	}
}