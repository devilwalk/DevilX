#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDX11
		{
			class IGPUBufferImp
				:public TBaseObject<IGPUBufferImp>
				,public IGPUResource
				,public IGPUBuffer
			{
			protected:
				ID3D11Buffer * mInternal;
			public:
				IGPUBufferImp(ID3D11Device * device,const IGPUStruct::SBufferDesc & desc,const IGPUStruct::SSubResourceData * initialData=nullptr);
				~IGPUBufferImp();
			};
		}
	}
}