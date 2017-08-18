#pragma once
#include "CommonControl.h"
#include "Caret.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISystemImp;
		class CEditBox
			:public CControl
			,public TBaseObject<CEditBox>
			,public CDefaultWindowEventListener
			,public CMessageNotifier
			,public TMessageReceiver<ISystemImp>
		{
		public:
			enum EMessage
			{
				EMessage_BeginTextChange,
				EMessage_EndTextChange
			};
		protected:
			CCommonControl * mCommonControl;
			CCaret * mCaret;
			UInt32 mCaretPosition;
			Bool mPrepareFocus;
		public:
			CEditBox(const String & name,CControl * coordParent);
			~CEditBox();
			CCommonControl * getCommonControl()const
			{
				return mCommonControl;
			}
			Void setText(const CUTF8String & text);
			virtual Void setPrepareFocus(Bool focus) override;
			virtual Void setFocus(Bool focus) override;
			virtual Void onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position) override;
			virtual Void onCharEvent(CWindow * window,const CUTF16Char & ch) override;

			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		protected:
			Void _setText(const CUTF8String & text);
			Void _updateListener(Bool preValue);
			virtual Void _setOrderChild(CControl * control) override;
		};
	}
}