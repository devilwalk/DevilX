#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
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
		delete(mListenerList[mCurrentListenerListIndex]);
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
		delete(mListenerList[1-mCurrentListenerListIndex]);
	}
}
UInt32 CMessageSource::getMessage() const
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
CMessageSource::ListenerList & CMessageSource::_getCurrentListenerList()
{
	if(!mListenerList[mCurrentListenerListIndex])
		mListenerList[mCurrentListenerListIndex]=new ListenerList;
	return *mListenerList[mCurrentListenerListIndex];
}
CMessageSource::ListenerList & CMessageSource::_getNextListenerList()
{
	if(!mListenerList[1-mCurrentListenerListIndex])
		mListenerList[1-mCurrentListenerListIndex]=new ListenerList;
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
	delete(mSourceList);
}
Void CMessageListener::addSource(CMessageSource * source)
{
	_getSourceList().push_back(source);
}
Void CMessageListener::removeSource(CMessageSource * source)
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

CMessageListener::SourceList & CMessageListener::_getSourceList()
{
	// TODO: insert return statement here
	if(!mSourceList)
		mSourceList=new SourceList;
	return *mSourceList;
}

CMessageReceiver::CMessageReceiver()
	:mListenerList(nullptr)
{}

CMessageReceiver::~CMessageReceiver()
{
	if(mListenerList)
	{
		for(auto listener:_getListenerList())
			delete(listener);
		delete(mListenerList);
	}
}

CMessageListener * CMessageReceiver::getListener(UInt32 message)
{
	if(_getListenerList().size()<=message)
		_getListenerList().resize(message+1);
	if(!_getListenerList()[message])
		_getListenerList()[message]=new CMessageListener(this);
	return _getListenerList()[message];
}

Boolean CMessageReceiver::hasListener(UInt32 message) const
{
	return mListenerList&&(nullptr!=_getListenerList()[message]);
}

CMessageReceiver::ListenerList & CMessageReceiver::_getListenerList()
{
	// TODO: insert return statement here
	if(!mListenerList)
		mListenerList=new ListenerList;
	return *mListenerList;
}

const CMessageReceiver::ListenerList & CMessageReceiver::_getListenerList() const
{
	// TODO: insert return statement here
	return *mListenerList;
}

CMessageNotifier::CMessageNotifier()
	:mSourceList(nullptr)
{
}

CMessageNotifier::~CMessageNotifier()
{
	if(mSourceList)
	{
		for(auto src:_getSourceList())
			delete(src);
		delete(mSourceList);
	}
}

Void CMessageNotifier::addListener(CMessageReceiver * receiver,UInt32 message,Bool checkRepeat)
{
	_getOrCreateSource(message)->addListener(receiver->getListener(message),checkRepeat);
}

Void CMessageNotifier::removeListener(CMessageReceiver * receiver,UInt32 message)
{
	if(
		(!_getSource(message))
	   ||(!receiver->hasListener(message))
	   )
		return;
	_getSourceList()[message]->removeListener(receiver->getListener(message));
}

Void CMessageNotifier::notify(UInt32 message,VoidPtr data)const
{
	if(!_getSource(message))
	{
		return;
	}
	_getSource(message)->notify(data);
}

CMessageSource * CMessageNotifier::_getOrCreateSource(UInt32 message)
{
	if(_getSourceList().size()<=message)
		_getSourceList().resize(message+1);
	if(!_getSourceList()[message])
		_getSourceList()[message]=new CMessageSource(message,this);
	return _getSourceList()[message];
}

CMessageSource * CMessageNotifier::_getSource(UInt32 message) const
{
	if((!mSourceList)||(_getSourceList().size()<=message))
		return nullptr;
	else
		return _getSourceList()[message];
}

CMessageNotifier::SourceList & CMessageNotifier::_getSourceList()
{
	// TODO: insert return statement here
	if(!mSourceList)
		mSourceList=new SourceList;
	return *mSourceList;
}

const CMessageNotifier::SourceList & CMessageNotifier::_getSourceList() const
{
	// TODO: insert return statement here
	return *mSourceList;
}
