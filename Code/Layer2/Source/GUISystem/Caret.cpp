#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CCaret::CCaret(const String & name,CControl * parent)
	:CControl(name,parent)
	,mEnable(False)
{
	auto background=getGraphicScene()->createWindow(name);
	background->queryInterface_IElement()->setPosition(CFloat2::sZero);
	background->queryInterface_IElement()->setSize(CFloat2::sOne);
	background->setColour(CFloatRGBA(CFloatRGBA::sZero));
	_attachWindow(background);
}

NSDevilX::NSGUISystem::CCaret::~CCaret()
{}

Void NSDevilX::NSGUISystem::CCaret::setEnable(Bool enable)
{
	if(enable!=mEnable)
	{
		mEnable=enable;
		if(mEnable)
		{
			ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Update);
		}
		else
		{
			_show(false);
			ISystemImp::getSingleton().removeListener(this,ISystemImp::EMessage_Update);
		}
	}
}

Void NSDevilX::NSGUISystem::CCaret::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
	{
		Boolean show=_isShow();
		auto delta_time=mTimer.getInMillisecond(False);
		if(delta_time>500)
		{
			show=!show;
			mTimer.getInMillisecond(True);
		}
		_show(show);
	}
	break;
	}
}

Boolean NSDevilX::NSGUISystem::CCaret::_isShow() const
{
	return mGraphicWindows[0]->getColour()==CFloatRGBA(0.5f,0.5f,0.5f,1.0f);
}

Void NSDevilX::NSGUISystem::CCaret::_show(Bool enable)
{
	if(enable)
	{
		mGraphicWindows[0]->setColour(CFloatRGBA(0.5f,0.5f,0.5f,1.0f));
	}
	else
	{
		mGraphicWindows[0]->setColour(CFloatRGBA(CFloatRGBA::sZero));
	}
}
