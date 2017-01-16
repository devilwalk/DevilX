#pragma once
#include "D3D11BaseObject.h"
#include "D3D11Geometry.h"
#include "D3D11Material.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CRenderableObject;
			class CRenderable
				:public TInterfaceObject<IRenderableImp>
				,public TBaseObject<CRenderable>
				,public TMessageReceiver<IGeometryUsageImp>
			{
			protected:
				CRenderableObject * const mRenderableObject;
				CGeometry * mGeometry;
				CMaterial * mMaterial;
				D3D11_PRIMITIVE_TOPOLOGY mPrimitiveTopology;
			public:
				CRenderable(IRenderableImp * interfaceImp,CRenderableObject * obj);
				~CRenderable();
				CRenderableObject * getObject()const
				{
					return mRenderableObject;
				}
				Void renderForward(CLight * light,CRenderOperation & operation);
				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(IRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

				// Inherited via TMessageReceiver
				virtual Void onMessage(IGeometryUsageImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _updatePrimitiveTopology();
			};
		}
	}
}