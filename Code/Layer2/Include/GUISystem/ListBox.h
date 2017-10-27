#pragma once
#include "List.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CListBoxItem
			:public TBaseObject<CListBoxItem>
		{
		protected:
			CUTF8String mText;
			NSResourceSystem::IResource * mBackground;
			CCommonControl * mControl;
		public:
			CListBoxItem();
			~CListBoxItem();
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
		class CListBox
			:public CControl
			,public TBaseObject<CListBox>
		{
		protected:
			CList * mList;
		public:
			CListBox(const String & name,CControl * coordParent);
			~CListBox();
			Void setSize(UInt32 rowSize,UInt32 columeSize)
			{
				mList->setSize(rowSize,columeSize);
			}
			UInt32 getRowCount()const
			{
				return mList->getRowSize();
			}
			UInt32 getColumeCount()const
			{
				return mList->getColumeSize();
			}
		};
	}
}