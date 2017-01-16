#pragma once
#include "BaseObject.h"
#include "Mesh.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		namespace NSBullet
		{
			class CScene;
			class CEntity
				:public TBaseObject<CEntity>
				,public TInterfaceObject<IEntityImp>
				,public TInternalObject<btCollisionObject>
				,public TMessageReceiver<CMesh>
			{
			public:
				struct SMessageReceiver_ITransformerImp
					:public TMessageReceiver<ITransformerImp>
				{
					CEntity * mEntity;
					SMessageReceiver_ITransformerImp(CEntity * entity):mEntity(entity){}

					// Inherited via TMessageReceiver
					virtual void onMessage(ITransformerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				};
				friend struct SMessageReceiver_ITransformerImp;
			protected:
				SMessageReceiver_ITransformerImp mMessageReceiver_ITransformerImp;
				CScene * const mScene;
				Bool mNeedUpdateTransform;
				Bool mNeedRebuild;
			public:
				CEntity(IEntityImp * interfaceImp,CScene * scene);
				~CEntity();
				Void update();
				// Inherited via TMessageReceiver
				virtual void onMessage(IEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual void onMessage(CMesh * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _needRebuild();
				Void _needUpdateTransform();
				Void _rebuild();
				Void _updateTransform();
			};
		}
	}
}