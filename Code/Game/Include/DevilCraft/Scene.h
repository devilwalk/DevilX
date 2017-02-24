#pragma once
#include "Entity.h"
namespace NSDevilX
{
	namespace NSDevilCraft
	{
		class CScene
			:public TBaseObject<CScene>
		{
		protected:
			NSRenderSystem::IScene * mRenderScene;
			NSPhysicalSystem::IScene * mPhysicalScene;
			TNamedResourcePtrMap<CEntity> mEntities;
		public:
			CScene(const String & name);
			virtual ~CScene();
			NSRenderSystem::IScene * getRenderScene()const
			{
				return mRenderScene;
			}
			NSPhysicalSystem::IScene * getPhysicalScene()const
			{
				return mPhysicalScene;
			}
			Void addEntity(CEntity * entity);
			CEntity * getEntity(const String & name)const;
			Void removeEntity(CEntity * entity);
			Void preUpdate();
			Void update();
		};
	}
}