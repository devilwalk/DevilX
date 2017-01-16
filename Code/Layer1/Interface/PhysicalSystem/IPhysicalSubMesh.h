#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IMesh;
		class ISubMesh
		{
		protected:
			virtual ~ISubMesh(){}
		public:
			virtual IMesh * getMesh()const=0;
			virtual const String & getName()const=0;
			virtual Void setVertexStart(UInt32 vertexStart)=0;
			virtual UInt32 getVertexStart()const=0;
			virtual Void setIndexStart(UInt32 indexStart)=0;
			virtual UInt32 getIndexStart()const=0;
			virtual Void setIndexCount(UInt32 indexCount)=0;
			virtual UInt32 getIndexCount()const=0;
		};

	}
}