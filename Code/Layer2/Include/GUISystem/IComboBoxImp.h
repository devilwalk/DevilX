#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IComboBoxItemImp
			:public IComboBoxItem
			,public TBaseObject<IComboBoxItemImp>
		{
		protected:
			CComboBoxItem * const mItem;
		public:
			IComboBoxItemImp(CComboBoxItem * item);
			~IComboBoxItemImp();
			CComboBoxItem * getItem()const
			{
				return mItem;
			}
			// 通过 IComboBoxItem 继承
			virtual Void setText(const CUTF8String & text) override;
			virtual const CUTF8String & getText() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;
		};
		class IComboBoxImp
			:public IComboBox
			,public TBaseObject<IComboBoxImp>
		{
		protected:
			TResourcePtrVector<IComboBoxItemImp> mItems;
			IControlImp * mControl;
			ITextPropertyImp * mTextProperty;
			ITextPropertyImp * mItemTextProperty;
			IComboBoxEventCallback * mEventCallback;
		public:
			IComboBoxImp(const String & name,IWindowImp * window);
			~IComboBoxImp();

			// 通过 IComboBox 继承
			virtual IControl * queryInterface_IControl() const override;
			virtual ITextProperty * getTextProperty() const override;
			virtual Void setText(const CUTF8String & text) override;
			virtual const CUTF8String & getText() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;
			virtual IComboBoxItem * createItem() override;
			virtual IComboBoxItem * getItem(UInt32 index) const override;
			virtual Void destroyItem(IComboBoxItem * item) override;
			virtual Void setItemListShowSize(UInt32 sizeInItems) override;
			virtual UInt32 getItemListShowSize() const override;
			virtual ITextProperty * getItemTextProperty() const override;
			virtual Void setEventCallback(IComboBoxEventCallback * callback) override;
			virtual IComboBoxEventCallback * getEventCallback() const override;
		};
	}
}