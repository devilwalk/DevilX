#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IMaterialImp::IMaterialImp(const String & name)
	:mName(name)
{
}

NSDevilX::NSRenderSystem::IMaterialImp::~IMaterialImp()
{
}

const String & NSDevilX::NSRenderSystem::IMaterialImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

ITechnique * NSDevilX::NSRenderSystem::IMaterialImp::createTechnique(const String & name)
{
}

ITechnique * NSDevilX::NSRenderSystem::IMaterialImp::getTechnique(const String & name)
{
	return nullptr;
}

Void NSDevilX::NSRenderSystem::IMaterialImp::destroyTechnique(ITechnique * tech)
{
	return Void();
}
