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