#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSystemImp;
			class CVertexBufferImp
				:public TInterfaceObject<IVertexBufferImp>
				,public TBaseObject<CVertexBufferImp>
				,public TMessageReceiver<CSystemImp>
			{
			protected:
				ID3D11Buffer * mBuffers[CEnum::EVertexBufferType_Count];
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