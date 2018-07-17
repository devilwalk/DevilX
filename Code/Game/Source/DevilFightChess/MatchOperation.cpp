#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchOperation2D::CMatchOperation2D(CMatchView2D * view)
	:mMouse(nullptr)
	,mKeyboard(nullptr)
	,mView(view)
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
	{
		CUInt2 mouse_position=mView->getSizeInPixel()/2+mouse->getPosition();
		if((mouse_position.x<10)&&(mouse_position.x>0))
			mView->move(CMatchView2D::EMoveType_Left);
		else if((mView->getSizeInPixel().x-mouse_position.x<10)&&(mView->getSizeInPixel().x-mouse_position.x>0))
			mView->move(CMatchView2D::EMoveType_Right);
		if((mouse_position.y<10)&&(mouse_position.y>0))
			mView->move(CMatchView2D::EMoveType_Down);
		else if((mView->getSizeInPixel().y-mouse_position.y<10)&&(mView->getSizeInPixel().y-mouse_position.y>0))
			mView->move(CMatchView2D::EMoveType_Up);
	}
	break;
	}
}

Void NSDevilX::NSFightChess::CMatchOperation2D::addFrameData(NSInputSystem::IKeyboard * keyboard,NSInputSystem::IKeyboardFrameData * data)
{
	return Void();
}
