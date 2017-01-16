#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::IGeometryImp::IGeometryImp(const String & name)
	:mName(name)
	,mVertexBuffer(nullptr)
	,mIndexBuffer(nullptr)
{
	setVertexBuffer(DEVILX_NEW IVertexBufferImp());
	setIndexBuffer(DEVILX_NEW IIndexBufferImp());
	mVertexBuffer->release();
	mIndexBuffer->release();
}

NSDevilX::NSRenderSystem::IGeometryImp::~IGeometryImp()
{
	_unregisterToIIndexBufferImp();
	_unregisterToIVertexBufferImp();
	mVertexBuffer->release();
	mIndexBuffer->release();
}

const String & NSDevilX::NSRenderSystem::IGeometryImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

Void NSDevilX::NSRenderSystem::IGeometryImp::setVertexBuffer(IVertexBuffer * buffer)
{
	if(!buffer)
		buffer=DEVILX_NEW IVertexBufferImp();
	if(buffer!=getVertexBuffer())
	{
		notify(EMessage_BeginVertexBufferChange);
		if(getVertexBuffer())
		{
			_unregisterToIVertexBufferImp();
			mVertexBuffer->release();
		}
		mVertexBuffer=static_cast<IVertexBufferImp*>(buffer);
		mVertexBuffer->addRef();
		_registerToIVertexBufferImp();
		notify(EMessage_EndVertexBufferChange);
	}
}

IVertexBuffer * NSDevilX::NSRenderSystem::IGeometryImp::getVertexBuffer() const
{
	return mVertexBuffer;
}

Void NSDevilX::NSRenderSystem::IGeometryImp::setIndexBuffer(IIndexBuffer * buffer)
{
	if(!buffer)
		buffer=DEVILX_NEW IIndexBufferImp();
	if(buffer!=getIndexBuffer())
	{
		notify(EMessage_BeginIndexBufferChange);
		if(getIndexBuffer())
		{
			_unregisterToIIndexBufferImp();
			mIndexBuffer->release();
		}
		mIndexBuffer=static_cast<IIndexBufferImp*>(buffer);
		mIndexBuffer->addRef();
		_registerToIIndexBufferImp();
		notify(EMessage_EndIndexBufferChange);
	}
}

IIndexBuffer * NSDevilX::NSRenderSystem::IGeometryImp::getIndexBuffer() const
{
	return mIndexBuffer;
}

Void NSDevilX::NSRenderSystem::IGeometryImp::_registerToIVertexBufferImp()
{
	mVertexBuffer->addListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_BeginDiffuseEnableChange);
	mVertexBuffer->addListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_BeginNormalEnableChange);
	mVertexBuffer->addListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_BeginTangentEnableChange);
	mVertexBuffer->addListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_BeginTextureCoord0EnableChange);
	mVertexBuffer->addListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_BeginTextureCoord1EnableChange);
	mVertexBuffer->addListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndDiffuseEnableChange);
	mVertexBuffer->addListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndDirtyFlagAdd);
	mVertexBuffer->addListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndNormalEnableChange);
	mVertexBuffer->addListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndTangentEnableChange);
	mVertexBuffer->addListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndTextureCoord0EnableChange);
	mVertexBuffer->addListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndTextureCoord1EnableChange);
}

Void NSDevilX::NSRenderSystem::IGeometryImp::_unregisterToIVertexBufferImp()
{
	mVertexBuffer->removeListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_BeginDiffuseEnableChange);
	mVertexBuffer->removeListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_BeginNormalEnableChange);
	mVertexBuffer->removeListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_BeginTangentEnableChange);
	mVertexBuffer->removeListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_BeginTextureCoord0EnableChange);
	mVertexBuffer->removeListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_BeginTextureCoord1EnableChange);
	mVertexBuffer->removeListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndDiffuseEnableChange);
	mVertexBuffer->removeListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndDirtyFlagAdd);
	mVertexBuffer->removeListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndNormalEnableChange);
	mVertexBuffer->removeListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndTangentEnableChange);
	mVertexBuffer->removeListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndTextureCoord0EnableChange);
	mVertexBuffer->removeListener(static_cast<TMessageReceiver<IVertexBufferImp>*>(this),IVertexBufferImp::EMessage_EndTextureCoord1EnableChange);
}

Void NSDevilX::NSRenderSystem::IGeometryImp::_registerToIIndexBufferImp()
{
}

Void NSDevilX::NSRenderSystem::IGeometryImp::_unregisterToIIndexBufferImp()
{
}

Void NSDevilX::NSRenderSystem::IGeometryImp::onMessage(IVertexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IVertexBufferImp::EMessage_BeginDiffuseEnableChange:
		notify(EMessage_BeginDiffuseEnableChange);
		break;
	case IVertexBufferImp::EMessage_BeginNormalEnableChange:
		notify(EMessage_BeginNormalEnableChange);
		break;
	case IVertexBufferImp::EMessage_BeginTangentEnableChange:
		notify(EMessage_BeginTangentEnableChange);
		break;
	case IVertexBufferImp::EMessage_BeginTextureCoord0EnableChange:
		notify(EMessage_BeginTextureCoord0EnableChange);
		break;
	case IVertexBufferImp::EMessage_BeginTextureCoord1EnableChange:
		notify(EMessage_BeginTextureCoord1EnableChange);
		break;
	case IVertexBufferImp::EMessage_EndDiffuseEnableChange:
		notify(EMessage_EndDiffuseEnableChange);
		break;
	case IVertexBufferImp::EMessage_EndNormalEnableChange:
		notify(EMessage_EndNormalEnableChange);
		break;
	case IVertexBufferImp::EMessage_EndTangentEnableChange:
		notify(EMessage_EndTangentEnableChange);
		break;
	case IVertexBufferImp::EMessage_EndTextureCoord0EnableChange:
		notify(EMessage_EndTextureCoord0EnableChange);
		break;
	case IVertexBufferImp::EMessage_EndTextureCoord1EnableChange:
		notify(EMessage_EndTextureCoord1EnableChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::IGeometryImp::onMessage(IIndexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
}
