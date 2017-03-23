#pragma once
#include "IInputPhysicalDeviceManager.h"
#include "IInputVirtualDeviceManager.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual Void shutdown()=0;
			virtual Void update()=0;
			virtual IPhysicalDeviceManager * getPhysicalDeviceManager()const=0;
			virtual IVirtualDeviceManager * getVirtualDeviceManager()const=0;
		};
		ISystem * getSystem();
	}
}