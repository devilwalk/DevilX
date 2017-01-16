#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IMeshImp;
		class ISubMeshImp
			:public ISubMesh
			,public TBaseObject<ISubMeshImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction,
				EMessage_BeginVertexStartChange,
				EMessage_EndVertexStartChange,
				EMessage_BeginIndexStartChange,
				EMessage_EndIndexStartChange,
				EMessage_BeginIndexCountChange,
				EMessage_EndIndexCountChange
			};
		protected:
			const String mName;
			IMeshImp * const mMesh;
			UInt32 mVertexStart;
			UInt32 mIndexStart;
			UInt32 mIndexCount;
		public:
			ISubMeshImp(const String & name,IMeshImp * mesh);
			~ISubMeshImp();
			// Inherited via ISubMesh
			virtual IMesh * getMesh() const override;
			virtual const String & getName() const override;
			virtual Void setVertexStart(UInt32 vertexStart) override;
			virtual UInt32 getVertexStart() const override;
			virtual Void setIndexStart(UInt32 indexStart) override;
			virtual UInt32 getIndexStart() const override;
			virtual Void setIndexCount(UInt32 indexCount) override;
			virtual UInt32 getIndexCount() const override;
		};
	}
}