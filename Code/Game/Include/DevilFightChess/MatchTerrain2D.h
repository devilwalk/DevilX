#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchMap;
		class CMatchTerrain2D
			:public TBaseObject<CMatchTerrain2D>
		{
		protected:
			CMatchMap * const mMap;
			NSRenderSystem::IGeometry * mGeometry;
			NSRenderSystem::IEntity * mRenderEntity;
			NSRenderSystem::IVisibleArea * mRenderVisibleArea;
		public:
			CMatchTerrain2D(CMatchMap * map);
			~CMatchTerrain2D();
			CMatchMap * getMap()const
			{
				return mMap;
			}
		};
	}
}