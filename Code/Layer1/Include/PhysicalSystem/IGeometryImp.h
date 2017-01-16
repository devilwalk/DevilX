#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IGeometryImp
			:public IGeometry
			,public TBaseObject<IGeometryImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginVertexCountChange,
				EMessage_EndVertexCountChange,
				EMessage_BeginIndexCountChange,
				EMessage_EndIndexCountChange,
				EMessage_BeginPositionsChange,
				EMessage_EndPositionsChange,
				EMessage_BeginIndicesChange,
				EMessage_EndIndicesChange
			};
		protected:
			const String mName;
			UInt32 mVertexCount;
			UInt32 mIndexCount;
			const CFloat3 * mPositions;
			const UInt32 * mIndices;
		public:
			IGeometryImp(const String & name);
			~IGeometryImp();
			// Inherited via IGeometry
			virtual const String & getName() const override;
			virtual Void setVertexCount(UInt32 vertexCount)override;
			virtual UInt32 getVertexCount()const override;
			virtual Void setIndexCount(UInt32 indexCount)override;
			virtual UInt32 getIndexCount()const override;
			virtual Void setPositions(const CFloat3 * positions)override;
			virtual const CFloat3 * getPositions()const override;
			virtual Void setIndices(const UInt32 * indices)override;
			virtual const UInt32 * getIndices()const override;

		};
	}
}