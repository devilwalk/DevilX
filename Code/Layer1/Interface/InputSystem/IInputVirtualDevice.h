#pragma once
#include "IInputPhysicalDevice.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IMouse
		{
		protected:
			virtual ~IMouse()
			{}
		public:
			virtual const CSInt2 & getOffset()const=0;
			virtual const CSInt2 & getPosition()const=0;
			virtual Int32 getWheelOffset()const=0;
			virtual Int32 getWheelPosition()const=0;
			virtual IEnum::EButtonState getButtonState(IEnum::EMouseButtonType type)const=0;
		};
		class IKeyboard
		{
		protected:
			virtual ~IKeyboard()
			{}
		public:
			virtual IEnum::EButtonState getButtonState(IEnum::EKeyType type)const=0;
		};
		class IVirtualDevice
		{
		protected:
			virtual ~IVirtualDevice(){}
		public:
			virtual IMouse * queryInterface_IMouse()const=0;
			virtual IKeyboard * queryInterface_IKeyboard()const=0;
			virtual const String & getName()const=0;
			virtual IPhysicalDevice * getPhysicalDevice()const=0;
		};
	}
}