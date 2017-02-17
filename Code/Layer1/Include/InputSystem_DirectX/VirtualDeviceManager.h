#pragma once
#include "VirtualDevice.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		namespace NSDirectX
		{
			class CVirtualDeviceManager
				:public TBaseObject<CVirtualDeviceManager>
				,public TMessageReceiver<IVirtualDeviceManagerImp>
			{
			public:
				typedef TResourcePtrMap<IVirtualDeviceImp*,CVirtualDevice> Devices;
			protected:
				Devices mDevices;
			public:
				CVirtualDeviceManager();
				~CVirtualDeviceManager();
				Void update();
				// Inherited via TMessageReceiver
				virtual void onMessage(IVirtualDeviceManagerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _createVirtualDevice(IVirtualDeviceImp * device);
			};
		}
	}
}