#pragma once
#include "GL4VertexBufferImp.h"
#include "GL4IndexBufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CGeometry
				:public TInterfaceObject<IGeometryImp>
				,public TBaseObject<CGeometry>
				,public CReferenceObject
			{
			protected:
				CVertexBufferImp * mVertexBuffer;
				CIndexBufferImp * mIndexBuffer;
			public:
				CGeometry(IGeometryImp * interfaceImp);
				decltype(mVertexBuffer) const & getVertexBuffer()const
				{
					return mVertexBuffer;
				}
				CIndexBufferImp * getIndexBuffer()const
				{
					return mIndexBuffer;
				}
			protected:
				~CGeometry();
				// Inherited via TInterfaceObject
				virtual Void onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}