#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			template<class TClass,class TInterface,class TInternal>
			class TGAResourceImp
				:public TBaseObject<TClass>
				,public TInterface
				,public IGAResource
			{
			protected:
				CComPtr<TInternal> mInternal;
			public:
				TGAResourceImp(TInternal * obj=nullptr)
					:mInternal(obj)
				{ }
				virtual ~TGAResourceImp(){ }

				virtual IGAResource * queryInterface_IGAResource()override
				{
					return this;
				}

				TInternal * getInternal() const
				{
					return mInternal;
				}
			};
			namespace NSVersion11
			{
				class IGABufferImp
					:public TGAResourceImp<IGABufferImp,IGABuffer,ID3D11Buffer>
					,public IGAVertexBuffer
					,public IGAIndexBuffer
					,public IGAConstantBuffer
					,public IGAUnorderedAccessBuffer
				{
				protected:
				public:
					IGABufferImp(ID3D11Device * device,const D3D11_BUFFER_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData=nullptr);
					~IGABufferImp();
					
					virtual IGABuffer * queryInterface_IGABuffer()override;
				};
				class IGATexture1DImp
					:public TGAResourceImp<IGATexture1DImp,IGATexture,ID3D11Texture1D>
					,public IGATexture1D
				{
				protected:
				public:
					IGATexture1DImp(ID3D11Device * device,const D3D11_TEXTURE1D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData=nullptr);
					~IGATexture1DImp();

					virtual IGATexture * queryInterface_IGATexture()override;
				};
				class IGATexture2DImp
					:public TGAResourceImp<IGATexture2DImp,IGATexture,ID3D11Texture2D>
					,public IGATexture2D
				{
				protected:
				public:
					IGATexture2DImp(ID3D11Device * device,const D3D11_TEXTURE2D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData=nullptr);
					~IGATexture2DImp();

					virtual IGATexture * queryInterface_IGATexture()override;
				};
				class IGATexture3DImp
					:public TGAResourceImp<IGATexture3DImp,IGATexture,ID3D11Texture3D>
					,public IGATexture3D
				{
				protected:
				public:
					IGATexture3DImp(ID3D11Device * device,const D3D11_TEXTURE3D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData=nullptr);
					~IGATexture3DImp();

					virtual IGATexture * queryInterface_IGATexture()override;
				};
				class IGAInputLayoutImp
					:public TGAResourceImp<IGAInputLayoutImp,IGAInputLayout,ID3D11InputLayout>
				{
				public:
					IGAInputLayoutImp(ID3D11Device * device,const TVector<D3D11_INPUT_ELEMENT_DESC> & desc);
					~IGAInputLayoutImp();
				};
				class IGAVertexShaderImp
					:public TGAResourceImp<IGAVertexShaderImp,IGAShader,ID3D11VertexShader>
				{
				public:
					IGAVertexShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAVertexShaderImp();
				};
				class IGAGeometryShaderImp
					:public TGAResourceImp<IGAGeometryShaderImp,IGAShader,ID3D11GeometryShader>
				{
				public:
					IGAGeometryShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAGeometryShaderImp();
				};
				class IGAPixelShaderImp
					:public TGAResourceImp<IGAPixelShaderImp,IGAShader,ID3D11PixelShader>
				{
				public:
					IGAPixelShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAPixelShaderImp();
				};
				class IGAHullShaderImp
					:public TGAResourceImp<IGAHullShaderImp,IGAShader,ID3D11HullShader>
				{
				public:
					IGAHullShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAHullShaderImp();
				};
				class IGADomainShaderImp
					:public TGAResourceImp<IGADomainShaderImp,IGAShader,ID3D11DomainShader>
				{
				public:
					IGADomainShaderImp(ID3D11Device * device,const String & hlsl);
					~IGADomainShaderImp();
				};
				class IGABlendStateImp
					:public TGAResourceImp<IGABlendStateImp,IGABlendState,ID3D11BlendState>
				{
				public:
					IGABlendStateImp(ID3D11Device * device,const D3D11_BLEND_DESC & desc);
					~IGABlendStateImp();
				};
				class IGARasterizerStateImp
					:public TGAResourceImp<IGARasterizerStateImp,IGARasterizerState,ID3D11RasterizerState>
				{
				public:
					IGARasterizerStateImp(ID3D11Device * device,const D3D11_RASTERIZER_DESC & desc);
					~IGARasterizerStateImp();
				};
				class IGADepthStencilStateImp
					:public TGAResourceImp<IGADepthStencilStateImp,IGADepthStencilState,ID3D11DepthStencilState>
				{
				public:
					IGADepthStencilStateImp(ID3D11Device * device,const D3D11_DEPTH_STENCIL_DESC & desc);
					~IGADepthStencilStateImp();
				};
				class IGASamplerStateImp
					:public TGAResourceImp<IGASamplerStateImp,IGASamplerState,ID3D11SamplerState>
				{
				public:
					IGASamplerStateImp(ID3D11Device * device,const D3D11_SAMPLER_DESC & desc);
					~IGASamplerStateImp();
				};
			}
		}
	}
}