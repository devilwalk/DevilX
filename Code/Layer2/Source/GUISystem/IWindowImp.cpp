#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IWindowImp::SEvent::SEvent(EType type)
	:mType(type)
	,mLayer(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer("Window/ControlFocus/"+CStringConverter::toString(this));
}

NSDevilX::NSGUISystem::IWindowImp::SEvent::~SEvent()
{
	NSUISystem::getSystem()->destroyLayer(queryInterface_IElement());
}

NSUISystem::IElement * NSDevilX::NSGUISystem::IWindowImp::SEvent::queryInterface_IElement() const
{
	return mLayer;
}

UInt32 NSDevilX::NSGUISystem::IWindowImp::SEvent::getType() const
{
	return mType;
}

NSDevilX::NSGUISystem::IWindowImp::IWindowImp(const String & name,ISceneImp * scene)
	:mControl(nullptr)
	,mScene(scene)
	,mEventScene(nullptr)
	,mEventWindow(nullptr)
	,mFocusControl(nullptr)
{
	mEventScene=NSUISystem::getSystem()->createEventScene(CStringConverter::toString(getScene()->getRenderViewport())+"/"+name);
	mControl=DEVILX_NEW IControlImp(DEVILX_NEW CControl(name,static_cast<ISceneImp*>(getScene())->getGraphicScene(),mEventScene),nullptr);
	mEventWindow=static_cast<ISceneImp*>(getScene())->getEventScene()->createWindow(name);
	mEventWindow->queryInterface_IElement()->setParent(mControl->getControl()->getLayer());
	mEventWindow->queryInterface_IElement()->setSize(CFloat2::sOne);
	mEventWindow->registerListener(this,ISceneImp::SEvent::EType_WindowActive);
}

NSDevilX::NSGUISystem::IWindowImp::~IWindowImp()
{
	mControls.destroyAll();
	static_cast<ISceneImp*>(getScene())->getEventScene()->destroyWindow(mEventWindow);
	DEVILX_DELETE(mControl);
	NSUISystem::getSystem()->destroyEventScene(mEventScene);
}

Void NSDevilX::NSGUISystem::IWindowImp::update()
{
	SEvent e(SEvent::EType_ControlFocus);
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