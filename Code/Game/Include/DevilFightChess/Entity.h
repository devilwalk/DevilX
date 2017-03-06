#pragma once
#include "Grid.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CScene;
		class CEntity
			:public TBaseObject<CEntity>
		{
		protected:
			CScene * const mScene;
			UInt32 mHP;
			UInt32 mMP;
			UInt32 mAttack;
			UInt32 mDefense;
			UInt32 mSpeed;
			CGrid * mGrid;
		public:
			CEntity(CScene * scene);
			~CEntity();
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
			Void setPosition(CGrid * grid);
			const CGrid * getPosition()const;
			Void attack(CEntity * dst);
			Void moveTo(CGrid * grid);
		};
	}
}