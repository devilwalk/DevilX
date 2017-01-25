#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::ISceneElementImp::ISceneElementImp(const String & name,ISceneImp * scene,VoidPtr containerObject,EContainerObjectType type)
	:mName(name)
	,mScene(scene)
	,mContainerObject(containerObject)
	,mContainerObjectType(type)
	,mTransformer(nullptr)
{
	mTransformer=DEVILX_NEW ITransformerImp();
	_registerToITransformerImp();
}

NSDevilX::NSRenderSystem::ISceneElementImp::~ISceneElementImp()
{
	mTransformer->release();
}

const String & NSDevilX::NSRenderSystem::ISceneElementImp::getName() const
{
	return mName;
}

IScene * NSDevilX::NSRenderSystem::ISceneElementImp::getScene() const
{
	return mScene;
}

Void NSDevilX::NSRenderSystem::ISceneElementImp::setTransformer(ITransformer * transformer)
{
	if(transformer!=mTransformer)
	{
		notify(EMessage_BeginTransformerChange);
		_unregisterToITransformerImp();
		mTransformer->release();
		mTransformer=static_cast<ITransformerImp*>(transformer);
		if(mTransformer)
			mTransformer->addRef();
		else
			mTransformer=DEVILX_NEW ITransformerImp();
		notify(EMessage_EndTransformerChange);
		_registerToITransformerImp();
	}
}

ITransformer * NSDevilX::NSRenderSystem::ISceneElementImp::getTransformer() const
{
	return mTransformer;
}

Void NSDevilX::NSRenderSystem::ISceneElementImp::onMessage(ITransformerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITransformerImp::EMessage_EndOrientationChange:
		CMessageNotifier::notify(EMessage_OrientationChange);
		break;
	case ITransformerImp::EMessage_EndPositionChange:
		CMessageNotifier::notify(EMessage_PositionChange);
		break;
	case ITransformerImp::EMessage_EndScaleChange:
		CMessageNotifier::notify(EMessage_ScaleChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::ISceneElementImp::_registerToITransformerImp()
{
	mTransformer->CMessageNotifier::addListener(static_cast<TMessageReceiver<ITransformerImp>*>(this),ITransformerImp::EMessage_EndOrientationChange);
	mTransformer->CMessageNotifier::addListener(static_cast<TMessageReceiver<ITransformerImp>*>(this),ITransformerImp::EMessage_EndPositionChange);
	mTransformer->CMessageNotifier::addListener(static_cast<TMessageReceiver<ITransformerImp>*>(this),ITransformerImp::EMessage_EndScaleChange);
}

Void NSDevilX::NSRenderSystem::ISceneElementImp::_unregisterToITransformerImp()
{
	mTransformer->CMessageNotifier::removeListener(static_cast<TMessageReceiver<ITransformerImp>*>(this),ITransformerImp::EMessage_EndOrientationChange);
	mTransformer->CMessageNotifier::removeListener(static_cast<TMessageReceiver<ITransformerImp>*>(this),ITransformerImp::EMessage_EndPositionChange);
	mTransformer->CMessageNotifier::removeListener(static_cast<TMessageReceiver<ITransformerImp>*>(this),ITransformerImp::EMessage_EndScaleChange);
}
