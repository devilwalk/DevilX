#pragma once
#include "IMouse.h"
#include "IKeyboard.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IVirtualDeviceManager
		{
		protected:
			virtual ~IVirtualDeviceManager(){}
		public:
			virtual IMouse * createMouse(const String & name,IPhysicalDevice * device,CWindow * window=nullptr)=0;
			virtual IKeyboard * createKeyboard(const String & name,IPhysicalDevice * device,CWindow * window=nullptr)=0;
			virtual Void destroyDevice(IVirtualDevice * device)=0;
			virtual IVirtualDevice * getDevice(const String & name)const=0;
		};
	}
}