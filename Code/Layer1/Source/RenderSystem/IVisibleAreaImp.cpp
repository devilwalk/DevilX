#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IVisibleAreaImp::IVisibleAreaImp(const String & name,ISceneImp * scene)
	:mName(name)
	,mScene(scene)
	,mVisible(True)
	,mTransformer(nullptr)
{}

NSDevilX::NSRenderSystem::IVisibleAreaImp::~IVisibleAreaImp()
{
	if(mTransformer)
		mTransformer->release();
}

const DirectX::BoundingBox & NSDevilX::NSRenderSystem::IVisibleAreaImp::getWorldBoundingBox()
{
	// TODO: insert return statement here
	processSingle(EDirtyFlag_WorldAABB);
	return mWorldAABB;
}

const String & NSDevilX::NSRenderSystem::IVisibleAreaImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

IScene * NSDevilX::NSRenderSystem::IVisibleAreaImp::getScene() const
{
	return mScene;
}

Void NSDevilX::NSRenderSystem::IVisibleAreaImp::setVisible(Bool visible)
{
	if(visible!=getVisible())
	{
		notify(EMessage_BeginVisibleChange);
		mVisible=visible;
		notify(EMessage_EndVisibleChange);
	}
}

Bool NSDevilX::NSRenderSystem::IVisibleAreaImp::getVisible() const
{
	return mVisible;
}

Void NSDevilX::NSRenderSystem::IVisibleAreaImp::setTransformer(ITransformer * transformer)
{
	if(transformer!=mTransformer)
	{
		notify(EMessage_BeginTransformerChange,static_cast<ITransformerImp*>(transformer));
		if(getTransformer())
		{
			mTransformer->release();
			mTransformer->removeListener(this,ITransformerImp::EMessage_EndOrientationChange);
			mTransformer->removeListener(this,ITransformerImp::EMessage_EndPositionChange);
			mTransformer->removeListener(this,ITransformerImp::EMessage_EndScaleChange);
		}
		mTransformer=static_cast<ITransformerImp*>(transformer);
		addDirtyFlag(EDirtyFlag_WorldAABB);
		if(getTransformer())
		{
			mTransformer->addRef();
			mTransformer->addListener(this,ITransformerImp::EMessage_EndOrientationChange);
			mTransformer->addListener(this,ITransformerImp::EMessage_EndPositionChange);
			mTransformer->addListener(this,ITransformerImp::EMessage_EndScaleChange);
		}
		notify(EMessage_EndTransformerChange);
	}
}

ITransformer * NSDevilX::NSRenderSystem::IVisibleAreaImp::getTransformer() const
{
	return mTransformer;
}

Void NSDevilX::NSRenderSystem::IVisibleAreaImp::setBoundingBox(const DirectX::BoundingBox & aabb)
{
	if(aabb!=mLocalAABB)
	{
		mLocalAABB=aabb;
		addDirtyFlag(EDirtyFlag_WorldAABB);
	}
}

const DirectX::BoundingBox & NSDevilX::NSRenderSystem::IVisibleAreaImp::getBoundingBox() const
{
	// TODO: insert return statement here
	return mLocalAABB;
}

Void NSDevilX::NSRenderSystem::IVisibleAreaImp::attachObject(ISceneElement * element)
{
	mObjects.insert(static_cast<ISceneElementImp*>(element));
}

Void NSDevilX::NSRenderSystem::IVisibleAreaImp::detachObject(ISceneElement * element)
{
	mObjects.erase(static_cast<ISceneElementImp*>(element));
}

Void NSDevilX::NSRenderSystem::IVisibleAreaImp::_updateWorldAABB()
{
	notify(EMessage_BeginWorldBoundingBoxChange);
	DirectX::XMVECTOR translate=getTransformer()?getTransformer()->getPosition():CFloat3::sZero;
	DirectX::XMVECTOR rotate=getTransformer()?getTransformer()->getOrientation():CFloat4::sIdentityQuaternion;
	DirectX::XMVECTOR scale=getTransformer()?getTransformer()->getScale():CFloat3::sOne;
	auto trans=DirectX::XMMatrixScalingFromVector(scale)*DirectX::XMMatrixRotationQuaternion(rotate)*DirectX::XMMatrixTranslationFromVector(translate);
	mLocalAABB.Transform(mWorldAABB,trans);
	notify(EMessage_EndWorldBoundingBoxChange);
}

Void NSDevilX::NSRenderSystem::IVisibleAreaImp::onMessage(ITransformerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITransformerImp::EMessage_EndPositionChange:
	case ITransformerImp::EMessage_EndOrientationChange:
	case ITransformerImp::EMessage_EndScaleChange:
		addDirtyFlag(EDirtyFlag_WorldAABB);
		break;
	}
}

Boolean NSDevilX::NSRenderSystem::IVisibleAreaImp::_process(UInt32 flagIndex,OUT Bool & needNextProcess)
{
	switch(flagIndex)
	{
	case EDirtyFlag_WorldAABB:
		_updateWorldAABB();
		return true;
	}
	return false;
}
