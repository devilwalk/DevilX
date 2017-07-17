#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CQueryObjectManager::CQueryObjectManager(CSceneImp * scene)
	:mScene(scene)
{
	mScene->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_EndQueryObjectCreate);
	mScene->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISceneImp>*>(this),ISceneImp::EMessage_BeginQueryObjectDestroy);
}

NSDevilX::NSRenderSystem::NSD3D11::CQueryObjectManager::~CQueryObjectManager()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CQueryObjectManager::onMessage(ISceneImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISceneImp::EMessage_EndQueryObjectCreate:
		_addObject(static_cast<IQueryObjectImp*>(data));
		static_cast<IQueryObjectImp*>(data)->addListener(static_cast<TMessageReceiver<IQueryObjectImp>*>(this),IQueryObjectImp::EMessage_BeginGeometryChange);
		static_cast<IQueryObjectImp*>(data)->addListener(static_cast<TMessageReceiver<IQueryObjectImp>*>(this),IQueryObjectImp::EMessage_EndGeometryChange);
		static_cast<IQueryObjectImp*>(data)->addListener(static_cast<TMessageReceiver<IQueryObjectImp>*>(this),IQueryObjectImp::EMessage_EndVisibleChange);
		break;
	case ISceneImp::EMessage_BeginQueryObjectDestroy:
		_removeObject(static_cast<IQueryObjectImp*>(data));
		static_cast<IQueryObjectImp*>(data)->removeListener(static_cast<TMessageReceiver<IQueryObjectImp>*>(this),IQueryObjectImp::EMessage_BeginGeometryChange);
		static_cast<IQueryObjectImp*>(data)->removeListener(static_cast<TMessageReceiver<IQueryObjectImp>*>(this),IQueryObjectImp::EMessage_EndGeometryChange);
		static_cast<IQueryObjectImp*>(data)->removeListener(static_cast<TMessageReceiver<IQueryObjectImp>*>(this),IQueryObjectImp::EMessage_EndVisibleChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CQueryObjectManager::onMessage(IQueryObjectImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IQueryObjectImp::EMessage_EndVisibleChange:
		if(!notifier->getVisible())
			_removeObject(notifier);
		break;
	case IQueryObjectImp::EMessage_BeginGeometryChange:
		_removeObject(notifier);
		break;
	case IQueryObjectImp::EMessage_EndGeometryChange:
		_addObject(notifier);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CQueryObjectManager::_addObject(IQueryObjectImp * obj)
{
	if(!obj->getGeometry())
		return;
	Boolean merged=false;
	for(auto renderable:mRenderables)
	{
		if(renderable->merge(obj))
		{
			merged=true;
			break;
		}
	}
	if(!merged)
	{
		auto renderable=DEVILX_NEW CQueryObjectRenderable;
		renderable->merge(obj);
		mRenderables.push_back(renderable);
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CQueryObjectManager::_removeObject(IQueryObjectImp * obj)
{
	if(!obj->getGeometry())
		return;
	auto geo=CSystemImp::getSingleton().getGeometry(static_cast<IGeometryImp*>(obj->getGeometry()));
}
