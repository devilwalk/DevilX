#pragma once
#include "ICoreEnum.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IDevice
		{
		protected:
			virtual ~IDevice(){}
		public:
			virtual IEnum::EDeviceType getType()const=0;
		};
	}
}