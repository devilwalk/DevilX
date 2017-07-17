#pragma once
#include "D3D11GeometryImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CQueryObjectRenderable
				:public TBaseObject<CQueryObjectRenderable>
			{
			protected:
				CTransformerImp * mTransformer;
				CGeometryImp * mGeometry;
				IGeometryUsageImp * mGeometryUsage;
			public:
				CQueryObjectRenderable();
				~CQueryObjectRenderable();
				CTransformerImp * getTransformer()const
				{
					return mTransformer;
				}
				CGeometryImp * getGeometry()const
				{
					return mGeometry;
				}
				IGeometryUsageImp * getGeometryUsage()const
				{
					return mGeometryUsage;
				}
				Boolean merge(IQueryObjectImp * obj);
			};
		}
	}
}