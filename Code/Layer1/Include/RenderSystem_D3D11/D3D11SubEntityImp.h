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
			class CSubEntityImp
				:public TInterfaceObject<ISubEntityImp>
				,public TBaseObject<CSubEntityImp>
				,public TMessageReceiver<IGeometryUsageImp>
			{
			protected:
				CEntityImp * const mEntity;
				CGeometryImp * mGeometry;
				CEntityMaterial * mMaterial;
				D3D11_PRIMITIVE_TOPOLOGY mPrimitiveTopology;
				CBufferImp * mQueryBuffer;
			public:
				CSubEntityImp(ISubEntityImp * interfaceImp,CEntityImp * obj);
				~CSubEntityImp();
				CEntityImp * getEntity()const;
				Void renderForward(CLight * light,CRenderOperation & operation);
				Void query(CRenderOperation & operation);
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