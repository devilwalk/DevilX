#pragma once
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
			EMouseButtonType_Left,
			EMouseButtonType_Right,
			EMouseButtonType_Middle,
		};
		enum EMouseButtonEventType
		{
			EMouseButtonEventType_Up,
			EMouseButtonEventType_Down,
			EMouseButtonEventType_DoubleClick
		};
	protected:
		virtual ~CWindowEventListener(){}
	public:
		virtual Void onResize(CWindow * window)=0;
		virtual Void onCharEvent(CWindow * window,const CUTF16Char & ch)=0;
		virtual Void onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position)=0;
		virtual Void onMouseMoveEvent(CWindow * window,const CUInt2 & position)=0;
		virtual Void onMouseWheelEvent(CWindow * window,Int32 offset)=0;
	};
	class CDefaultWindowEventListener
		:public CWindowEventListener
	{
	public:
		virtual ~CDefaultWindowEventListener(){}
	public:
		virtual Void onResize(CWindow * window) override
		{}
		virtual Void onCharEvent(CWindow * window,const CUTF16Char & ch) override
		{}
		virtual Void onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position) override
		{}
		virtual Void onMouseMoveEvent(CWindow * window,const CUInt2 & position) override
		{}
		virtual Void onMouseWheelEvent(CWindow * window,Int32 offset) override
		{}
	};
	class CWindow
		:public TBaseObject<CWindow>
	{
	protected:
		VoidPtr mHandle;
		CInt2 mPosition;
		CUInt2 mSize;
		DevilXTUnorderedSet(CWindowEventListener*) mEventListeners;
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
		CInt2 getCursorPosition()const;
		Void registerEventListener(CWindowEventListener * listener)
		{
			mEventListeners.insert(listener);
		}
		Void unregisterEventListener(CWindowEventListener * listener)
		{
			mEventListeners.erase(listener);
		}
	};
}