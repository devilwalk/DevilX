#pragma once
#include "GL4BaseObject.h"
#include "GL4Geometry.h"
#include "GL4EntityMaterial.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CEntityImp;
			class CLight;
			class CRenderOperation;
			class CEntityRenderableImp
				:public TInterfaceObject<IEntityRenderableImp>
				,public TBaseObject<CEntityRenderableImp>
				,public TMessageReceiver<IGeometryUsageImp>
			{
			protected:
				CEntityImp * const mEntity;
				CGeometry * mGeometry;
				CEntityMaterial * mMaterial;
				GLenum mPrimitiveTopology;
			public:
				CEntityRenderableImp(IEntityRenderableImp * interfaceImp,CEntityImp * obj);
				~CEntityRenderableImp();
				CEntityImp * getEntity()const
				{
					return mEntity;
				}
				CGeometry * getGeometry()const
				{
					return mGeometry;
				}
				Void renderForward(CLight * light,CRenderOperation & operation);
				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(IEntityRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

				// Inherited via TMessageReceiver
				virtual Void onMessage(IGeometryUsageImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _updatePrimitiveTopology();
			};
		}
	}
}