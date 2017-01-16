#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSystemImp;
			class CIndexBufferImp
				:public TInterfaceObject<IIndexBufferImp>
				,public TBaseObject<CIndexBufferImp>
				,public TMessageReceiver<CSystemImp>
			{
			protected:
				ID3D11Buffer * mBuffer;
			public:
				CIndexBufferImp(IIndexBufferImp * interfaceImp);
				~CIndexBufferImp();
				ID3D11Buffer * getBuffer()const
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