#pragma once
#include "GLES3BaseObject.h"
#include "GLES3ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
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