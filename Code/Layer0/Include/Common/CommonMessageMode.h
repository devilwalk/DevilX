#pragma once
#include "CommonConstant.h"
#include "CommonSTL.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CMessageSource;
	class CMessageListener;
	class CMessageNotifier;
	class CMessageReceiver;
	class CMessageSource
		:public TBaseObject<CMessageSource>
	{
	public:
		typedef TList<CMessageListener*> ListenerList;
	protected:
		CMessageNotifier * const mNotifier;
		CMessageListener * mNotifing;
		ListenerList * mListenerList[2];
		Bool mNotifyListenersWhenDestruction:1;
		UInt32 mCurrentListenerListIndex:1;
		const UInt32 mMessage:30;
	public:
		CMessageSource(UInt32 message,CMessageNotifier * notifier);
		~CMessageSource();
		UInt32 getMessage()const;
		CMessageNotifier * getNotifier()const;
		Void addListener(CMessageListener * listener,Bool checkRepeat=True);
		Void removeListener(CMessageListener * listener);
		Void notify(VoidPtr data);
		Void onListenerDestruction(CMessageListener * listener);
	protected:
		ListenerList & _getCurrentListenerList();
		ListenerList & _getNextListenerList();
	};
	class CMessageListener
		:public TBaseObject<CMessageListener>
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