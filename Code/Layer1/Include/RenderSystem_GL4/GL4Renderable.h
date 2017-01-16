#pragma once
#include "GL4Geometry.h"
#include "GL4Material.h"
#include "GL4RenderOperation.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
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
				GLenum mPrimitiveTopology;
			public:
				CRenderable(IRenderableImp * interfaceImp,CRenderableObject * obj);
				~CRenderable();
				CRenderableObject * getObject()const
				{
					return mRenderableObject;
				}
				CGeometry * getGeometry()const
				{
					return mGeometry;
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