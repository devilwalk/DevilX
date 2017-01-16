#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;
NSDevilX::NSInputSystem::IPhysicalDeviceImp::IPhysicalDeviceImp(IEnum::EPhysicalDeviceType type)
	:mType(type)
{
	static_cast<IPhysicalDeviceManagerImp*>(ISystemImp::getSingleton().getPhysicalDeviceManager())->addPhysicalDevice(this);
}

NSDevilX::NSInputSystem::IPhysicalDeviceImp::~IPhysicalDeviceImp()
{}

IEnum::EPhysicalDeviceType NSDevilX::NSInputSystem::IPhysicalDeviceImp::getType() const
{
	return mType;
}
