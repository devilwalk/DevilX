#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CBigWorld;
		class CBigWorldPage
			:public TBaseObject<CBigWorldPage>
			,public NSGUISystem::IButtonEventCallback
			,public NSGUISystem::IEditBoxEventCallback
		{
		protected:
			CBigWorld * const mBigWorld;
			NSGUISystem::IWindow * mGUIWindow;
		public:
			CBigWorldPage(CBigWorld * bigWorld);
			~CBigWorldPage();

			// ͨ�� IButtonEventCallback �̳�
			virtual Void onEvent(NSGUISystem::IButton * control,NSGUISystem::IButtonEventCallback::EEvent events) override;

			// ͨ�� IEditBoxEventCallback �̳�
			virtual Void onEvent(NSGUISystem::IEditBox * control,NSGUISystem::IEditBoxEventCallback::EEvent events) override;
		};
		class CBigWorld
			:public TBaseObject<CBigWorld>
			,public CModule
		{
		protected:
			CBigWorldPage * mPage;
			TSharedReadData<Int32> mReturnCode;
		public:
			CBigWorld();
			~CBigWorld();

			// ͨ�� CModule �̳�
			virtual Void start() override;
			virtual Void update() override;
			virtual Void stop() override;
		};
	}
}