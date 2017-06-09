#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMessageBox
			:public TBaseObject<CMessageBox>
			,public NSGUISystem::IButtonEventCallback
		{
		protected:
			NSGUISystem::IWindow * mGUIWindow;
		public:
			CMessageBox(const CUTF8String & message);
			~CMessageBox();

			// Í¨¹ý IButtonEventCallback ¼Ì³Ð
			virtual Void onEvent(NSGUISystem::IButton * control,EEvent events) override;
		};
	}
}