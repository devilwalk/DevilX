#pragma once
#include "Control.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CPageBarItem
			:public CControl
			,public TBaseObject<CPageBarItem>
			,public CDefaultWindowEventListener
			,public CMessageNotifier
			,public NSUISystem::IEventListener
		{
		protected:
			CStaticText * mTextControl;
		public:
			CPageBarItem(const String & name,CControl * parent);
			~CPageBarItem();
			CStaticText * getTextControl()const
			{
				return mTextControl;
			}
			virtual Void setPrepareFocus(Bool focus) override;

			// ͨ�� IEventListener �̳�
			virtual Void onEvent(NSUISystem::IEvent * e) override;
		};
	}
}