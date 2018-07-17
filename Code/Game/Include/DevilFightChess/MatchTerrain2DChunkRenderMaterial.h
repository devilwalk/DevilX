#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchTerrain2DChunkRenderMaterial
			:public TBaseObject<CMatchTerrain2DChunkRenderMaterial>
		{
		protected:
			NSRenderSystem::ITexture * mTexture;
			CFloatRGBA mColour;
		public:
			CMatchTerrain2DChunkRenderMaterial();
			~CMatchTerrain2DChunkRenderMaterial();
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