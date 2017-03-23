#pragma once
#include "CommonType.h"
#include "CommonVectorI.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CDesktop
		:public TBaseObject<CDesktop>
	{
	public:
		CDesktop();
		~CDesktop();
		VoidPtr getHandle()const;
		CUInt2 getSize();
	};
	class CWindow;
	class CWindowEventListener
	{
	public:
		enum EMouseButtonType
		{
			EButtonType_Left,
			EButtonType_Right,
			EButtonType_Middle,
		};
		enum EMouseButtonEventType
		{
			EButtonEventType_ButtonUp,
			EButtonEventType_ButtonDown,
			EButtonEventType_ButtonDoubleClick
		};
	protected:
		virtual ~CWindowEventListener(){}
	public:
		virtual Void onCharEvent(CWindow * window,const CUTF8Char & ch){}
		virtual Void onButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position){}
	};
	class CWindow
		:public TBaseObject<CWindow>
	{
	protected:
		VoidPtr mHandle;
		CInt2 mPosition;
		CUInt2 mSize;
		CWindowEventListener * mEventListener;
	public:
		CWindow();
		~CWindow();
		VoidPtr getHandle()const
		{
			return mHandle;
		}
		Void setPosition(const CInt2 & position);
		const CInt2 & getPosition()const
		{
			return mPosition;
		}
		Void setSize(const CUInt2 & size);
		const CUInt2 & getSize()const
		{
			return mSize;
		}
		Void setEventListener(CWindowEventListener * listener);
		CWindowEventListener * getEventListener()const
		{
			return mEventListener;
		}
	};
}