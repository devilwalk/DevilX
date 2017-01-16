#pragma once
#include "IPhysicalGeometry.h"
#include "IPhysicalMesh.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IResourceManager
		{
		protected:
			virtual ~IResourceManager(){}
		public:
			virtual IMesh * createMesh(const String & name)=0;
			virtual Void destroyMesh(IMesh * mesh)=0;
			virtual IMesh * getMesh(const String & name)const=0;
			virtual IGeometry * createGeometry(const String & name)=0;
			virtual Void destroyGeometry(IGeometry * geometry)=0;
			virtual IGeometry * getGeometry(const String & name)const=0;
		};
	}
}