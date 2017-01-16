#pragma once
#include "IPhysicalEnum.h"
#include "IPhysicalGeometry.h"
#include "IPhysicalSubMesh.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IMesh
		{
		protected:
			virtual ~IMesh()
			{}
		public:
			virtual const String & getName()const=0;
			virtual Void setGeometry(IGeometry * geometry)=0;
			virtual IGeometry * getGeometry()const=0;
			virtual ISubMesh * createSubMesh(const String & name)=0;
			virtual Void destroySubMesh(ISubMesh * subMesh)=0;
			virtual ISubMesh * getSubMesh(const String & name)const=0;
			virtual UInt32 getSubMeshCount()const=0;
			virtual ISubMesh * getSubMesh(UInt32 index)const=0;
		};
	}
}