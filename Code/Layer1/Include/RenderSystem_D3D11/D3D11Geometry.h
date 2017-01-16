#pragma once
#include "D3D11BaseObject.h"
#include "D3D11VertexBufferImp.h"
#include "D3D11IndexBufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
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