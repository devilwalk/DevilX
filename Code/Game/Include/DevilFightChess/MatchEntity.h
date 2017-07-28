#pragma once
#include "MatchMapGrid.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CScene;
		class CMatchEntity
			:public TBaseObject<CMatchEntity>
		{
		protected:
			CScene * const mScene;
			UInt32 mHP;
			UInt32 mMP;
			UInt32 mAttack;
			UInt32 mDefense;
			UInt32 mSpeed;
			CMatchMapGrid * mGrid;
		public:
			CMatchEntity(CScene * scene);
			~CMatchEntity();
			Void setHP(UInt32 hp);
			UInt32 getHP()const
			{
				return mHP;
			}
			Void setMP(UInt32 mp);
			UInt32 getMP()const
			{
				return mMP;
			}
			Void setAttack(UInt32 attack);
			UInt32 getAttack()const
			{
				return mAttack;
			}
			Void setDefense(UInt32 defense);
			UInt32 getDefense()const
			{
				return mDefense;
			}
			Void setSpeed(UInt32 speed);
			UInt32 getSpeed()const
			{
				return mSpeed;
			}
			Void setPosition(CMatchMapGrid * grid);
			const CMatchMapGrid * getPosition()const;
			Void attack(CMatchEntity * dst);
			Void moveTo(CMatchMapGrid * grid);
		};
	}
}