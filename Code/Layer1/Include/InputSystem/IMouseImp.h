#pragma once
#include "IInputVirtualDeviceImp.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IMouseImp
			:public IMouse
			,public IVirtualDeviceImp
			,public TBaseObject<IMouseImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_Move,
				EMessage_WheelMove,
				EMessage_ButtonPress,
				EMessage_ButtonRelease
			};
			typedef std::array<IEnum::EButtonState,IEnum::EMouseButtonType_Last+1> ButtonStateList;
		protected:
			CSInt2 mOffset;
			CSInt2 mPosition;
			Int32 mWheelOffset;
			Int32 mWheelPosition;
			ButtonStateList mButtonStateList;
		public:
			IMouseImp(const String & name,IPhysicalDeviceImp * physicalDevice);
			virtual ~IMouseImp();
			Void setOffset(Int32 x,Int32 y);
			Void setPosition(Int32 x,Int32 y);
			Void setWheelOffset(Int32 offset);
			void changeButtonState(IEnum::EMouseButtonType type,IEnum::EButtonState state);
			// Inherited via IMouse
			virtual const CSInt2 & getOffset() const override;
			virtual const CSInt2 & getPosition() const override;
			virtual Int32 getWheelOffset() const override;
			virtual Int32 getWheelPosition() const override;
			virtual IEnum::EButtonState getButtonState(IEnum::EMouseButtonType type) const override;
			virtual IMouse * queryInterface_IMouse() const override;
		};
	}
}