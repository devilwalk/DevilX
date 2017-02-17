#pragma once
#include "IMeshImp.h"
#include "ITransformerImp.h"
#include "ISubEntityImp.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class ISceneImp;
		class IEntityImp
			:public IEntity
			,public TBaseObject<IEntityImp>
			,public CMessageNotifier
			,public TMessageReceiver<IMeshImp>
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction,
				EMessage_BeginMeshChange,
				EMessage_EndMeshChange,
				EMessage_BeginTransformerChange,
				EMessage_EndTransformerChange
			};
		protected:
			const String mName;
			ISceneImp * const mScene;
			IMeshImp * mMesh;
			ITransformerImp * mTransformer;
			Bool mOutsideTransformer;
			TResourcePtrMap<ISubMeshImp*,ISubEntityImp> mSubEntitys;
		public:
			IEntityImp(const String & name,ISceneImp * scene);
			~IEntityImp();

			// Inherited via IEntity
			virtual const String & getName() const override;
			virtual Void setMesh(IMesh * mesh) override;
			virtual IMesh * getMesh() const override;
			virtual Void setTransformer(ITransformer * transformer) override;
			virtual ITransformer * getTransformer() const override;
			virtual ISubEntity * getSubEntity(ISubMesh * subMesh) const override;
		protected:
			Void _rebuildSubEntitys();

			// Inherited via TMessageReceiver
			virtual Void onMessage(IMeshImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}