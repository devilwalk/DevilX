#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		namespace NSBullet
		{
			class CQuery
				:public TInterfaceObject<IQueryImp>
			{
			protected:
				CScene * const mScene;
			public:
				CQuery(IQueryImp * interfaceImp,CScene * scene);
				virtual ~CQuery();

				// Inherited via TInterfaceObject
				virtual Void onMessage(IQueryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				virtual Void _execute(){}
			};
			class CRayQuery
				:public CQuery
				,public TBaseObject<CRayQuery>
				,public btCollisionWorld::RayResultCallback
			{
			public:
				CRayQuery(IQueryImp * interfaceImp,CScene * scene);
				~CRayQuery();
				virtual	btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult,bool normalInWorldSpace) override;
			protected:
				virtual Void _execute() override;
			};
		}
	}
}