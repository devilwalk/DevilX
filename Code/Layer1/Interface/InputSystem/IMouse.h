#pragma once
#include "IInputVirtualDevice.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IMouseFrameData
		{
		protected:
			virtual ~IMouseFrameData()
			{}
		public:
			virtual Int32 getAxisXOffset()const=0;
			virtual Int32 getAxisYOffset()const=0;
			virtual Int32 getWheelOffset()const=0;
			virtual IEnum::EButtonState getButtonState(IEnum::EMouseButtonType type)const=0;
			virtual IEnum::EMouseEventType getEvent()const=0;
		};
		class IMouse;
		class IMouseListener
		{
		protected:
			virtual ~IMouseListener(){}
		public:
			virtual Void addFrameData(IMouse * mouse,IMouseFrameData * data)=0;
		};
		class IMouse
		{
		protected:
			virtual ~IMouse(){}
		public:
			virtual IVirtualDevice * queryInterface_IVirtualDevice()const=0;
			virtual const CInt2 & getPosition()const=0;
			virtual Int32 getWheelPosition()const=0;
			virtual IEnum::EButtonState getButtonState(IEnum::EMouseButtonType type)const=0;
			virtual UInt32 getFrameDataCount()const=0;
			virtual IMouseFrameData * getFrameData(UInt32 index)const=0;
			virtual Void setListener(IMouseListener * listener)=0;
			virtual IMouseListener * getListener()const=0;
		};
	}
}