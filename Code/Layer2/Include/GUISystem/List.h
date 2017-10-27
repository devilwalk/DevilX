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
			const UInt32 mRowIndex;
			const UInt32 mColumeIndex;
			CControl * mAttachedControl;
			Bool mAttached;
		public:
			CListItem(UInt32 rowIndex,UInt32 columeIndex,CList * list);
			~CListItem();
			UInt32 getRowIndex()const
			{
				return mRowIndex;
			}
			UInt32 getColumeIndex()const
			{
				return mColumeIndex;
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
		protected:
			TVector<TResourcePtrVector<CListItem> > mItems;
			UInt32 mSelectRow;
			UInt32 mSelectColume;
		public:
			CList(const String & name,CControl * coordParent);
			~CList();
			Void setSize(UInt32 rowSize,UInt32 columeSize);
			UInt32 getRowSize()const
			{
				return static_cast<UInt32>(mItems[0].size());
			}
			UInt32 getColumeSize()const
			{
				return static_cast<UInt32>(mItems.size());
			}
			CListItem * getItem(UInt32 row,UInt32 colume)const
			{
				return mItems[colume][row];
			}
			UInt32 getSelectRow()const
			{
				return mSelectRow;
			}
			UInt32 getSelectColume()const
			{
				return mSelectColume;
			}
			virtual Void setVisible(Bool visible) override;
		protected:
			CFloat2 _getItemSize()const
			{
				return 1.0f/CFloat2(static_cast<Float>(getColumeSize()),static_cast<Float>(getRowSize()));
			}
			virtual Void _setOrderChild(CControl * control) override;
			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(CListItem * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}