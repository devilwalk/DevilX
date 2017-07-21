#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchScene;
		class CMatchView
			:public TBaseObject<CMatchView>
		{
		protected:
			CMatchScene * const mScene;
			NSRenderSystem::IViewport * mRenderViewport2D;
			NSRenderSystem::ICamera * mRenderCamera2D;
			NSRenderSystem::IQuery * mRenderQuery2D;
		public:
			CMatchView(CMatchScene * scene);
			~CMatchView();
		};
	}
}