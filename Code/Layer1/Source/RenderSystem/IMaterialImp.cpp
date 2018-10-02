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
	assert(!mTechniques.has(name));
	auto ret=DEVILX_NEW ITechniqueImp(name,this);
	mTechniques.add(name,ret);
	return ret;
}

ITechnique * NSDevilX::NSRenderSystem::IMaterialImp::getTechnique(const String & name)
{
	return mTechniques.get(name);
}

Void NSDevilX::NSRenderSystem::IMaterialImp::destroyTechnique(ITechnique * tech)
{
	return mTechniques.destroy(tech->getName());
}
