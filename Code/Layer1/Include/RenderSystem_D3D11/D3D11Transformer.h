#pragma once
#include "D3D11BaseObject.h"
#include "D3D11ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CTransformer
				:public TInterfaceObject<ITransformerImp>
				,public TBaseObject<CTransformer>
				,public CConstantBufferContainer
			{
			protected:
			public:
				CTransformer(ITransformerImp * interfaceImp);
				~CTransformer();

				// Inherited via TInterfaceObject
				virtual Void onMessage(ITransformerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			protected:
			};
		}
	}
}