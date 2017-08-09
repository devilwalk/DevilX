#pragma once
#include "Control.h"
#include "CommonControl.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CButton
			:public CControl
			,public TBaseObject<CButton>
			,public CDefaultWindowEventListener
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_Press,
				EMessage_Release,
				EMessage_Click
			};
		protected:
			CCommonControl * mCommonControl;
			CImageBox * mAlphaControl;
			Bool mPressed;
		public:
			CButton(const String & name,CControl * coordParent);
			~CButton();
			CCommonControl * getCommonControl()const
			{
				return mCommonControl;
			}
			virtual Void setPrepareFocus(Bool focus) override;
		protected:
			virtual Void _setOrderChild(CControl * control) override;
			virtual Void onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position) override;
		};
	}
}