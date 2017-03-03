#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CBuff
		{
		public:
			CBuff();
			virtual ~CBuff();
		};
		class CTerrainBuff
			:public CBuff
			,public TBaseObject<CTerrainBuff>
		{
		protected:
		public:
			CTerrainBuff();
			~CTerrainBuff();
		};
	}
}