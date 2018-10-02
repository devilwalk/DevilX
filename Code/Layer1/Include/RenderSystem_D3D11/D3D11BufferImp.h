#pragma once
#include "D3D11BufferUpdater.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSystemImp;
			class CBufferImp
				:public CBuffer
				,public TCOMInternalObject<ID3D11Buffer>
				,public TBaseObject<CBuffer>
				,public CReferenceObject
			{
			protected:
			public:
				CBufferImp();
				~CBufferImp();

				virtual Void initialize(IEnum::EBufferType type,UInt32 sizeInBytes,UInt32 flag=IEnum::EBufferFlag_GPURead,ConstVoidPtr data=nullptr) override;
				virtual Void updateData(ConstVoidPtr data,UInt32 offsetInBytes=0,UInt32 sizeInBytes=0) override;
				virtual Void bind(UInt32 offsetInBytes,IEnum::EAutoPropgramParameterDataSource source) override;
				virtual Void unbind(UInt32 offsetInBytes) override;
			};
		}
	}
}