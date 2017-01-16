#pragma once
#include "IInputPhysicalDeviceManager.h"
#include "IInputVirtualDeviceManager.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		template<typename eventTypeT>
		class IEventListener
		{
		protected:
			virtual ~IEventListener(){}
		public:
			virtual Void onEvent(eventTypeT type,IVirtualDevice * device)=0;
		};
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual Void shutdown()=0;
			virtual Void update()=0;
			virtual IPhysicalDeviceManager * getPhysicalDeviceManager()const=0;
			virtual IVirtualDeviceManager * getVirtualDeviceManager()const=0;
			virtual Void registerEvent(IEnum::EMouseEventType type,IEventListener<IEnum::EMouseEventType> * listener)=0;
			virtual Void registerEvent(IEnum::EKeyboardEventType type,IEventListener<IEnum::EKeyboardEventType> * listener)=0;
			virtual Void unregisterEvent(IEnum::EMouseEventType type,IEventListener<IEnum::EMouseEventType> * listener)=0;
			virtual Void unregisterEvent(IEnum::EKeyboardEventType type,IEventListener<IEnum::EKeyboardEventType> * listener)=0;
		};
		ISystem * getSystem();
	}
}