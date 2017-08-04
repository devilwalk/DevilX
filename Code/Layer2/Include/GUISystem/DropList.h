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
			CImageBox * mBackgroundControl;
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
			Void set(CControl * control,Bool attach=True)
			{
				if(get())
				{
					get()->setCoordParent(nullptr);
					get()->setOrderParent(nullptr);
				}
				mAttachedControl=control;
				mAttached=attach;
				if(get())
				{
					get()->setCoordParent(this);
					get()->setOrderParent(mBackgroundControl);
				}
			}
			CControl * get()const
			{
				return mAttachedControl;
			}
			virtual Void setPrepareFocus(Bool focus) override;
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
			CDropList(const String & name,CControl * coordParent,CControl * orderParent);
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
		protected:
			Float _getItemHeight()const
			{
				return 1.0f/getSize();
			}

			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(CDropListItem * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}