#pragma once
#include "D3D11BaseObject.h"
#include "D3D11ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CTransformerImp
				:public TInterfaceObject<ITransformerImp>
				,public TBaseObject<CTransformerImp>
				,public CConstantBufferContainer
			{
			protected:
			public:
				CTransformerImp(ITransformerImp * interfaceImp);
				~CTransformerImp();

				// Inherited via TInterfaceObject
				virtual Void onMessage(ITransformerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			protected:
			};
		}
	}
}