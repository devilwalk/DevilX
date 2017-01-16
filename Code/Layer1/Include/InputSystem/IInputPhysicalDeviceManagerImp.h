#pragma once
#include "IInputPhysicalDeviceImp.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IPhysicalDeviceManagerImp
			:public IPhysicalDeviceManager
			,public TBaseObject<IPhysicalDeviceManagerImp>
		{
		public:
			typedef TVector<IPhysicalDeviceImp*> DeviceList;
		protected:
			DeviceList mDeviceList;
		public:
			IPhysicalDeviceManagerImp();
			virtual ~IPhysicalDeviceManagerImp();
			Void addPhysicalDevice(IPhysicalDeviceImp * device)
			{
				mDeviceList.push_back(device);
			}

			// Inherited via IPhysicalDeviceManager
			virtual UInt16 getDeviceCount() const override;
			virtual IPhysicalDevice * getDevice(UInt16 index) const override;
		};
	}
}