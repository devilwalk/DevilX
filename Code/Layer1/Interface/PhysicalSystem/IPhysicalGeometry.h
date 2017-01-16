#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IGeometry
		{
		protected:
			virtual ~IGeometry(){}
		public:
			virtual const String & getName()const=0;
			virtual Void setVertexCount(UInt32 vertexCount)=0;
			virtual UInt32 getVertexCount()const=0;
			virtual Void setIndexCount(UInt32 indexCount)=0;
			virtual UInt32 getIndexCount()const=0;
			virtual Void setPositions(const CFloat3 * positions)=0;
			virtual const CFloat3 * getPositions()const=0;
			virtual Void setIndices(const UInt32 * indices)=0;
			virtual const UInt32 * getIndices()const=0;
		};
	}
}