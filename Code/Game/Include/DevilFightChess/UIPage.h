#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CUIPage
			:public TBaseObject<CUIPage>
			,public NSGUISystem::IButtonEventCallback
			,public NSGUISystem::IEditBoxEventCallback
		{
		public:
			enum EType
			{
				EType_Unknown,
				EType_Login,
				EType_Register,
				EType_BigWorld,
				EType_MatchServerConfig,
				EType_Count
			};
			typedef Void buttonLogic(NSGUISystem::IButton*,NSGUISystem::IButtonEventCallback::EEvent);
			typedef Void editBoxLogic(NSGUISystem::IEditBox*,NSGUISystem::IEditBoxEventCallback::EEvent);
		protected:
			EType const mType;
			EType mCallPage;
			NSGUISystem::IWindow * mGUIWindow;
			buttonLogic * mButtonLogic;
			editBoxLogic * mEditBoxLogic;
		public:
			CUIPage(EType type);
			virtual ~CUIPage();
			EType getType()const
			{
				return mType;
			}
			NSGUISystem::IWindow * getGUIWindow()const
			{
				return mGUIWindow;
			}
			Void setButtonLogic(buttonLogic * logic);
			Void setEditBoxLogic(editBoxLogic * logic);
			Void setCallPage(EType type);
			EType getCallPage()const
			{
				return mCallPage;
			}
			// 通过 IButtonEventCallback 继承
			virtual Void onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent e) override;

			// 通过 IEditBoxEventCallback 继承
			virtual Void onEvent(NSGUISystem::IEditBox * control,NSGUISystem::IEditBoxEventCallback::EEvent e) override;
		};
	}
}