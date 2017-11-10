#pragma once
#include "EditBox.h"
#include "List.h"
#include "Button.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISystemImp;
		class CComboBoxItem
			:public TBaseObject<CComboBoxItem>
		{
		protected:
			CUTF8String mText;
			NSResourceSystem::IResource * mBackground;
			CCommonControl * mControl;
		public:
			CComboBoxItem();
			~CComboBoxItem();
			Void setControl(CCommonControl * control);
			Void setText(const CUTF8String & text);
			const CUTF8String & getText()const
			{
				return mText;
			}
			Void setBackground(NSResourceSystem::IResource * res);
			NSResourceSystem::IResource * getBackground()const
			{
				return mBackground;
			}
		};
		class CComboBox
			:public CControl
			,public TBaseObject<CComboBox>
			,public TMessageReceiver<CEditBox>
			,public TMessageReceiver<CButton>
			,public TMessageReceiver<CList>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginItemShowControlCreate,
				EMessage_EndItemShowControlCreate,
				EMessage_BeginItemShowControlDestroy,
				EMessage_EndItemShowControlDestroy
			};
		protected:
			TResourcePtrVector<CComboBoxItem> mItems;
			TResourcePtrVector<CCommonControl> mDropListControls;
			UInt32 mItemShowStart;
			CEditBox * mEditBox;
			CList * mDropList;
			CButton * mDropIcon;
		public:
			CComboBox(const String & name,CControl * coordParent);
			~CComboBox();
			CEditBox * getEditControl()const
			{
				return mEditBox;
			}
			CList * getDropList()const
			{
				return mDropList;
			}
			Void setText(const CUTF8String & text);
			const CUTF8String & getText()const
			{
				return mEditBox->getCommonControl()->getTextControl()->getText();
			}
			Void setBackground(NSResourceSystem::IResource * resource);
			NSResourceSystem::IResource * getBackground()const
			{
				return mEditBox->getCommonControl()->getImageControl()->getBackground();
			}
			CComboBoxItem * createItem();
			CComboBoxItem * getItem(UInt32 index)const
			{
				return mItems[index];
			}
			Void destroyItem(CComboBoxItem * item);
			Void setItemListShowSize(UInt32 sizeInItems);
			UInt32 getItemListShowSize()const;
		protected:
			Void _refreshItemControl();
			Void _updateDropList();
			virtual Void _setOrderChild(CControl * control) override;
			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(CEditBox * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Void onMessage(CButton * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Void onMessage(CList * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}