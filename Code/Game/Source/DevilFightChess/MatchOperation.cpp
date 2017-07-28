#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchOperation2D::CMatchOperation2D()
	:mMouse(nullptr)
	,mKeyboard(nullptr)
{
	for(UInt32 physical_device_index=0;physical_device_index<NSInputSystem::getSystem()->getPhysicalDeviceManager()->getDeviceCount();++physical_device_index)
	{
		auto dev=NSInputSystem::getSystem()->getPhysicalDeviceManager()->getDevice(physical_device_index);
		if(dev->getType()==NSInputSystem::IEnum::EPhysicalDeviceType_Mouse)
		{
			mMouse=NSInputSystem::getSystem()->getVirtualDeviceManager()->createMouse("MatchMouse2D",dev,CApp::getSingleton().getWindow());
			mMouse->setListener(this);
			break;
		}
		if(dev->getType()==NSInputSystem::IEnum::EPhysicalDeviceType_Keyboard)
		{
			mKeyboard=NSInputSystem::getSystem()->getVirtualDeviceManager()->createKeyboard("MatchKeyboard2D",dev,CApp::getSingleton().getWindow());
			mKeyboard->setListener(this);
			break;
		}
	}
}

NSDevilX::NSFightChess::CMatchOperation2D::~CMatchOperation2D()
{
	NSInputSystem::getSystem()->getVirtualDeviceManager()->destroyDevice(mMouse->queryInterface_IVirtualDevice());
	NSInputSystem::getSystem()->getVirtualDeviceManager()->destroyDevice(mKeyboard->queryInterface_IVirtualDevice());
}

Void NSDevilX::NSFightChess::CMatchOperation2D::addFrameData(NSInputSystem::IMouse * mouse,NSInputSystem::IMouseFrameData * data)
{
	switch(data->getEvent())
	{
	case NSInputSystem::IEnum::EMouseEventType_Move:

		break;
	}
}

Void NSDevilX::NSFightChess::CMatchOperation2D::addFrameData(NSInputSystem::IKeyboard * keyboard,NSInputSystem::IKeyboardFrameData * data)
{
	return Void();
}
