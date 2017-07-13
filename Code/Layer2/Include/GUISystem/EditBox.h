#pragma once
#include "StaticText.h"
#include "Caret.h"
#include "GraphicWindowTextureUtility.h"
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
				EMessage_SetFocus,
				EMessage_BeginTextChange,
				EMessage_EndTextChange
			};
		protected:
			CStaticText * mTextControl;
			CCaret * mCaret;
			CGraphicWindowTextureUtility * mBackground;
			UInt32 mCaretPosition;
			Bool mPrepareFocus;
		public:
			CEditBox(const String & name,CControl * parent);
			~CEditBox();
			CStaticText * getTextControl()const
			{
				return mTextControl;
			}
			Void setBackground(NSResourceSystem::IResource * resource);
			NSResourceSystem::IResource * getBackground()const;
			virtual Void setPrepareFocus(Bool focus) override;
			virtual Void setFocus(Bool focus) override;
			virtual Void onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position) override;
			virtual Void onCharEvent(CWindow * window,const CUTF16Char & ch) override;

			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		protected:
			Void _updateListener(Bool preValue);
		};
	}
}