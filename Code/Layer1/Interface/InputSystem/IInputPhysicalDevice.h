#pragma once
#include "IInputEnum.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IPhysicalDevice
		{
		protected:
			virtual ~IPhysicalDevice(){}
		public:
			virtual IEnum::EPhysicalDeviceType getType()const=0;
		};
	}
}