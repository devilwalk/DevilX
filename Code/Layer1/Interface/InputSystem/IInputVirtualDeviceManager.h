#pragma once
#include "IInputVirtualDevice.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IVirtualDeviceManager
		{
		protected:
			virtual ~IVirtualDeviceManager(){}
		public:
			virtual IVirtualDevice * createDevice(const String & name,IPhysicalDevice * device)=0;
			virtual Void destroyDevice(IVirtualDevice * device)=0;
			virtual IVirtualDevice * getDevice(const String & name)const=0;
		};
	}
}