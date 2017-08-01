#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IWindowImp::IWindowImp(const String & name,ISceneImp * scene,Bool isModule)
	:mControl(nullptr)
	,mScene(scene)
	,mIsModule(isModule)
	,mEventScene(nullptr)
	,mEventWindow(nullptr)
	,mPrepareFocusControl(nullptr)
	,mFocusControl(nullptr)
{
	mEventScene=NSUISystem::getSystem()->createEventScene(CStringConverter::toString(getScene()->getRenderViewport())+"/"+name);
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_Container,DEVILX_NEW CContainer(name,static_cast<ISceneImp*>(getScene())->getGraphicScene(),mEventScene),nullptr);
	mEventWindow=static_cast<ISceneImp*>(getScene())->getEventScene()->createWindow(name);
	mEventWindow->queryInterface_IElement()->setCoordParent(mControl->getControl()->getLayer());
	mEventWindow->queryInterface_IElement()->setOrderParent(mControl->getControl()->getLayer());
	mEventWindow->queryInterface_IElement()->setSize(CFloat2::sOne);
	mEventWindow->registerListener(this,ISceneImp::SEvent::EType_WindowActive);
}

NSDevilX::NSGUISystem::IWindowImp::~IWindowImp()
{
	setPrepareFocusControl(nullptr);
	setFocusControl(nullptr);
	mButtons.destroyAll();
	mStaticTexts.destroyAll();
	mImageBoxes.destroyAll();
	mEditBoxes.destroyAll();
	mPageBars.destroyAll();
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
		setPrepareFocusControl(nullptr);
	}
}

Void NSDevilX::NSGUISystem::IWindowImp::setPrepareFocusControl(IControlImp * control)
{
	if(control!=mPrepareFocusControl)
	{
		if(mPrepareFocusControl)
			mPrepareFocusControl->setPrepareFocus(False);
		mPrepareFocusControl=control;
		if(mPrepareFocusControl)
			mPrepareFocusControl->setPrepareFocus(True);
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
	if(mImageBoxes.has(name))
		return nullptr;
	auto ret=DEVILX_NEW IImageBoxImp(name,this);
	mImageBoxes.add(name,ret);
	return ret;
}

IStaticText * NSDevilX::NSGUISystem::IWindowImp::createStaticText(const String & name)
{
	if(mStaticTexts.has(name))
		return nullptr;
	auto ret=DEVILX_NEW IStaticTextImp(name,this);
	mStaticTexts.add(name,ret);
	return ret;
}

IButton * NSDevilX::NSGUISystem::IWindowImp::createButton(const String & name)
{
	if(mButtons.has(name))
		return nullptr;
	auto ret=DEVILX_NEW IButtonImp(name,this);
	mButtons.add(name,ret);
	return ret;
}

IEditBox * NSDevilX::NSGUISystem::IWindowImp::createEditBox(const String & name)
{
	if(mEditBoxes.has(name))
		return nullptr;
	auto ret=DEVILX_NEW IEditBoxImp(name,this);
	mEditBoxes.add(name,ret);
	return ret;
}

Void NSDevilX::NSGUISystem::IWindowImp::destroyControl(IControl * control)
{
	switch(static_cast<IControlImp*>(control)->getType())
	{
	case IControlImp::EType_Button:mButtons.destroy(control->getName());break;
	case IControlImp::EType_EditBox:mEditBoxes.destroy(control->getName());break;
	case IControlImp::EType_ImageBox:mImageBoxes.destroy(control->getName());break;
	case IControlImp::EType_PageBar:mPageBars.destroy(control->getName());break;
	case IControlImp::EType_StaticText:mStaticTexts.destroy(control->getName());break;
	}
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
	return mImageBoxes.get(name);
}

IStaticText * NSDevilX::NSGUISystem::IWindowImp::getStaticText(const String & name) const
{
	return mStaticTexts.get(name);
}

IButton * NSDevilX::NSGUISystem::IWindowImp::getButton(const String & name) const
{
	return mButtons.get(name);
}

IEditBox * NSDevilX::NSGUISystem::IWindowImp::getEditBox(const String & name) const
{
	return mEditBoxes.get(name);
}

IPageBar * NSDevilX::NSGUISystem::IWindowImp::createPageBar(const String & name)
{
	if(mPageBars.has(name))
		return nullptr;
	auto ret=DEVILX_NEW IPageBarImp(name,this);
	mPageBars.add(name,ret);
	return ret;
}

IPageBar * NSDevilX::NSGUISystem::IWindowImp::getPageBar(const String & name) const
{
	return mPageBars.get(name);
}

UInt32 NSDevilX::NSGUISystem::IWindowImp::getButtonCount() const
{
	return static_cast<UInt32>(mButtons.size());
}

IButton * NSDevilX::NSGUISystem::IWindowImp::getButton(UInt32 index) const
{
	return mButtons.get(index);
}

UInt32 NSDevilX::NSGUISystem::IWindowImp::getEditBoxCount() const
{
	return static_cast<UInt32>(mEditBoxes.size());
}

IEditBox * NSDevilX::NSGUISystem::IWindowImp::getEditBox(UInt32 index) const
{
	return mEditBoxes.get(index);
}
