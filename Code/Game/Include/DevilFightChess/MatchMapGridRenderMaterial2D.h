#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchMapGridRenderMaterial2D
			:public TBaseObject<CMatchMapGridRenderMaterial2D>
		{
		protected:
			NSRenderSystem::ITexture * mTexture;
			CFloatRGBA mColour;
		public:
			CMatchMapGridRenderMaterial2D();
			~CMatchMapGridRenderMaterial2D();
			Void setTexture(const String & filename);
			NSRenderSystem::ITexture * getTexture()const
			{
				return mTexture;
			}
			Void setColour(const CColour & colour);
			const CColour & getColour()const
			{
				return mColour;
			}
		};
	}
}