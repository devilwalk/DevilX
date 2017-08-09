#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IComboBoxImp;
		class IComboBoxItemImp
			:public IComboBoxItem
			,public TBaseObject<IComboBoxItemImp>
			,public TMessageReceiver<CComboBoxItem>
		{
		protected:
			CComboBoxItem * const mItem;
			IComboBoxImp * const mComboBox;
		public:
			IComboBoxItemImp(CComboBoxItem * item,IComboBoxImp * comboBox);
			~IComboBoxItemImp();
			CComboBoxItem * getItem()const
			{
				return mItem;
			}
			// ͨ�� IComboBoxItem �̳�
			virtual Void setText(const CUTF8String & text) override;
			virtual const CUTF8String & getText() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;

			// ͨ�� TMessageReceiver �̳�
			virtual Void onMessage(CComboBoxItem * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
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

			// ͨ�� IComboBox �̳�
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