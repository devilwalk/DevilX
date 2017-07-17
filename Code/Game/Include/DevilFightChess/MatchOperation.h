#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchOperation
			:public TBaseObject<CMatchOperation>
			,public NSInputSystem::IMouseListener
			,public NSInputSystem::IKeyboardListener
		{
		protected:
		public:
			CMatchOperation();
			~CMatchOperation();
		};
	}
}