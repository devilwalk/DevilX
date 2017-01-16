#pragma once
#include "IInputVirtualDeviceImp.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IKeyboardImp
			:public IKeyboard
			,public IVirtualDeviceImp
			,public TBaseObject<IKeyboardImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_KeyPress,
				EMessage_KeyRelease
			};
			typedef std::array<IEnum::EButtonState,IEnum::EKeyType_Last+1> KeyStateList;
		protected:
			KeyStateList mKeyStateList;
		public:
			IKeyboardImp(const String & name,IPhysicalDeviceImp * physicalDevice);
			virtual ~IKeyboardImp();
			void changeButtonState(IEnum::EKeyType type,IEnum::EButtonState state);
			// Inherited via IKeyboard
			virtual IEnum::EButtonState getButtonState(IEnum::EKeyType type) const override;
			virtual IKeyboard * queryInterface_IKeyboard() const override;
		};
	}
}