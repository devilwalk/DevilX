#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::ISubEntityImp::ISubEntityImp(const String & name,IEntityImp * object)
	:mName(name)
	,mObject(object)
	,mRenderable(nullptr)
{
}

NSDevilX::NSRenderSystem::ISubEntityImp::~ISubEntityImp()
{
}

IRenderable * NSDevilX::NSRenderSystem::ISubEntityImp::queryInterface_IRenderable() const
{
	return mRenderable;
}

const String & NSDevilX::NSRenderSystem::ISubEntityImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

IEntity * NSDevilX::NSRenderSystem::ISubEntityImp::getEntity() const
{
	return mObject;
}