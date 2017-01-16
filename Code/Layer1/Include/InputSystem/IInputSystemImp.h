#pragma once
#include "IInputPhysicalDeviceManagerImp.h"
#include "IInputVirtualDeviceManagerImp.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class ISystemImp
			:public ISystem
			,public TBaseObject<ISystemImp>
			,public TSingleton<ISystemImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction,
				EMessage_UpdateData,
				EMessage_UpdateState
			};
		protected:
			IPhysicalDeviceManagerImp * mPhysicalDeviceManager;
			IVirtualDeviceManagerImp * mVirtualDeviceManager;
		public:
			ISystemImp();
			~ISystemImp();

			// Inherited via ISystem
			virtual Void shutdown() override;
			virtual Void update() override;
			virtual IPhysicalDeviceManager * getPhysicalDeviceManager() const override;
			virtual IVirtualDeviceManager * getVirtualDeviceManager() const override;
			virtual Void registerEvent(IEnum::EMouseEventType type,IEventListener<IEnum::EMouseEventType>* listener) override;
			virtual Void registerEvent(IEnum::EKeyboardEventType type,IEventListener<IEnum::EKeyboardEventType>* listener) override;
			virtual Void unregisterEvent(IEnum::EMouseEventType type,IEventListener<IEnum::EMouseEventType>* listener) override;
			virtual Void unregisterEvent(IEnum::EKeyboardEventType type,IEventListener<IEnum::EKeyboardEventType>* listener) override;
		};
	}
}