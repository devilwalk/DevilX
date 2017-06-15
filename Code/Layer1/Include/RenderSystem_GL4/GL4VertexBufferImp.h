#pragma once
#include "GL4Enum.h"
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
				,public TMessageReceiver<CSystemImp>
				,public CMessageNotifier
			{
			public:
				enum EMessage
				{
					EMessage_BufferCreate
				};
			protected:
				GLuint mBuffers[CEnum::EVertexBufferType_Count];
			public:
				CVertexBufferImp(IVertexBufferImp * interfaceImp);
				~CVertexBufferImp();
				decltype(mBuffers) const & getBuffers()const
				{
					return mBuffers;
				}
				// Inherited via TInterfaceObject
				virtual Void onMessage(IVertexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _update();
				Bool _update(CEnum::EVertexBufferType type);
			};
		}
	}
}