#pragma once
namespace NSDevilX
{
	namespace NSInputSystem
	{
		namespace NSDirectX
		{
			class CPhysicalDeviceManager
				:public TBaseObject<CPhysicalDeviceManager>
			{
			public:
				typedef TUnorderedMap(IPhysicalDeviceImp*,DIDEVICEINSTANCE) Devices;
			protected:
				Devices mDevices;
			public:
				CPhysicalDeviceManager();
				~CPhysicalDeviceManager();
				Void addDevice(LPCDIDEVICEINSTANCE instance);
				const DIDEVICEINSTANCE & getInstance(IPhysicalDeviceImp * device)const;
			};
		}
	}
}