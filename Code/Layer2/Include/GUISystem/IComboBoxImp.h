#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IComboBoxImp
			:public IComboBox
			,public TBaseObject<IComboBoxImp>
			,public NSUISystem::IEventListener
			,public TMessageReceiver<CComboBox>
		{
		protected:
			IControlImp * mControl;
			ITextPropertyImp * mTextProperty;
			IComboBoxEventCallback * mEventCallback;
		public:
			IComboBoxImp(const String & name,IWindowImp * window);
			~IComboBoxImp();
		};
	}
}