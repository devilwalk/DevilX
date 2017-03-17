#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;

NSDevilX::NSResourceSystem::IResourceImp::IResourceImp(const String & name,const String & file)
	:mName(name)
	,mFile(file)
	,mLoadState(ELoadState_Unload)
	,mLoadThreadSyncGroupID(-1)
{}

NSDevilX::NSResourceSystem::IResourceImp::~IResourceImp()
{
	if(-1!=mLoadThreadSyncGroupID)
		ISystemImp::getSingleton().getIOPool()->waitMT(mLoadThreadSyncGroupID);
	DEVILX_DELETE(mBuffer);
}

Void NSDevilX::NSResourceSystem::IResourceImp::setDataStreamMT(CMemoryStream * stream)
{
	mBuffer.write(stream);
}

const String & NSDevilX::NSResourceSystem::IResourceImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

const String & NSDevilX::NSResourceSystem::IResourceImp::getFileName() const
{
	// TODO: 在此处插入 return 语句
	return mFile;
}

Void NSDevilX::NSResourceSystem::IResourceImp::load(ILoadCallback * callback)
{
	_updateLoadState();
	switch(mLoadState)
	{
	case ELoadState_Unload:
		mLoadThreadSyncGroupID=ISystemImp::getSingleton().getIOPool()->nextSyncGroupID();
		ISystemImp::getSingleton().getIOPool()->submitMT(IOFunction,this,mLoadThreadSyncGroupID);
		ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Update);
		mLoadState=ELoadState_Loading;
		break;
	case ELoadState_Loading:
		mLoadCallbacks.push_back(callback);
		break;
	case ELoadState_Loaded:
		callback->onLoaded(this);
		break;
	}
}

Bool NSDevilX::NSResourceSystem::IResourceImp::isLoaded() const
{
	return mLoadState==ELoadState_Loaded;
}

IResource * NSDevilX::NSResourceSystem::IResourceImp::queryInterface_IResource() const
{
	return const_cast<IResourceImp*>(this);
}

Void NSDevilX::NSResourceSystem::IResourceImp::_updateLoadState()
{
	if(ELoadState_Loading==mLoadState)
	{
		auto buffer=mBuffer.beginRead();
		if(buffer)
		{
			mLoadState=ELoadState_Loaded;
			mLoadThreadSyncGroupID=-1;
		}
		mBuffer.endRead();
	}
}

Void NSDevilX::NSResourceSystem::IResourceImp::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		_updateLoadState();
		if(isLoaded())
		{
			for(auto callback:mLoadCallbacks)
				callback->onLoaded(this);
			mLoadCallbacks.clear();
			ISystemImp::getSingleton().removeListener(this,ISystemImp::EMessage_Update);
		}
		break;
	}
}
