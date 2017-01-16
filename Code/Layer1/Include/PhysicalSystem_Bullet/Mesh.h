#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		namespace NSBullet
		{
			class CSystem;
			class CMesh
				:public TInterfaceObject<IMeshImp>
				,public TInternalObject<btTriangleIndexVertexArray>
				,public TBaseObject<CMesh>
				,public TMessageReceiver<ISubMeshImp>
				,public TMessageReceiver<CSystem>
				,public CMessageNotifier
			{
			public:
				enum EMessage
				{
					EMessage_BeginRebuild,
					EMessage_EndRebuild
				};
				struct SMessageReceiver_IGeometryImp
					:public TMessageReceiver<IGeometryImp>
					,public TBaseObject<SMessageReceiver_IGeometryImp>
				{
					CMesh * mMesh;
					SMessageReceiver_IGeometryImp(CMesh * mesh):mMesh(mesh)
					{}
					virtual Void onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				};
				friend struct SMessageReceiver_IGeometryImp;
			protected:
				SMessageReceiver_IGeometryImp mMessageReceiver_IGeometryImp;
				Bool mNeedRebuild;
			public:
				CMesh(IMeshImp * interfaceImp);
				virtual ~CMesh();
				// Inherited via TMessageReceiver
				virtual void onMessage(IMeshImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual void onMessage(ISubMeshImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual void onMessage(CSystem * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _needRebuild();
				Void _rebuild();
			};
		}
	}
}