#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CUIManager
			:public TBaseObject<CUIManager>
		{
		protected:
			NSUISystem::IGraphicScene * mGraphicScene;
		public:
			CUIManager();
			~CUIManager();
			NSUISystem::IGraphicScene * getGraphicScene()const
			{
				return mGraphicScene;
			}
		};
	}
}