#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IEntity;
		class ISubEntity
		{
		protected:
			virtual ~ISubEntity(){}
		public:
			virtual IEntity * getEntity()const=0;
			virtual ISubMesh * getSubMesh()const=0;
			virtual Void setQueryMask(UInt32 mask)=0;
			virtual UInt32 getQueryMask()const=0;
		};
	}
}