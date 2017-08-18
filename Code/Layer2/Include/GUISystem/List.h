#pragma once
#include "CommonControl.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CList;
		class CListItem
			:public CControl
			,public TBaseObject<CListItem>
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
			CListItem(UInt32 index,CList * list);
			~CListItem();
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
		class CList
			:public CControl
			,public TBaseObject<CList>
			,public CMessageNotifier
			,public TMessageReceiver<CListItem>
		{
		public:
			enum EMessage
			{
				EMessage_SelectIndexChange
			};
			enum EType
			{
				EType_Row,
				EType_Colume
			};
		protected:
			const EType mType;
			TResourcePtrVector<CListItem> mItems;
			UInt32 mSelectIndex;
		public:
			CList(const String & name,CControl * coordParent,EType type=EType_Colume);
			~CList();
			Void setSize(UInt32 size);
			UInt32 getSize()const
			{
				return static_cast<UInt32>(mItems.size());
			}
			CListItem * getItem(UInt32 index)const
			{
				return mItems[index];;
			}
			UInt32 getSelectIndex()const
			{
				return mSelectIndex;
			}
			virtual Void setVisible(Bool visible) override;
		protected:
			Float _getItemSize()const
			{
				return 1.0f/getSize();
			}
			virtual Void _setOrderChild(CControl * control) override;
			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(CListItem * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}