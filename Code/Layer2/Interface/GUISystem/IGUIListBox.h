#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IListBoxItem
		{
		protected:
			virtual ~IListBoxItem(){}
		public:
			virtual Void setText(const CUTF8String & text)=0;
			virtual const CUTF8String & getText()const=0;
		};
		class IListBox
		{
		protected:
			virtual ~IListBox(){}
		public:
			virtual IControl * queryInterface_IControl()const=0;
			virtual ITextProperty * getTextProperty()const=0;
			virtual Void setBackground(NSResourceSystem::IResource * resource)=0;
			virtual NSResourceSystem::IResource * getBackground()const=0;
			virtual IListBoxItem * createItem()=0;
			virtual IListBoxItem * getItem(UInt32 index)const=0;
			virtual Void destroyItem(IListBoxItem * item)=0;
			virtual Void setRowCount(UInt32 count)=0;
			virtual UInt32 getRowCount()const=0;
			virtual Void setColumeCount(UInt32 count)=0;
			virtual UInt32 getColumeCount()const=0;
		};
	}
}