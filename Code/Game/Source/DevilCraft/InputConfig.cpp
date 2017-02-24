#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSDevilCraft;

NSDevilX::NSDevilCraft::CInputConfig::CInputConfig(const String & name)
	:mName(name)
{}

NSDevilX::NSDevilCraft::CInputConfig::~CInputConfig()
{}

Void NSDevilX::NSDevilCraft::CInputConfig::update(CActor * actor)
{
	for(auto const & pair:mActionKeyDownMap)
	{
		auto const key=pair.first;
		auto const action=pair.second;
		if(NSInputSystem::IEnum::EButtonState_Pressed==CApp::getSingleton().getKeyboard()->queryInterface_IKeyboard()->getButtonState(key))
		{
			actor->addAction(action);
		}
	}
	for(auto const & pair:mActionButtonDownMap)
	{
		auto const key=pair.first;
		auto const action=pair.second;
		if(NSInputSystem::IEnum::EButtonState_Pressed==CApp::getSingleton().getKeyboard()->queryInterface_IMouse()->getButtonState(key))
		{
			actor->addAction(action);
		}
	}
}

NSDevilX::NSDevilCraft::CInputConfigManager::CInputConfigManager()
{
}

NSDevilX::NSDevilCraft::CInputConfigManager::~CInputConfigManager()
{}

CInputConfig * NSDevilX::NSDevilCraft::CInputConfigManager::createConfig(const String & name)
{
	if(mConfigs.has(name))
		return nullptr;
	auto ret=DEVILX_NEW CInputConfig(name);
	mConfigs.add(name,ret);
	return ret;
}

Void NSDevilX::NSDevilCraft::CInputConfigManager::destroyConfig(CInputConfig * config)
{
	if(!mConfigs.has(config->getName()))
		return;
	mConfigs.destroy(config->getName());
}
