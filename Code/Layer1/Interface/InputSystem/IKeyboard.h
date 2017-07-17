#pragma once
#include "IInputVirtualDevice.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IKeyboardFrameData
		{
		protected:
			virtual ~IKeyboardFrameData(){}
		public:
			virtual IEnum::EKeyType getKey()const=0;
			virtual IEnum::EButtonState getButtonState()const=0;
		};
		class IKeyboard;
		class IKeyboardListener
		{
		protected:
			virtual ~IKeyboardListener(){}
		public:
			virtual Void addFrameData(IKeyboard * keyboard,IKeyboardFrameData * data)=0;
		};
		class IKeyboard
		{
		protected:
			virtual ~IKeyboard(){}
		public:
			virtual IVirtualDevice * queryInterface_IVirtualDevice()const=0;
			virtual IEnum::EButtonState getButtonState(IEnum::EKeyType type)const=0;
			virtual UInt32 getFrameDataCount()const=0;
			virtual IKeyboardFrameData * getFrameData(UInt32 index)const=0;
			virtual Void setListener(IKeyboardListener * listener)=0;
			virtual IKeyboardListener * getListener()const=0;
		};
	}
}