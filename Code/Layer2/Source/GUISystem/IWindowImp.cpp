#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IWindowImp::IWindowImp(const String & name,ISceneImp * scene)
	:mScene(scene)
	,mControl(nullptr)
{
	mControl=DEVILX_NEW IControlImp(name,nullptr);
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
	return nullptr;
}

IButton * NSDevilX::NSGUISystem::IWindowImp::createButton(const String & name)
{
	return nullptr;
}
