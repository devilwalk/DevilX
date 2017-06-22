#pragma once
#include "GLES3VertexBufferImp.h"
#include "GLES3IndexBufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CGeometry
				:public TInterfaceObject<IGeometryImp>
				,public TBaseObject<CGeometry>
			{
			protected:
				CVertexBufferImp * mVertexBuffer;
				CIndexBufferImp * mIndexBuffer;
			public:
				CGeometry(IGeometryImp * interfaceImp);
				~CGeometry();
				decltype(mVertexBuffer) const & getVertexBuffer()const
				{
					return mVertexBuffer;
				}
				CIndexBufferImp * getIndexBuffer()const
				{
					return mIndexBuffer;
				}

				// Inherited via TInterfaceObject
				virtual Void onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}