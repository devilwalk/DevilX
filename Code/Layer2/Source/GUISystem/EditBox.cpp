#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CEditBox::CEditBox(const String & name,CControl * parent)
	:CControl(name,parent)
	,mTextControl(nullptr)
	,mCaret(nullptr)
	,mBackgroundResource(nullptr)
{
	auto background=getGraphicScene()->createWindow(name+"/Background");
	background->queryInterface_IElement()->setPosition(CFloat2::sZero);
	background->queryInterface_IElement()->setSize(CFloat2::sOne);
	background->setColour(CFloatRGBA::sWhite);
	_attachWindow(background);
	mTextControl=DEVILX_NEW CStaticText(name+"/TextControl",this);
	mCaret=DEVILX_NEW CCaret(name+"/Caret",this);
	mCaret->getLayer()->setPosition(CFloat2::sZero);
	mCaret->getLayer()->setSize(CFloat2(0.01f,1.0f));
	auto event_window=getEventScene()->createWindow(name);
	event_window->queryInterface_IElement()->setPosition(CFloat2::sZero);
	event_window->queryInterface_IElement()->setSize(CFloat2::sOne);
	_attachWindow(event_window);
}

NSDevilX::NSGUISystem::CEditBox::~CEditBox()
{
	DEVILX_DELETE(getTextControl());
	DEVILX_DELETE(mCaret);
}

Void NSDevilX::NSGUISystem::CEditBox::setBackground(NSResourceSystem::IResource * resource)
{
	mBackgroundResource=resource;
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::CEditBox::getBackground() const
{
	return mBackgroundResource;
}

Void NSDevilX::NSGUISystem::CEditBox::setFocus(Bool focus)
{
	if(focus)
		ISystemImp::getSingleton().getWindow()->registerEventListener(this);
	else
		ISystemImp::getSingleton().getWindow()->unregisterEventListener(this);
}

Void NSDevilX::NSGUISystem::CEditBox::onCharEvent(CWindow * window,const CUTF16Char & ch)
{
	notify(EMessage_BeginTextChange);
	getTextControl()->setText(getTextControl()->getText()+CUTF8Char(ch));
	notify(EMessage_EndTextChange);
}
