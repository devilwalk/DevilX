#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CPageBarItem::CPageBarItem(const String & name,CControl * parent)
	:CControl(name,parent)
	,mTextControl(nullptr)
{
	auto background=getGraphicScene()->createWindow(name+"/Background");
	background->queryInterface_IElement()->setPosition(CFloat2::sZero);
	background->queryInterface_IElement()->setSize(CFloat2::sOne);
	background->setColour(CFloatRGBA::sBlue);
	_attachWindow(background);
	mTextControl=DEVILX_NEW CStaticText(name+"/TextControl",this);

	auto event_window=getEventScene()->createWindow(name);
	event_window->queryInterface_IElement()->setPosition(CFloat2::sZero);
	event_window->queryInterface_IElement()->setSize(CFloat2::sOne);
	_attachWindow(event_window);
	getEventWindow()->registerListener(this,CEvent::EType_MouseMove);
}

NSDevilX::NSGUISystem::CPageBarItem::~CPageBarItem()
{
	DEVILX_DELETE(getTextControl());
}

Void NSDevilX::NSGUISystem::CPageBarItem::setPrepareFocus(Bool focus)
{
	if(focus)
		ISystemImp::getSingleton().getWindow()->registerEventListener(this);
	else
		ISystemImp::getSingleton().getWindow()->unregisterEventListener(this);
}

Void NSDevilX::NSGUISystem::CPageBarItem::onEvent(NSUISystem::IEvent * e)
{
	switch(e->getType())
	{
	case CEvent::EType_MouseMove:
		static_cast<CPageBar*>(getParent())->setPrepareFocusControl(this);
		break;
	}
}
