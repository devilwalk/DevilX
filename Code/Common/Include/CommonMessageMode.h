#pragma once
#include "CommonConstant.h"
#include "CommonSTL.h"
namespace NSDevilX
{
	class CObserverSource
	{
	public:
		typedef TList<VoidPtr> ListenerList;
	protected:
		VoidPtr mNotifing;
		ListenerList * mListenerList[2];
		UInt32 mCurrentListenerListIndex;
	public:
		CObserverSource()
		{
			mListenerList[0]=nullptr;
			mListenerList[1]=nullptr;
		}
		virtual ~CObserverSource()
		{	//不允许在通知的时候被删除
			assert(nullptr==mNotifing);
			delete(mListenerList[mCurrentListenerListIndex]);
			delete(mListenerList[1-mCurrentListenerListIndex]);
		}
		Boolean addListener(VoidPtr listener,Bool checkRepeat=True)
		{
			if(checkRepeat&&_getCurrentListenerList().has(listener))
				return false;
			_getCurrentListenerList().push_back(listener);
			return true;
		}
		Void removeListener(VoidPtr listener)
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
		}
		Void notify(VoidPtr data)
		{
			//一定要避免在通知里把自己删除的情况
			Bool need_next_process=True;
			while(need_next_process&&(!_getCurrentListenerList().empty()))
			{
				mNotifing=_getCurrentListenerList().back();
				_getCurrentListenerList().pop_back();
				_getNextListenerList().push_back(mNotifing);
				_notify(data,need_next_process);
			}
			mCurrentListenerListIndex=1-mCurrentListenerListIndex;
			mNotifing=nullptr;
		}
	protected:
		ListenerList&_getCurrentListenerList()
		{
			if(!mListenerList[mCurrentListenerListIndex])
				mListenerList[mCurrentListenerListIndex]=new ListenerList;
			return *mListenerList[mCurrentListenerListIndex];
		}
		ListenerList & _getNextListenerList()
		{
			if(!mListenerList[1-mCurrentListenerListIndex])
				mListenerList[1-mCurrentListenerListIndex]=new ListenerList;
			return *mListenerList[1-mCurrentListenerListIndex];
		}
		virtual Void _notify(VoidPtr data,Bool & needNextProcess)=0;
	};

	class CMessageSource;
	class CMessageListener;
	class CMessageNotifier;
	class CMessageReceiver;
	class CMessageSource
		:public CObserverSource
	{
	protected:
		CMessageNotifier * const mNotifier;
		Bool mNotifyListenersWhenDestruction:1;
		const UInt32 mMessage:31;
	public:
		CMessageSource(UInt32 message,CMessageNotifier * notifier);
		~CMessageSource();
		UInt32 getMessage()const;
		CMessageNotifier * getNotifier()const;
		Void addListener(CMessageListener * listener,Bool checkRepeat=True);
		Void removeListener(CMessageListener * listener,Bool removeSource=True);
		Void onListenerDestruction(CMessageListener * listener);
	protected:
		virtual Void _notify(VoidPtr data,Bool & needNextProcess) override;
	};
	class CMessageListener
	{
	public:
		typedef TList<CMessageSource*> SourceList;
	protected:
		CMessageReceiver * mReceiver;
		SourceList * mSourceList;
		Bool mNotifySourceWhenDestruction;
	public:
		CMessageListener(CMessageReceiver * receiver);
		~CMessageListener();
		Void addSource(CMessageSource * source);
		Void removeSource(CMessageSource * source);
		Void onSourceDestruction(CMessageSource * source);
		Void onMessage(CMessageSource * source,VoidPtr data,Bool & needNextProcess);
	protected:
		SourceList & _getSourceList();
	};
	class CMessageReceiver
	{
	public:
		typedef TVector<CMessageListener*> ListenerList;
	protected:
		ListenerList * mListenerList;
	public:
		CMessageReceiver();
		virtual ~CMessageReceiver();
		CMessageListener * getListener(UInt32 message);
		Boolean hasListener(UInt32 message)const;
		virtual Void onMessage(CMessageNotifier * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)=0;
	protected:
		ListenerList & _getListenerList();
		const ListenerList & _getListenerList()const;
	};
	template<class NotifierT>
	class TMessageReceiver
		:public CMessageReceiver
	{
	public:
		TMessageReceiver()
		{
		}
		virtual ~TMessageReceiver(){}
		virtual Void onMessage(CMessageNotifier * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)final
		{
			onMessage(static_cast<NotifierT*>(notifier),message,data,needNextProcess);
		}
		virtual Void onMessage(NotifierT * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)=0;
	};
	template<>
	class TMessageReceiver<CMessageNotifier>
		:public CMessageReceiver
	{
	public:
		TMessageReceiver()
		{}
		virtual ~TMessageReceiver()
		{}
		virtual Void onMessage(CMessageNotifier * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)=0;
	};
	class CMessageNotifier
	{
	public:
		typedef TVector<CMessageSource*> SourceList;
	protected:
		SourceList * mSourceList;
	public:
		CMessageNotifier();
		virtual ~CMessageNotifier();
		Void addListener(CMessageReceiver * receiver,UInt32 message,Bool checkRepeat=True);
		Void removeListener(CMessageReceiver * receiver,UInt32 message);
		Void notify(UInt32 message,VoidPtr data=0)const;
	protected:
		CMessageSource * _getOrCreateSource(UInt32 message);
		CMessageSource * _getSource(UInt32 message)const;
		SourceList & _getSourceList();
		const SourceList & _getSourceList()const;
	};
}