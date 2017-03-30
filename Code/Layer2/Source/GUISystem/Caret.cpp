#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CCaret::CCaret(const String & name,CControl * parent)
	:CControl(name,parent)
	,mShow(True)
{
	auto background=getGraphicScene()->createWindow(name);
	background->queryInterface_IElement()->setPosition(CFloat2::sZero);
	background->queryInterface_IElement()->setSize(CFloat2::sOne);
	background->setColour(CFloatRGBA(0.5f,0.5f,0.5f,1.0f));
	_attachWindow(background);
	ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Update);
}

NSDevilX::NSGUISystem::CCaret::~CCaret()
{}

Void NSDevilX::NSGUISystem::CCaret::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		auto delta_time=mTimer.getInMillisecond(False);
		if(delta_time>500)
		{
			mShow=mShow?False:True;
			mTimer.getInMillisecond(True);
		}
		if(mShow)
		{
			mGraphicWindows[0]->setColour(CFloatRGBA(0.5f,0.5f,0.5f,1.0f));
		}
		else
		{
			mGraphicWindows[0]->setColour(CFloatRGBA(CFloatRGBA::sZero));
		}
		break;
	}
}
