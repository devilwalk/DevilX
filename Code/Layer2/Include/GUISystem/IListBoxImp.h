#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IListBoxItemImp
			:public IListBoxItem
			,public TBaseObject<IListBoxItemImp>
		{
		protected:
		public:
			IListBoxItemImp();
			~IListBoxItemImp();
		};
		class IListBoxImp
			:public IListBox
			,public TBaseObject<IListBoxImp>
		{
		protected:
			IControlImp * mControl;
		public:
			IListBoxImp(const String & name,IWindowImp * window);
			~IListBoxImp();

			// Í¨¹ý IListBox ¼Ì³Ð
			virtual IControl * queryInterface_IControl() const override;
			virtual ITextProperty * getTextProperty() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;
			virtual IListBoxItem * getItem(UInt32 rowIndex,UInt32 columeIndex) const override;
			virtual Void destroyItem(IListBoxItem * item) override;
			virtual Void setRowCount(UInt32 count) override;
			virtual UInt32 getRowCount() const override;
			virtual Void setColumeCount(UInt32 count) override;
			virtual UInt32 getColumeCount() const override;
		};
	}
}