#pragma once
#include "PageBarItem.h"
#include "TextProperty.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CPageBar
			:public CControl
			,public TBaseObject<CPageBar>
			,public CMessageNotifier
			,public TMessageReceiver<CTextProperty>
		{
		protected:
			CTextProperty * mTextProperty;
			TResourcePtrList<CPageBarItem> mItems;
			UInt32 mNextItemName;
			CPageBarItem * mFocus;
		public:
			CPageBar(const String & name,CControl * parent);
			~CPageBar();
			CTextProperty * getTextProperty()const{ return mTextProperty; }
			Void setFocus(CPageBarItem * item);
			Void addItem(const CUTF8String & text);
			const CUTF8String & getItem(UInt32 index)const;
			Void removeItem(UInt32 index);
		protected:
			Void _updateItems();

			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(CTextProperty * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}