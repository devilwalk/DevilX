#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchScene;
		class CMatchView2D
			:public TBaseObject<CMatchView2D>
		{
		public:
			enum EMoveType
			{
				EMoveType_Left,
				EMoveType_Right,
				EMoveType_Up,
				EMoveType_Down
			};
		protected:
			CMatchScene * const mScene;
			NSRenderSystem::IViewport * mRenderViewport2D;
			NSRenderSystem::ICamera * mRenderCamera2D;
			NSRenderSystem::IQuery * mRenderQuery2D;
		public:
			CMatchView2D(CMatchScene * scene);
			~CMatchView2D();

			Void move(EMoveType type)const;
			CUInt2 getSizeInPixel()const;
		};
	}
}