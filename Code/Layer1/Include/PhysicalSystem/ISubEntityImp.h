#pragma once
#include "ISubMeshImp.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IEntityImp;
		class ISubEntityImp
			:public ISubEntity
			,public TBaseObject<ISubEntityImp>
		{
		protected:
			ISubMeshImp * const mSubMesh;
			IEntityImp * const mEntity;
			UInt32 mQueryMask;
		public:
			ISubEntityImp(ISubMeshImp * subMesh,IEntityImp * entity);
			~ISubEntityImp();

			// Inherited via ISubEntity
			virtual IEntity * getEntity() const override;
			virtual ISubMesh * getSubMesh() const override;
			virtual Void setQueryMask(UInt32 mask) override;
			virtual UInt32 getQueryMask() const override;
		};
	}
}