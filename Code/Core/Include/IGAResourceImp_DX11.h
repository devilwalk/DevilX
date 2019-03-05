#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDX11
		{
			class IGABufferImp
				:public TBaseObject<IGABufferImp>
				,public IGAResource
				,public IGABuffer
			{
			protected:
				ID3D11Buffer * mInternal;
			public:
				IGABufferImp(ID3D11Device * device,const IGAStruct::SBufferDesc & desc,const IGAStruct::SSubResourceData * initialData=nullptr);
				~IGABufferImp();
			};
			class IGATexture1DImp
				:public IGAResource
				,public IGATexture
				,public IGATexture1D
			{
			protected:
				ID3D11Texture1D * mInternal;
			public:
				IGATexture1DImp(ID3D11Device * device,const IGAStruct::STexture1DDesc & desc,const IGAStruct::SSubResourceData * initialData=nullptr);
				~IGATexture1DImp();
			};
		}
	}
}