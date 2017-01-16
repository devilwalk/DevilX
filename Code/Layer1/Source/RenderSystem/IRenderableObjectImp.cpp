#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IRenderableObjectImp::IRenderableObjectImp(const String & name,ISceneImp * scene)
	:mSceneElement(nullptr)
{
	mSceneElement=DEVILX_NEW ISceneElementImp(name,scene,this,ISceneElementImp::EContainerObjectType_RenderableObject);
}

NSDevilX::NSRenderSystem::IRenderableObjectImp::~IRenderableObjectImp()
{
	DEVILX_DELETE(mSceneElement);
}

IRenderable * NSDevilX::NSRenderSystem::IRenderableObjectImp::createRenderable(const String & name)
{
	if(mRenderables.has(name))
		return nullptr;
	notify(EMessage_BeginRenderableCreate);
	IRenderableImp * renderable=DEVILX_NEW IRenderableImp(name,this);
	mRenderables.add(name,renderable);
	notify(EMessage_EndRenderableCreate,renderable);
	return renderable;
}

IRenderable * NSDevilX::NSRenderSystem::IRenderableObjectImp::getRenderable(const String & name) const
{
	return mRenderables.get(name);
}

IRenderable * NSDevilX::NSRenderSystem::IRenderableObjectImp::getRenderable(UInt32 index) const
{
	return mRenderables.get(index);
}

UInt32 NSDevilX::NSRenderSystem::IRenderableObjectImp::getRenderableCount() const
{
	return static_cast<UInt32>(mRenderables.size());
}

Void NSDevilX::NSRenderSystem::IRenderableObjectImp::destroyRenderable(IRenderable * renderable)
{
	if((!renderable)
		||(!mRenderables.has(renderable->getName()))
		)
		return;
	notify(EMessage_BeginRenderableDestroy,static_cast<IRenderableImp*>(renderable));
	mRenderables.destroy(renderable->getName());
	notify(EMessage_EndRenderableDestroy,static_cast<IRenderableImp*>(renderable));
}

ISceneElement * NSDevilX::NSRenderSystem::IRenderableObjectImp::queryInterface_ISceneElement() const
{
	return mSceneElement;
}
