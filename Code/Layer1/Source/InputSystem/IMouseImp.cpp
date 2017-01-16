#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;
NSDevilX::NSInputSystem::IMouseImp::IMouseImp(const String & name,IPhysicalDeviceImp * physicalDevice)
	:IVirtualDeviceImp(name,physicalDevice)
	,mOffset(0,0)
	,mPosition(0,0)
	,mWheelOffset(0)
	,mWheelPosition(0)
{
	memset(&mButtonStateList[0],0,mButtonStateList.size()*sizeof(IEnum::EButtonState));
}

NSDevilX::NSInputSystem::IMouseImp::~IMouseImp()
{}

Void NSDevilX::NSInputSystem::IMouseImp::setOffset(Int32 x,Int32 y)
{
	if((x!=mOffset.x)||(y!=mOffset.y))
	{
		mOffset.x=x;
		mOffset.y=y;
		notify(EMessage_Move);
	}
}

Void NSDevilX::NSInputSystem::IMouseImp::setPosition(Int32 x,Int32 y)
{
	mPosition.x=x;
	mPosition.y=y;
}

Void NSDevilX::NSInputSystem::IMouseImp::setWheelOffset(Int32 offset)
{
	if(offset!=mWheelOffset)
	{
		mWheelOffset=offset;
		mWheelPosition+=mWheelOffset;
		notify(EMessage_WheelMove);
	}
}

void NSDevilX::NSInputSystem::IMouseImp::changeButtonState(IEnum::EMouseButtonType type,IEnum::EButtonState state)
{
	if(state!=mButtonStateList[type])
	{
		mButtonStateList[type]=state;
		UInt32 msg=0;
		switch(state)
		{
		case IEnum::EButtonState_Pressed:
			msg=EMessage_ButtonPress;
			break;
		case IEnum::EButtonState_Released:
			msg=EMessage_ButtonRelease;
			break;
		}
		notify(msg,&type);
	}
}

const CSInt2 & NSDevilX::NSInputSystem::IMouseImp::getOffset() const
{
	// TODO: insert return statement here
	return mOffset;
}

const CSInt2 & NSDevilX::NSInputSystem::IMouseImp::getPosition() const
{
	// TODO: insert return statement here
	return mPosition;
}

Int32 NSDevilX::NSInputSystem::IMouseImp::getWheelOffset() const
{
	return mWheelOffset;
}

Int32 NSDevilX::NSInputSystem::IMouseImp::getWheelPosition() const
{
	return mWheelPosition;
}

IEnum::EButtonState NSDevilX::NSInputSystem::IMouseImp::getButtonState(IEnum::EMouseButtonType type) const
{
	return mButtonStateList[type];
}

IMouse * NSDevilX::NSInputSystem::IMouseImp::queryInterface_IMouse() const
{
	return const_cast<IMouseImp*>(this);
}
