#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CEntityImp::CEntityImp(IEntityImp * interfaceImp)
	:TInterfaceObject<IEntityImp>(interfaceImp)
	,mScene(CSystemImp::getSingleton().getScene(static_cast<ISceneImp*>(static_cast<ISceneElementImp*>(interfaceImp->queryInterface_ISceneElement())->getScene())))
	,mTransformer(nullptr)
{
	_updateTransformer();
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityImp>*>(this),IEntityImp::EMessage_EndSubEntityCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IEntityImp>*>(this),IEntityImp::EMessage_BeginSubEntityDestroy);
	static_cast<ISceneElementImp*>(getInterfaceImp()->queryInterface_ISceneElement())->addListener(static_cast<TMessageReceiver<ISceneElementImp>*>(this),ISceneElementImp::EMessage_EndTransformerChange);
}

NSDevilX::NSRenderSystem::NSD3D11::CEntityImp::~CEntityImp()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityImp::onMessage(IEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IEntityImp::EMessage_EndSubEntityCreate:
	{
		auto renderable=DEVILX_NEW CSubEntityImp(static_cast<ISubEntityImp*>(data),this);
		mSubEntities[static_cast<ISubEntityImp*>(data)]=renderable;
	}
	break;
	case IEntityImp::EMessage_BeginSubEntityDestroy:
		mSubEntities.destroy(static_cast<ISubEntityImp*>(data));
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityImp::onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISceneElementImp::EMessage_EndTransformerChange:
		_updateTransformer();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityImp::_updateTransformer()
{
	mTransformer=nullptr;
	if(static_cast<ITransformerImp*>(getInterfaceImp()->queryInterface_ISceneElement()->getTransformer()))
	{
		if(CSystemImp::getSingleton().getTransformer(static_cast<ITransformerImp*>(getInterfaceImp()->queryInterface_ISceneElement()->getTransformer())))
		{
			mTransformer=CSystemImp::getSingleton().getTransformer(static_cast<ITransformerImp*>(getInterfaceImp()->queryInterface_ISceneElement()->getTransformer()));
		}
		else
		{
			mTransformer=CSystemImp::getSingleton().createTransformer(static_cast<ITransformerImp*>(getInterfaceImp()->queryInterface_ISceneElement()->getTransformer()));
		}
	}
}
