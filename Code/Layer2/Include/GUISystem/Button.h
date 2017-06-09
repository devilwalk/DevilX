#pragma once
#include "Control.h"
#include "StaticText.h"
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
			CStaticText * mTextControl;
			NSResourceSystem::IResource * mBackgroundResource;
			Bool mPressed;
		public:
			CButton(const String & name,CControl * parent);
			~CButton();
			CStaticText * getTextControl()const
			{
				return mTextControl;
			}
			Void setBackground(NSResourceSystem::IResource * resource);
			NSResourceSystem::IResource * getBackground()const;
			virtual Void setPrepareFocus(Bool focus) override;
			virtual Void onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position) override;
		};
	}
}