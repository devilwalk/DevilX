#pragma once
#include "ISubMeshImp.h"
#include "IGeometryImp.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IMeshImp
			:public IMesh
			,public TBaseObject<IMeshImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction,
				EMessage_BeginGeometryChange,
				EMessage_EndGeometryChange,
				EMessage_BeginSubMeshCreate,
				EMessage_EndSubMeshCreate,
				EMessage_BeginSubMeshDestroy,
				EMessage_EndSubMeshDestroy
			};
		protected:
			const String mName;
			IGeometryImp * mGeometry;
			TNamedIndexResourcePtrContainer(ISubMeshImp) mSubMeshes;
		public:
			IMeshImp(const String & name);
			~IMeshImp();

			// Inherited via IMesh
			virtual const String & getName() const override;
			virtual Void setGeometry(IGeometry * geometry) override;
			virtual IGeometry * getGeometry() const override;
			virtual ISubMesh * createSubMesh(const String & name) override;
			virtual Void destroySubMesh(ISubMesh * subMesh) override;
			virtual ISubMesh * getSubMesh(const String & name) const override;
			virtual UInt32 getSubMeshCount() const override;
			virtual ISubMesh * getSubMesh(UInt32 index) const override;
		};
	}
}