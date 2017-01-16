#pragma once
#include "IPhysicalMesh.h"
#include "IPhysicalTransformer.h"
#include "IPhysicalSubEntitiy.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IEntity
		{
		protected:
			virtual ~IEntity(){}
		public:
			virtual const String & getName()const=0;
			virtual Void setMesh(IMesh * mesh)=0;
			virtual IMesh * getMesh()const=0;
			virtual Void setTransformer(ITransformer * transformer)=0;
			virtual ITransformer * getTransformer()const=0;
			virtual ISubEntity * getSubEntity(ISubMesh * subMesh)const=0;
		};
	}
}