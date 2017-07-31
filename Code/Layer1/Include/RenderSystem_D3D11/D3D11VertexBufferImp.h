#pragma once
#include "D3D11BufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CVertexBufferImp
				:public TInterfaceObject<IVertexBufferImp>
				,public TBaseObject<CVertexBufferImp>
				,public CReferenceObject
			{
			protected:
				TRefResourcePtrVector<CBufferImp> mBuffers;
			public:
				CVertexBufferImp(IVertexBufferImp * interfaceImp);
				decltype(mBuffers) const & getBuffers()const
				{
					return mBuffers;
				}
			protected:
				~CVertexBufferImp();
				// Inherited via TInterfaceObject
				virtual Void onMessage(IVertexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}