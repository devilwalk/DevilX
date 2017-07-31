#pragma once
#include "GL4BufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CSystemImp;
			class CVertexBufferImp
				:public TInterfaceObject<IVertexBufferImp>
				,public TBaseObject<CVertexBufferImp>
				,public CReferenceObject
				,public CMessageNotifier
			{
			public:
				enum EMessage
				{
					EMessage_BeginBufferChange,
					EMessage_EndBufferChange
				};
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