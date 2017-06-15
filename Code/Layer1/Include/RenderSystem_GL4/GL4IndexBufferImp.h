#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CSystemImp;
			class CIndexBufferImp
				:public TInterfaceObject<IIndexBufferImp>
				,public TBaseObject<CIndexBufferImp>
				,public TMessageReceiver<CSystemImp>
				,public CMessageNotifier
			{
			public:
				enum EMessage
				{
					EMessage_BufferCreate
				};
			protected:
				GLuint mBuffer;
			public:
				CIndexBufferImp(IIndexBufferImp * interfaceImp);
				~CIndexBufferImp();
				decltype(mBuffer) getBuffer()const
				{
					return mBuffer;
				}
				// Inherited via TInterfaceObject
				virtual Void onMessage(IIndexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _update();
			};
		}
	}
}