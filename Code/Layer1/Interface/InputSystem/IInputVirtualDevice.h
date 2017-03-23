#pragma once
#include "IInputPhysicalDevice.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IVirtualDevice
		{
		protected:
			virtual ~IVirtualDevice(){}
		public:
			virtual const String & getName()const=0;
			virtual IPhysicalDevice * getPhysicalDevice()const=0;
			virtual CWindow * getWindow()const=0;
		};
	}
}