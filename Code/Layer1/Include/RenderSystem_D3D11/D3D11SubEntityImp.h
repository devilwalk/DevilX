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
			class CSystemImp;
			class CSubEntityImp
				:public TInterfaceObject<ISubEntityImp>
				,public TBaseObject<CSubEntityImp>
				,public TMessageReceiver<IGeometryUsageImp>
				,public TMessageReceiver<CSystemImp>
			{
			protected:
				CEntityImp * const mEntity;
				CGeometryImp * mGeometry;
				CEntityMaterial * mMaterial;
				D3D11_PRIMITIVE_TOPOLOGY mPrimitiveTopology;
				CBufferUpdater * mQueryDataBuffer;
			public:
				CSubEntityImp(ISubEntityImp * interfaceImp,CEntityImp * obj);
				~CSubEntityImp();
				CEntityImp * getEntity()const;
				Void renderForward(CLight * light,CRenderOperation & operation);
				Void query(CRenderOperation & operation);
				// 通过 TInterfaceObject 继承
				virtual Void onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

				// Inherited via TMessageReceiver
				virtual Void onMessage(IGeometryUsageImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _updatePrimitiveTopology();

				// 通过 TMessageReceiver 继承
				virtual Void onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}