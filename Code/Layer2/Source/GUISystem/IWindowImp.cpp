#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IWindowImp::IWindowImp(const String & name,ISceneImp * scene)
	:mControl(nullptr)
	,mScene(scene)
	,mEventScene(nullptr)
	,mEventWindow(nullptr)
	,mFocusControl(nullptr)
{
	mEventScene=NSUISystem::getSystem()->createEventScene(CStringConverter::toString(getScene()->getRenderViewport())+"/"+name);
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_Container,DEVILX_NEW CContainer(name,static_cast<ISceneImp*>(getScene())->getGraphicScene(),mEventScene),nullptr);
	mControl->setUserPointer(0,this);
	mEventWindow=static_cast<ISceneImp*>(getScene())->getEventScene()->createWindow(name);
	mEventWindow->queryInterface_IElement()->setParent(mControl->getControl()->getLayer());
	mEventWindow->queryInterface_IElement()->setSize(CFloat2::sOne);
	mEventWindow->registerListener(this,ISceneImp::SEvent::EType_WindowActive);
}

NSDevilX::NSGUISystem::IWindowImp::~IWindowImp()
{
	setFocusControl(nullptr);
	mControls.destroyAll();
	static_cast<ISceneImp*>(getScene())->getEventScene()->destroyWindow(mEventWindow);
	DEVILX_DELETE(mControl);
	NSUISystem::getSystem()->destroyEventScene(mEventScene);
}

Void NSDevilX::NSGUISystem::IWindowImp::update()
{
	CEvent e(CEvent::EType_MouseMove);
	e.queryInterface_IElement()->setPosition(ISystemImp::getSingleton().getWindow()->getCursorPosition()/ISystemImp::getSingleton().getWindow()->getSize());
	e.queryInterface_IElement()->setSize(CInt2::sOne/ISystemImp::getSingleton().getWindow()->getSize());
	if(!mEventScene->route(&e))
	{
		setFocusControl(nullptr);
	}
}

Void NSDevilX::NSGUISystem::IWindowImp::setFocusControl(IControlImp * control)
{
	if(control!=mFocusControl)
	{
		if(mFocusControl)
			mFocusControl->setFocus(False);
		mFocusControl=control;
		if(mFocusControl)
			mFocusControl->setFocus(True);
	}
}

IControl * NSDevilX::NSGUISystem::IWindowImp::queryInterface_IControl() const
{
	return mControl;
}

IScene * NSDevilX::NSGUISystem::IWindowImp::getScene() const
{
	return mScene;
}

IImageBox * NSDevilX::NSGUISystem::IWindowImp::createImageBox(const String & name)
{
	auto ret=DEVILX_NEW IImageBoxImp(name,this);
	mControls.add(name,static_cast<IControlImp*>(ret->queryInterface_IControl()));
	return ret;
}

IStaticText * NSDevilX::NSGUISystem::IWindowImp::createStaticText(const String & name)
{
	auto ret=DEVILX_NEW IStaticTextImp(name,this);
	mControls.add(name,static_cast<IControlImp*>(ret->queryInterface_IControl()));
	return ret;
}

IButton * NSDevilX::NSGUISystem::IWindowImp::createButton(const String & name)
{
	auto ret=DEVILX_NEW IButtonImp(name,this);
	mControls.add(name,static_cast<IControlImp*>(ret->queryInterface_IControl()));
	return ret;
}

IEditBox * NSDevilX::NSGUISystem::IWindowImp::createEditBox(const String & name)
{
	auto ret=DEVILX_NEW IEditBoxImp(name,this);
	mControls.add(name,static_cast<IControlImp*>(ret->queryInterface_IControl()));
	return ret;
}

Void NSDevilX::NSGUISystem::IWindowImp::destroyControl(IControl * control)
{
	mControls.destroy(control->getName());
}

Void NSDevilX::NSGUISystem::IWindowImp::onEvent(NSUISystem::IEvent * e)
{
	switch(e->getType())
	{
	case ISceneImp::SEvent::EType_WindowActive:
		static_cast<ISceneImp*>(getScene())->setActiveWindow(this);
		break;
	}
}

IImageBox * NSDevilX::NSGUISystem::IWindowImp::getImageBox(const String & name) const
{
	auto control=mControls.get(name);
	if(control&&(control->getType()==IControlImp::EType_ImageBox))
		return control->getUserPointer<IImageBoxImp>(0);
	else
		return nullptr;
}

IStaticText * NSDevilX::NSGUISystem::IWindowImp::getStaticText(const String & name) const
{
	auto control=mControls.get(name);
	if(control&&(control->getType()==IControlImp::EType_StaticText))
		return control->getUserPointer<IStaticTextImp>(0);
	else
		return nullptr;
}

IButton * NSDevilX::NSGUISystem::IWindowImp::getButton(const String & name) const
{
	auto control=mControls.get(name);
	if(control&&(control->getType()==IControlImp::EType_Button))
		return control->getUserPointer<IButtonImp>(0);
	else
		return nullptr;
}

IEditBox * NSDevilX::NSGUISystem::IWindowImp::getEditBox(const String & name) const
{
	auto control=mControls.get(name);
	if(control&&(control->getType()==IControlImp::EType_EditBox))
		return control->getUserPointer<IEditBoxImp>(0);
	else
		return nullptr;
}

IPageBar * NSDevilX::NSGUISystem::IWindowImp::createPageBar(const String & name)
{
	auto ret=DEVILX_NEW IPageBarImp(name,this);
	mControls.add(name,static_cast<IControlImp*>(ret->queryInterface_IControl()));
	return ret;
}

IPageBar * NSDevilX::NSGUISystem::IWindowImp::getPageBar(const String & name) const
{
	auto control=mControls.get(name);
	if(control&&(control->getType()==IControlImp::EType_PageBar))
		return control->getUserPointer<IPageBarImp>(0);
	else
		return nullptr;
}
