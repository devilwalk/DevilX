#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IEntityImp::IEntityImp(const String & name,ISceneImp * scene)
	:mSceneElement(nullptr)
{
	mSceneElement=DEVILX_NEW ISceneElementImp(name,scene,this,ISceneElementImp::EContainerObjectType_Entity);
}

NSDevilX::NSRenderSystem::IEntityImp::~IEntityImp()
{
	DEVILX_DELETE(mSceneElement);
}

IEntityRenderable * NSDevilX::NSRenderSystem::IEntityImp::createRenderable(const String & name)
{
	if(mRenderables.has(name))
		return nullptr;
	notify(EMessage_BeginRenderableCreate);
	IEntityRenderableImp * renderable=DEVILX_NEW IEntityRenderableImp(name,this);
	mRenderables.add(name,renderable);
	notify(EMessage_EndRenderableCreate,renderable);
	return renderable;
}

IEntityRenderable * NSDevilX::NSRenderSystem::IEntityImp::getRenderable(const String & name) const
{
	return mRenderables.get(name);
}

IEntityRenderable * NSDevilX::NSRenderSystem::IEntityImp::getRenderable(UInt32 index) const
{
	return mRenderables.get(index);
}

UInt32 NSDevilX::NSRenderSystem::IEntityImp::getRenderableCount() const
{
	return static_cast<UInt32>(mRenderables.size());
}

Void NSDevilX::NSRenderSystem::IEntityImp::destroyRenderable(IEntityRenderable * renderable)
{
	if((!renderable)
		||(!mRenderables.has(renderable->getName()))
		)
		return;
	notify(EMessage_BeginRenderableDestroy,static_cast<IEntityRenderableImp*>(renderable));
	mRenderables.destroy(renderable->getName());
	notify(EMessage_EndRenderableDestroy,static_cast<IEntityRenderableImp*>(renderable));
}

ISceneElement * NSDevilX::NSRenderSystem::IEntityImp::queryInterface_ISceneElement() const
{
	return mSceneElement;
}
