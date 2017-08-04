#pragma once
#include "EditBox.h"
#include "DropList.h"
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
			,public TMessageReceiver<CButton>
			,public TMessageReceiver<CDropList>
		{
		protected:
			TResourcePtrVector<CComboBoxItem> mItems;
			UInt32 mItemShowStart;
			CEditBox * mEditBox;
			CDropList * mDropList;
			CButton * mDropIcon;
		public:
			CComboBox(const String & name,CControl * coordParent,CControl * orderParent);
			~CComboBox();
			CEditBox * getEditControl()const
			{
				return mEditBox;
			}
			CDropList * getDropList()const
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

			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(CButton * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Void onMessage(CDropList * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}