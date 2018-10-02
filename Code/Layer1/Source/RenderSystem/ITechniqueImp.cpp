#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::ITechniqueImp::ITechniqueImp(const String & name,IMaterialImp * material)
	:mName(name)
	,mMaterial(material)
{
}

NSDevilX::NSRenderSystem::ITechniqueImp::~ITechniqueImp()
{
}

IMaterial * NSDevilX::NSRenderSystem::ITechniqueImp::getMaterial() const
{
	return mMaterial;
}

const String & NSDevilX::NSRenderSystem::ITechniqueImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

Void NSDevilX::NSRenderSystem::ITechniqueImp::setSchemeName(const String & name)
{
	if(name!=mSchemeName)
	{
		mSchemeName=name;
	}
}

const String & NSDevilX::NSRenderSystem::ITechniqueImp::getSchemeName() const
{
	return mSchemeName;
}

IPass * NSDevilX::NSRenderSystem::ITechniqueImp::createPass()
{
	auto ret=DEVILX_NEW IPassImp(this);
	mPasses.push_back(ret);
	return ret;
}

IPass * NSDevilX::NSRenderSystem::ITechniqueImp::getPass(UInt32 index) const
{
	return mPasses[index];
}

Void NSDevilX::NSRenderSystem::ITechniqueImp::destroyPass(IPass * pass)
{
	return mPasses.destroy(static_cast<IPassImp*>(pass));
}
