#pragma once
#include "GLES3BaseObject.h"
#include "GLES3Geometry.h"
#include "GLES3EntityMaterial.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CEntityImp;
			class CLight;
			class CRenderOperation;
			class CSubEntityImp
				:public TInterfaceObject<ISubEntityImp>
				,public TBaseObject<ISubEntityImp>
				,public TMessageReceiver<IGeometryUsageImp>
			{
			protected:
				CEntityImp * const mEntity;
				CGeometry * mGeometry;
				CEntityMaterial * mMaterial;
				GLenum mPrimitiveTopology;
			public:
				CSubEntityImp(ISubEntityImp * interfaceImp,CEntityImp * obj);
				~CSubEntityImp();
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
				virtual Void onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

				// Inherited via TMessageReceiver
				virtual Void onMessage(IGeometryUsageImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _updatePrimitiveTopology();
			};
		}
	}
}