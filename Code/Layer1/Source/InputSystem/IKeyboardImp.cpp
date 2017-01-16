#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;

NSDevilX::NSInputSystem::IKeyboardImp::IKeyboardImp(const String & name,IPhysicalDeviceImp * physicalDevice)
	:IVirtualDeviceImp(name,physicalDevice)
{
	memset(&mKeyStateList[0],0,mKeyStateList.size()*sizeof(IEnum::EButtonState));
}

NSDevilX::NSInputSystem::IKeyboardImp::~IKeyboardImp()
{}

void NSDevilX::NSInputSystem::IKeyboardImp::changeButtonState(IEnum::EKeyType type,IEnum::EButtonState state)
{
	if(state!=mKeyStateList[type])
	{
		mKeyStateList[type]=state;
		UInt32 msg=0;
		switch(state)
		{
		case IEnum::EButtonState_Pressed:
			msg=EMessage_KeyPress;
			break;
		case IEnum::EButtonState_Released:
			msg=EMessage_KeyRelease;
			break;
		}
		notify(msg,&type);
	}
}

IEnum::EButtonState NSDevilX::NSInputSystem::IKeyboardImp::getButtonState(IEnum::EKeyType type) const
{
	return mKeyStateList[type];
}

IKeyboard * NSDevilX::NSInputSystem::IKeyboardImp::queryInterface_IKeyboard() const
{
	return const_cast<IKeyboardImp*>(this);
}
