#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CRenderableObject::CRenderableObject(IRenderableObjectImp * interfaceImp)
	:TInterfaceObject<IRenderableObjectImp>(interfaceImp)
	,mScene(CSystemImp::getSingleton().getScene(static_cast<ISceneImp*>(static_cast<ISceneElementImp*>(interfaceImp->queryInterface_ISceneElement())->getScene())))
	,mTransformer(nullptr)
{
	_updateTransformer();
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IRenderableObjectImp>*>(this),IRenderableObjectImp::EMessage_EndRenderableCreate);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<IRenderableObjectImp>*>(this),IRenderableObjectImp::EMessage_BeginRenderableDestroy);
	static_cast<ISceneElementImp*>(getInterfaceImp()->queryInterface_ISceneElement())->addListener(static_cast<TMessageReceiver<ISceneElementImp>*>(this),ISceneElementImp::EMessage_EndTransformerChange);
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderableObject::~CRenderableObject()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderableObject::onMessage(IRenderableObjectImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IRenderableObjectImp::EMessage_EndRenderableCreate:
	{
		auto renderable=DEVILX_NEW CRenderable(static_cast<IRenderableImp*>(data),this);
		mRenderables[static_cast<IRenderableImp*>(data)]=renderable;
	}
	break;
	case IRenderableObjectImp::EMessage_BeginRenderableDestroy:
		mRenderables.destroy(static_cast<IRenderableImp*>(data));
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderableObject::onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISceneElementImp::EMessage_EndTransformerChange:
		_updateTransformer();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderableObject::_updateTransformer()
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
