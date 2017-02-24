#pragma once
#include "Actor.h"
#include "Entity.h"
namespace NSDevilX
{
	namespace NSDevilCraft
	{
		class CScene;
		class CPlayer;
		class CEntityPlayer
			:public CEntity
			,public TBaseObject<CEntityPlayer>
		{
		protected:
			CPlayer * const mPlayer;
		public:
			CEntityPlayer(CPlayer * player);
			virtual ~CEntityPlayer();
		};
		class CPlayer
			:public TBaseObject<CPlayer>
		{
		public:
			struct SActor
				:public CActor
				,public TBaseObject<SActor>
			{
			private:
				CPlayer * const mPlayer;
				Bool mIsJump;
			public:
				enum EType
				{
					EType_MoveForward=1,
					EType_MoveBackward=-1,
					EType_MoveLeft=2,
					EType_MoveRight=-2,
					EType_Jump=3
				};
				SActor(CPlayer * player);
				virtual Void addAction(UInt32 action) override;
			};
		protected:
			CScene * const mScene;
			CEntityPlayer * mEntity;
			SActor * mActor;
			NSRenderSystem::ICamera * mRenderCamera;
		public:
			CPlayer(const String & name,CScene * scene);
			virtual ~CPlayer();
			CScene * getScene()const
			{
				return mScene;
			}
			Void addAction(SActor::EType action);
			Void setJump(Bool jump);
			Boolean isJump()const;
			Void update();
		};
	}
}