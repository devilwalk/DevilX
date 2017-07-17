#pragma once
#include "D3D11BaseObject.h"
#include "D3D11GeometryImp.h"
#include "D3D11EntityMaterial.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
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
				CGeometryImp * mGeometry;
				CEntityMaterial * mMaterial;
				D3D11_PRIMITIVE_TOPOLOGY mPrimitiveTopology;
			public:
				CEntityRenderableImp(IEntityRenderableImp * interfaceImp,CEntityImp * obj);
				~CEntityRenderableImp();
				CEntityImp * getEntity()const
				{
					return mEntity;
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