#pragma once
#include "MatchView.h"
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
			CMatchView2D * const mView;
		public:
			CMatchOperation2D(CMatchView2D * view);
			~CMatchOperation2D();

			// 通过 IMouseListener 继承
			virtual Void addFrameData(NSInputSystem::IMouse * mouse,NSInputSystem::IMouseFrameData * data) override;

			// 通过 IKeyboardListener 继承
			virtual Void addFrameData(NSInputSystem::IKeyboard * keyboard,NSInputSystem::IKeyboardFrameData * data) override;
		};
	}
}