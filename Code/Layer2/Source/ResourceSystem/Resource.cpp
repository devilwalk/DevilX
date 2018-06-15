#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;

NSDevilX::NSResourceSystem::CResource::CResource()
	:mLoadState(ELoadState_Unload)
	,mLoadThreadSyncGroupID(-1)
	,mReplacedLoadStateMT(nullptr)
{}

NSDevilX::NSResourceSystem::CResource::~CResource()
{
	if(-1!=mLoadThreadSyncGroupID)
		ISystemImp::getSingleton().getIOPool()->waitMT(mLoadThreadSyncGroupID);
}

Void NSDevilX::NSResourceSystem::CResource::load(SLoadCallback * callback,Bool sync)
{
	_updateLoadState();
	switch(mLoadState)
	{
	case ELoadState_Unload:
		mLoadState=ELoadState_Loading;
		mLoadThreadSyncGroupID=ISystemImp::getSingleton().getIOPool()->nextSyncGroupID();
		ISystemImp::getSingleton().getIOPool()->submitMT(
			[](VoidPtr parameter)
		{
			auto res=static_cast<CResource*>(parameter);
			if(res->_loadImpMT())
			{
				auto write_value=static_cast<CResource::ELoadState*>(DEVILX_ALLOC(sizeof(CResource::ELoadState)));
				*write_value=CResource::ELoadState_Loaded;
				res->mReplacedLoadStateMT.write(write_value);
			}
		}
		,this,mLoadThreadSyncGroupID);
		if(False==sync)
			ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Update);
		if(callback)
			mLoadCallbacks.push_back(callback);
		break;
	case ELoadState_Loading:
		if(callback)
			mLoadCallbacks.push_back(callback);
		break;
	case ELoadState_Loaded:
		if(callback)
			callback->onLoaded(this);
		break;
	}
	if(sync)
	{
		if(!isLoaded())
		{
			Sleep(10);
			load(nullptr,True);
		}
		else
		{
			for(auto callback:mLoadCallbacks)
				callback->onLoaded(this);
			mLoadCallbacks.clear();
		}
	}
}

Boolean NSDevilX::NSResourceSystem::CResource::isLoaded() const
{
	return mLoadState==ELoadState_Loaded;
}

Void NSDevilX::NSResourceSystem::CResource::_updateLoadState()
{
	auto & replace_value=mReplacedLoadStateMT.beginWrite();
	if(replace_value)
	{
		mLoadState=*replace_value;
		mLoadThreadSyncGroupID=-1;
		replace_value=nullptr;
	}
	mReplacedLoadStateMT.endWrite();
}

Void NSDevilX::NSResourceSystem::CResource::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
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
