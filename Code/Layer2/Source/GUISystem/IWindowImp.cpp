#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IWindowImp::IWindowImp(const String & name,ISceneImp * scene)
	:mControl(nullptr)
	,mScene(scene)
{
	mControl=DEVILX_NEW IControlImp(DEVILX_NEW CControl(name,static_cast<ISceneImp*>(getScene())->getGraphicScene(),nullptr),nullptr);
}

NSDevilX::NSGUISystem::IWindowImp::~IWindowImp()
{
	DEVILX_DELETE(mControl);
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
	mControls.destroy(control->queryInterface_IElement()->getName());
}
