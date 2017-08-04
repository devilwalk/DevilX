#pragma once
#include "IGUIControl.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IComboBox;
		class IComboBoxEventCallback
		{
		public:
			enum EEvent
			{
				EEvent_TextChange
			};
		protected:
			virtual ~IComboBoxEventCallback()
			{}
		public:
			virtual Void onEvent(IComboBox * control,EEvent events)=0;
		};
		class IComboBoxItem
		{
		protected:
			virtual ~IComboBoxItem(){}
		public:
			virtual Void setText(const CUTF8String & text)=0;
			virtual const CUTF8String & getText()const=0;
			virtual Void setBackground(NSResourceSystem::IResource * resource)=0;
			virtual NSResourceSystem::IResource * getBackground()const=0;
		};
		class IComboBox
		{
		protected:
			virtual ~IComboBox(){}
		public:
			virtual IControl * queryInterface_IControl()const=0;
			virtual ITextProperty * getTextProperty()const=0;
			virtual Void setText(const CUTF8String & text)=0;
			virtual const CUTF8String & getText()const=0;
			virtual Void setBackground(NSResourceSystem::IResource * resource)=0;
			virtual NSResourceSystem::IResource * getBackground()const=0;
			virtual IComboBoxItem * createItem()=0;
			virtual IComboBoxItem * getItem(UInt32 index)const=0;
			virtual Void destroyItem(IComboBoxItem * item)=0;
			virtual Void setItemListShowSize(UInt32 sizeInItems)=0;
			virtual UInt32 getItemListShowSize()const=0;
			virtual ITextProperty * getItemTextProperty()const=0;
			virtual Void setEventCallback(IComboBoxEventCallback * callback)=0;
			virtual IComboBoxEventCallback * getEventCallback()const=0;
		};
	}
}