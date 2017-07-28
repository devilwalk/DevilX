#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchOperation2D
			:public TBaseObject<CMatchOperation2D>
			,public NSInputSystem::IMouseListener
			,public NSInputSystem::IKeyboardListener
		{
		protected:
			NSInputSystem::IMouse * mMouse;
			NSInputSystem::IKeyboard * mKeyboard;
		public:
			CMatchOperation2D();
			~CMatchOperation2D();

			// ͨ�� IMouseListener �̳�
			virtual Void addFrameData(NSInputSystem::IMouse * mouse,NSInputSystem::IMouseFrameData * data) override;

			// ͨ�� IKeyboardListener �̳�
			virtual Void addFrameData(NSInputSystem::IKeyboard * keyboard,NSInputSystem::IKeyboardFrameData * data) override;
		};
	}
}