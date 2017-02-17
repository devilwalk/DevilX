#pragma once
#include "IMeshImp.h"
#include "IGeometryImp.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IResourceManagerImp
			:public IResourceManager
			,public TBaseObject<IResourceManagerImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginMeshCreate,
				EMessage_EndMeshCreate,
				EMessage_BeginMeshDestroy,
				EMessage_EndMeshDestroy,
				EMessage_BeginGeometryCreate,
				EMessage_EndGeometryCreate,
				EMessage_BeginGeometryDestroy,
				EMessage_EndGeometryDestroy
			};
		protected:
			TNamedResourcePtrMap<IMeshImp> mMeshes;
			TNamedResourcePtrMap<IGeometryImp> mGeometrys;
		public:
			IResourceManagerImp();
			~IResourceManagerImp();

			// Inherited via IResourceManager
			virtual IMesh * createMesh(const String & name) override;
			virtual Void destroyMesh(IMesh * mesh) override;
			virtual IMesh * getMesh(const String & name) const override;
			virtual IGeometry * createGeometry(const String & name) override;
			virtual Void destroyGeometry(IGeometry * geometry) override;
			virtual IGeometry * getGeometry(const String & name) const override;
		};
	}
}