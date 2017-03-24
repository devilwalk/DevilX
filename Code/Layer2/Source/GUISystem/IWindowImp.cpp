#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IWindowImp::IWindowImp(const String & name,ISceneImp * scene)
	:mControl(nullptr)
	,mScene(scene)
	,mEventScene(nullptr)
	,mEventWindow(nullptr)
{
	mEventScene=NSUISystem::getSystem()->createEventScene(CStringConverter::toString(getScene()->getRenderViewport())+"/"+name);
	mControl=DEVILX_NEW IControlImp(DEVILX_NEW CControl(name,static_cast<ISceneImp*>(getScene())->getGraphicScene(),mEventScene),nullptr);
	mEventWindow=static_cast<ISceneImp*>(getScene())->getEventScene()->createWindow(name);
	mEventWindow->queryInterface_IElement()->setParent(mControl->getControl()->getLayer());
	mEventWindow->queryInterface_IElement()->setSize(CFloat2::sOne);
	mEventWindow->registerListener(this,);
}

NSDevilX::NSGUISystem::IWindowImp::~IWindowImp()
{
	static_cast<ISceneImp*>(getScene())->getEventScene()->destroyWindow(mEventWindow);
	DEVILX_DELETE(mControl);
	NSUISystem::getSystem()->destroyEventScene(mEventScene);
}

Void NSDevilX::NSGUISystem::IWindowImp::setActive(Bool active)
{
	if(active)
		ISystemImp::getSingleton().getWindow()->registerEventListener(this);
	else
		ISystemImp::getSingleton().getWindow()->unregisterEventListener(this);
}

IControl * NSDevilX::NSGUISystem::IWindowImp::queryInterface_IControl() const
{
	return mControl;
}

IScene * NSDevilX::NSGUISystem::IWindowImp::getScene() const
{
	return mScene;
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

Void NSDevilX::NSGUISystem::IWindowImp::destroyControl(IControl * control)
{
	mControls.destroy(control->getName());
}

Void NSDevilX::NSGUISystem::IWindowImp::onEvent(NSUISystem::IEvent * e)
{
	static_cast<ISceneImp*>(getScene())->setActiveWindow(this);
}
