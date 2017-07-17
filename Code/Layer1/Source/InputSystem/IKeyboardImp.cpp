#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;

NSDevilX::NSInputSystem::SKeyboardFrameDataImp::SKeyboardFrameDataImp()
	:mState(IEnum::EButtonState_Unknown)
{
}

NSDevilX::NSInputSystem::SKeyboardFrameDataImp::~SKeyboardFrameDataImp()
{}

IEnum::EKeyType NSDevilX::NSInputSystem::SKeyboardFrameDataImp::getKey() const
{
	return mKey;
}

IEnum::EButtonState NSDevilX::NSInputSystem::SKeyboardFrameDataImp::getButtonState() const
{
	return mState;
}

NSDevilX::NSInputSystem::IKeyboardImp::IKeyboardImp(const String & name,IPhysicalDeviceImp * physicalDevice,CWindow * window)
	:IVirtualDeviceImp(name,physicalDevice,window)
	,mListener(nullptr)
{
	memset(&mKeyStateList[0],0,mKeyStateList.size()*sizeof(IEnum::EButtonState));
}

NSDevilX::NSInputSystem::IKeyboardImp::~IKeyboardImp()
{}

Void NSDevilX::NSInputSystem::IKeyboardImp::addFrameData(SKeyboardFrameDataImp * data)
{
	mFrameDatas.push_back(data);
	mKeyStateList[data->getKey()]=data->getButtonState();
}

Void NSDevilX::NSInputSystem::IKeyboardImp::update()
{
	mFrameDatas.clear();
	IVirtualDeviceImp::update();
	if(getListener())
	{
		for(auto data:mFrameDatas)
		{
			getListener()->addFrameData(this,data);
		}
	}
}

IVirtualDevice * NSDevilX::NSInputSystem::IKeyboardImp::queryInterface_IVirtualDevice() const
{
	return const_cast<IKeyboardImp*>(this);
}

IEnum::EButtonState NSDevilX::NSInputSystem::IKeyboardImp::getButtonState(IEnum::EKeyType type) const
{
	return mKeyStateList[type];
}

UInt32 NSDevilX::NSInputSystem::IKeyboardImp::getFrameDataCount() const
{
	return static_cast<UInt32>(mFrameDatas.size());
}

IKeyboardFrameData * NSDevilX::NSInputSystem::IKeyboardImp::getFrameData(UInt32 index) const
{
	return mFrameDatas[index];
}

Void NSDevilX::NSInputSystem::IKeyboardImp::setListener(IKeyboardListener * listener)
{
	mListener=listener;
}

IKeyboardListener * NSDevilX::NSInputSystem::IKeyboardImp::getListener() const
{
	return mListener;
}
