#include "Precompiler.h"
using namespace NSDevilX;
CMessageSource::CMessageSource(UInt32 message,CMessageNotifier * notifier)
	:mMessage(message)
	,mNotifier(notifier)
	,mNotifyListenersWhenDestruction(True)
{
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
				static_cast<CMessageListener*>(listener)->onSourceDestruction(this);
			}
		}
	}
	if(mListenerList[1-mCurrentListenerListIndex])
	{
		if(mNotifyListenersWhenDestruction)
		{
			for(auto listener:_getNextListenerList())
			{
				static_cast<CMessageListener*>(listener)->onSourceDestruction(this);
			}
		}
	}
}
UInt32 NSDevilX::CMessageSource::getMessage() const
{
	return mMessage;
}
Void CMessageSource::addListener(CMessageListener * listener,Bool checkRepeat)
{
	if(CObserverSource::addListener(listener,checkRepeat))
		listener->addSource(this);
}
Void CMessageSource::removeListener(CMessageListener * listener,Bool removeSource)
{
	CObserverSource::removeListener(listener);
	if(removeSource)
		listener->removeSource(this);
}
Void CMessageSource::onListenerDestruction(CMessageListener * listener)
{
	removeListener(listener,False);
}
Void NSDevilX::CMessageSource::_notify(VoidPtr data,Bool & needNextProcess)
{
	static_cast<CMessageListener*>(mNotifing)->onMessage(this,data,needNextProcess);
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
		mSourceList=new SourceList;
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
			delete(listener);
		delete(mListenerList);
	}
}

CMessageListener * NSDevilX::CMessageReceiver::getListener(UInt32 message)
{
	if(_getListenerList().size()<=message)
		_getListenerList().resize(message+1);
	if(!_getListenerList()[message])
		_getListenerList()[message]=new CMessageListener(this);
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
		mListenerList=new ListenerList;
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
			delete(src);
		delete(mSourceList);
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
		_getSourceList()[message]=new CMessageSource(message,this);
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
		mSourceList=new SourceList;
	return *mSourceList;
}

const CMessageNotifier::SourceList & NSDevilX::CMessageNotifier::_getSourceList() const
{
	// TODO: insert return statement here
	return *mSourceList;
}
