#pragma once
#include "CommonControl.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CDropList;
		class CDropListItem
			:public CControl
			,public TBaseObject<CDropListItem>
			,public CDefaultWindowEventListener
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_Select
			};
		protected:
			CImageBox * mAlphaControl;
			const UInt32 mIndex;
			CControl * mAttachedControl;
			Bool mAttached;
		public:
			CDropListItem(UInt32 index,CDropList * dropList);
			~CDropListItem();
			UInt32 getIndex()const
			{
				return mIndex;
			}
			Void set(CControl * control,Bool attach=True);
			CControl * get()const
			{
				return mAttachedControl;
			}
			virtual Void setVisible(Bool visible) override;
			virtual Void setPrepareFocus(Bool focus) override;
		protected:
			virtual Void _setOrderChild(CControl * control) override;
			virtual Void onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position) override;
		};
		class CDropList
			:public CControl
			,public TBaseObject<CDropList>
			,public CMessageNotifier
			,public TMessageReceiver<CDropListItem>
		{
		public:
			enum EMessage
			{
				EMessage_SelectIndexChange
			};
		protected:
			TResourcePtrVector<CDropListItem> mItems;
			UInt32 mSelectIndex;
		public:
			CDropList(const String & name,CControl * coordParent);
			~CDropList();
			Void setSize(UInt32 size);
			UInt32 getSize()const
			{
				return static_cast<UInt32>(mItems.size());
			}
			CDropListItem * getItem(UInt32 index)const
			{
				return mItems[index];;
			}
			UInt32 getSelectIndex()const
			{
				return mSelectIndex;
			}
			virtual Void setVisible(Bool visible) override;
		protected:
			Float _getItemHeight()const
			{
				return 1.0f/getSize();
			}
			virtual Void _setOrderChild(CControl * control) override;
			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(CDropListItem * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}