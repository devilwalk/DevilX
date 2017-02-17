#pragma once
#include "Entity.h"
#include "BaseObject.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		namespace NSBullet
		{
			class CScene
				:public TBaseObject<CScene>
				,public TInterfaceObject<ISceneImp>
				,public TInternalObject<btCollisionWorld>
			{
			protected:
				TResourcePtrMap<IEntityImp*,CEntity> mEntitys;
				TResourcePtrMap<IQueryImp*,CQuery> mQuerys;
			public:
				CScene(ISceneImp * interfaceImp);
				~CScene();
				Void update();
				// Inherited via TMessageReceiver
				virtual void onMessage(ISceneImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}