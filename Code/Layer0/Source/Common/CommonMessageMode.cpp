#include "Precompiler.h"
using namespace NSDevilX;
CMessageSource::CMessageSource(UInt32 message,CMessageNotifier * notifier)
	:mMessage(message)
	,mNotifier(notifier)
	,mNotifyListenersWhenDestruction(True)
	,mCurrentListenerListIndex(0)
	,mNotifing(nullptr)
{
	mListenerList[0]=nullptr;
	mListenerList[1]=nullptr;
}
CMessageSource::~CMessageSource()
{
	//不允许在通知的时候被删除
	assert(nullptr==mNotifing);
	if(mListenerList[mCurrentListenerListIndex])
	{
		if(mNotifyListenersWhenDestruction)
		{
			for(auto listener:_getCurrentListenerList())
			{
				listener->onSourceDestruction(this);
			}
		}
		DEVILX_DELETE(mListenerList[mCurrentListenerListIndex]);
	}
	if(mListenerList[1-mCurrentListenerListIndex])
	{
		if(mNotifyListenersWhenDestruction)
		{
			for(auto listener:_getNextListenerList())
			{
				listener->onSourceDestruction(this);
			}
		}
		DEVILX_DELETE(mListenerList[1-mCurrentListenerListIndex]);
	}
}
UInt32 NSDevilX::CMessageSource::getMessage() const
{
	return mMessage;
}
Void CMessageSource::addListener(CMessageListener * listener,Bool checkRepeat)
{
	if(checkRepeat&&_getCurrentListenerList().has(listener))
		return;
	_getCurrentListenerList().push_back(listener);
	listener->addSource(this);
}
Void CMessageSource::removeListener(CMessageListener * listener,Bool removeSource)
{
	if(mNotifing)
	{
		if(mNotifing==listener)
		{
			_getNextListenerList().pop_back();
		}
		else
		{
			if(!_getCurrentListenerList().remove(listener))
			{
				_getNextListenerList().remove(listener);
			}
		}
	}
	else
		_getCurrentListenerList().remove(listener);
	if(removeSource)
		listener->removeSource(this);
}
Void CMessageSource::notify(VoidPtr data)
{
	//一定要避免在通知里把自己删除的情况
	Bool need_next_process=True;
	while(need_next_process&&(!_getCurrentListenerList().empty()))
	{
		mNotifing=_getCurrentListenerList().back();
		_getCurrentListenerList().pop_back();
		_getNextListenerList().push_back(mNotifing);
		mNotifing->onMessage(this,data,need_next_process);
	}
	mCurrentListenerListIndex=1-mCurrentListenerListIndex;
	mNotifing=nullptr;
}
Void CMessageSource::onListenerDestruction(CMessageListener * listener)
{
	removeListener(listener,False);
}
CMessageSource::ListenerList & NSDevilX::CMessageSource::_getCurrentListenerList()
{
	if(!mListenerList[mCurrentListenerListIndex])
		mListenerList[mCurrentListenerListIndex]=DEVILX_NEW ListenerList;
	return *mListenerList[mCurrentListenerListIndex];
}
CMessageSource::ListenerList & NSDevilX::CMessageSource::_getNextListenerList()
{
	if(!mListenerList[1-mCurrentListenerListIndex])
		mListenerList[1-mCurrentListenerListIndex]=DEVILX_NEW ListenerList;
	return *mListenerList[1-mCurrentListenerListIndex];
}
CMessageNotifier * CMessageSource::getNotifier()const
{
	return mNotifier;
}

CMessageListener::CMessageListener(CMessageReceiver * receiver)
	:mReceiver(receiver)
	,mNotifySourceWhenDestruction(True)
	,mSourceList(nullptr)
{}
CMessageListener::~CMessageListener()
{
	if(mNotifySourceWhenDestruction)
	{
		if(mSourceList)
		{
			for(auto source:_getSourceList())
			{
				source->onListenerDestruction(this);
			}
		}
	}
	DEVILX_DELETE(mSourceList);
}
Void NSDevilX::CMessageListener::addSource(CMessageSource * source)
{
	_getSourceList().push_back(source);
}
Void NSDevilX::CMessageListener::removeSource(CMessageSource * source)
{
	_getSourceList().remove(source);
}
Void CMessageListener::onSourceDestruction(CMessageSource * source)
{
	removeSource(source);
}
Void CMessageListener::onMessage(CMessageSource * source,VoidPtr data,Bool & needNextProcess)
{
	mReceiver->onMessage(source->getNotifier(),source->getMessage(),data,needNextProcess);
}

CMessageListener::SourceList & NSDevilX::CMessageListener::_getSourceList()
{
	// TODO: insert return statement here
	if(!mSourceList)
		mSourceList=DEVILX_NEW SourceList;
	return *mSourceList;
}

NSDevilX::CMessageReceiver::CMessageReceiver()
	:mListenerList(nullptr)
{}

NSDevilX::CMessageReceiver::~CMessageReceiver()
{
	if(mListenerList)
	{
		for(auto listener:_getListenerList())
			DEVILX_DELETE(listener);
		DEVILX_DELETE(mListenerList);
	}
}

CMessageListener * NSDevilX::CMessageReceiver::getListener(UInt32 message)
{
	if(_getListenerList().size()<=message)
		_getListenerList().resize(message+1);
	if(!_getListenerList()[message])
		_getListenerList()[message]=DEVILX_NEW CMessageListener(this);
	return _getListenerList()[message];
}

Boolean NSDevilX::CMessageReceiver::hasListener(UInt32 message) const
{
	return mListenerList&&(nullptr!=_getListenerList()[message]);
}

CMessageReceiver::ListenerList & NSDevilX::CMessageReceiver::_getListenerList()
{
	// TODO: insert return statement here
	if(!mListenerList)
		mListenerList=DEVILX_NEW ListenerList;
	return *mListenerList;
}

const CMessageReceiver::ListenerList & NSDevilX::CMessageReceiver::_getListenerList() const
{
	// TODO: insert return statement here
	return *mListenerList;
}

NSDevilX::CMessageNotifier::CMessageNotifier()
	:mSourceList(nullptr)
{
}

NSDevilX::CMessageNotifier::~CMessageNotifier()
{
	if(mSourceList)
	{
		for(auto src:_getSourceList())
			DEVILX_DELETE(src);
		DEVILX_DELETE(mSourceList);
	}
}

Void NSDevilX::CMessageNotifier::addListener(CMessageReceiver * receiver,UInt32 message,Bool checkRepeat)
{
	_getOrCreateSource(message)->addListener(receiver->getListener(message),checkRepeat);
}

Void NSDevilX::CMessageNotifier::removeListener(CMessageReceiver * receiver,UInt32 message)
{
	if(
		(!_getSource(message))
	   ||(!receiver->hasListener(message))
	   )
		return;
	_getSourceList()[message]->removeListener(receiver->getListener(message));
}

Void NSDevilX::CMessageNotifier::notify(UInt32 message,VoidPtr data)const
{
	if(!_getSource(message))
	{
		return;
	}
	_getSource(message)->notify(data);
}

CMessageSource * NSDevilX::CMessageNotifier::_getOrCreateSource(UInt32 message)
{
	if(_getSourceList().size()<=message)
		_getSourceList().resize(message+1);
	if(!_getSourceList()[message])
		_getSourceList()[message]=DEVILX_NEW CMessageSource(message,this);
	return _getSourceList()[message];
}

CMessageSource * NSDevilX::CMessageNotifier::_getSource(UInt32 message) const
{
	if((!mSourceList)||(_getSourceList().size()<=message))
		return nullptr;
	else
		return _getSourceList()[message];
}

CMessageNotifier::SourceList & NSDevilX::CMessageNotifier::_getSourceList()
{
	// TODO: insert return statement here
	if(!mSourceList)
		mSourceList=DEVILX_NEW SourceList;
	return *mSourceList;
}

const CMessageNotifier::SourceList & NSDevilX::CMessageNotifier::_getSourceList() const
{
	// TODO: insert return statement here
	return *mSourceList;
}
