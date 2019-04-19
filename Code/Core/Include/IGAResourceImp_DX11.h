#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			template<class TD3DResource>
			class TD3DResourceContainer
			{
			protected:
				CComPtr<TD3DResource> mInternal;
			public:
				TD3DResourceContainer(TD3DResource * obj=nullptr)
					:mInternal(obj)
				{}
				virtual ~TD3DResourceContainer()
				{}

				TD3DResource * getInternal() const
				{
					return mInternal;
				}
			};
			class IGAResourceImp
				:public IGAResource
			{
			public:
				IGAResourceImp();
				virtual ~IGAResourceImp();
			};
			template<class TInterface>
			class TGAResourceImp
				:public TInterface
				,public IGAResourceImp
			{
			public:
				TGAResourceImp()
				{ }
				virtual ~TGAResourceImp(){ }

				virtual IGAResource * queryInterface_IGAResource()override
				{
					return this;
				}
			};
			template<class TInterface,class TInternal>
			class TGAD3DResourceImp
				:public TGAResourceImp<TInterface>
				,public TD3DResourceContainer<TInternal>
			{
			public:
				TGAD3DResourceImp(TInternal * obj=nullptr)
					:TD3DResourceContainer<TInternal>(obj)
				{}
				virtual ~TGAD3DResourceImp()
				{}
			};
			namespace NSVersion11
			{
				class CGAProgram
				{
				public:
					CGAProgram();
					virtual ~CGAProgram();

					virtual Void apply(ID3D11DeviceContext * context)=0;
				};
				class IGABufferImp
					:public TGAD3DResourceImp<IGABuffer,ID3D11Buffer>
					,public IGAVertexBuffer
					,public IGAIndexBuffer
					,public IGAConstantBuffer
					,public IGAUnorderedAccessBuffer
					,public TBaseObject<IGABufferImp>
				{
				protected:
				public:
					IGABufferImp(ID3D11Device * device,const D3D11_BUFFER_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData=nullptr);
					~IGABufferImp();
					
					virtual IGABuffer * queryInterface_IGABuffer()override;
				};
				class IGATextureImp
					:public TGAResourceImp<IGATexture>
					,public IGATexture1D
					,public IGATexture2D
					,public IGATexture3D
				{
				public:
					IGATextureImp();
					virtual ~IGATextureImp();

					virtual IGATexture * queryInterface_IGATexture()override;
				};
				class IGATexture1DImp
					:public IGATextureImp
					,public TD3DResourceContainer<ID3D11Texture1D>
					,public TBaseObject<IGATexture1DImp>
				{
				protected:
				public:
					IGATexture1DImp(ID3D11Device * device,const D3D11_TEXTURE1D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData=nullptr);
					~IGATexture1DImp();
				};
				class IGATexture2DImp
					:public TD3DResourceContainer<ID3D11Texture2D>
					,public IGATextureImp
					,public TBaseObject<IGATexture2DImp>
				{
				protected:
				public:
					IGATexture2DImp(ID3D11Device * device,const D3D11_TEXTURE2D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData=nullptr);
					~IGATexture2DImp();
				};
				class IGATexture3DImp
					:public TD3DResourceContainer<ID3D11Texture3D>
					,public IGATextureImp
					,public TBaseObject<IGATexture3DImp>
				{
				protected:
				public:
					IGATexture3DImp(ID3D11Device * device,const D3D11_TEXTURE3D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData=nullptr);
					~IGATexture3DImp();
				};
				class IGAInputLayoutImp
					:public TGAD3DResourceImp<IGAInputLayout,ID3D11InputLayout>
					,public TBaseObject<IGAInputLayoutImp>
					,public CReferenceObject
				{
				protected:
					TVector(D3D11_INPUT_ELEMENT_DESC) mInputElementDescs;
				public:
					IGAInputLayoutImp(ID3D11Device * device,const TVector(D3D11_INPUT_ELEMENT_DESC) & desc);
					~IGAInputLayoutImp();

					decltype(mInputElementDescs) const & getInputelementDescs()const
					{
						return mInputElementDescs;
					}
				};
				class IGAShaderImp
					:public TGAD3DResourceImp<IGAShader,ID3DBlob>
					,public IGAVertexShader
					,public IGAGeometryShader
					,public IGAPixelShader
					,public IGAHullShader
					,public IGADomainShader
					,public IGAComputeShader
				{
				public:
					IGAShaderImp();
					virtual ~IGAShaderImp();

					virtual IGAShader * queryInterface_IGAShader()override;
				};
				class IGAVertexShaderImp
					:public TD3DResourceContainer<ID3D11VertexShader>
					,public IGAShaderImp
					,public TBaseObject<IGAVertexShaderImp>
				{
				public:
					IGAVertexShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAVertexShaderImp();

					using TD3DResourceContainer<ID3D11VertexShader>::getInternal;
				};
				class IGAGeometryShaderImp
					:public TD3DResourceContainer<ID3D11GeometryShader>
					,public IGAShaderImp
					,public TBaseObject<IGAGeometryShaderImp>
				{
				public:
					IGAGeometryShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAGeometryShaderImp();

					using TD3DResourceContainer<ID3D11GeometryShader>::getInternal;
				};
				class IGAPixelShaderImp
					:public TD3DResourceContainer<ID3D11PixelShader>
					,public IGAShaderImp
					,public TBaseObject<IGAPixelShaderImp>
				{
				public:
					IGAPixelShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAPixelShaderImp();

					using TD3DResourceContainer<ID3D11PixelShader>::getInternal;
				};
				class IGAHullShaderImp
					:public TD3DResourceContainer<ID3D11HullShader>
					,public IGAShaderImp
					,public TBaseObject<IGAHullShaderImp>
				{
				public:
					IGAHullShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAHullShaderImp();

					using TD3DResourceContainer<ID3D11HullShader>::getInternal;
				};
				class IGADomainShaderImp
					:public TD3DResourceContainer<ID3D11DomainShader>
					,public IGAShaderImp
					,public TBaseObject<IGAVertexShaderImp>
				{
				public:
					IGADomainShaderImp(ID3D11Device * device,const String & hlsl);
					~IGADomainShaderImp();

					using TD3DResourceContainer<ID3D11DomainShader>::getInternal;
				};
				class IGAComputeShaderImp
					:public TD3DResourceContainer<ID3D11ComputeShader>
					,public IGAShaderImp
					,public TBaseObject<IGAComputeShaderImp>
					,public CGAProgram
				{
				public:
					IGAComputeShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAComputeShaderImp();

					using TD3DResourceContainer<ID3D11ComputeShader>::getInternal;

					// 通过 CGAProgram 继承
					virtual Void apply(ID3D11DeviceContext * context) override;
				};
				class IGABlendStateImp
					:public TGAD3DResourceImp<IGABlendState,ID3D11BlendState>
					,public CReferenceObject
					,public TBaseObject<IGABlendStateImp>
				{
				public:
					IGABlendStateImp(ID3D11Device * device,const D3D11_BLEND_DESC1 & desc);
					~IGABlendStateImp();
				};
				class IGARasterizerStateImp
					:public TGAD3DResourceImp<IGARasterizerState,ID3D11RasterizerState>
					,public CReferenceObject
					,public TBaseObject<IGARasterizerStateImp>
				{
				public:
					IGARasterizerStateImp(ID3D11Device * device,const D3D11_RASTERIZER_DESC2 & desc);
					~IGARasterizerStateImp();
				};
				class IGADepthStencilStateImp
					:public TGAD3DResourceImp<IGADepthStencilState,ID3D11DepthStencilState>
					,public CReferenceObject
					,public TBaseObject<IGADepthStencilStateImp>
				{
				public:
					IGADepthStencilStateImp(ID3D11Device * device,const D3D11_DEPTH_STENCIL_DESC & desc);
					~IGADepthStencilStateImp();
				};
				class IGASamplerStateImp
					:public TGAD3DResourceImp<IGASamplerState,ID3D11SamplerState>
					,public CReferenceObject
					,public TBaseObject<IGASamplerStateImp>
				{
				public:
					IGASamplerStateImp(ID3D11Device * device,const D3D11_SAMPLER_DESC & desc);
					~IGASamplerStateImp();
				};
				class IGARenderPipelineProgramImp
					:public TGAResourceImp<IGAProgram>
					,public CGAProgram
					,public TBaseObject<IGARenderPipelineProgramImp>
				{
				protected:
					std::array<IGAShaderImp*,5> mShaders;
				public:
					IGARenderPipelineProgramImp(IGAVertexShaderImp * vertexShader,IGAPixelShaderImp * pixelShader,IGAGeometryShaderImp * geometryShader=nullptr,IGAHullShaderImp * hullShader=nullptr,IGADomainShaderImp * domainShader=nullptr);
					~IGARenderPipelineProgramImp();

					IGAShaderImp * const * getShaders()const
					{
						return &mShaders[0];
					}

					// 通过 CGAProgram 继承
					virtual Void apply(ID3D11DeviceContext * context) override;
				};
				class IGAProgramParameterImp
					:public TGAResourceImp<IGAProgramParameter>
					,public TBaseObject<IGAProgramParameterImp>
				{
				protected:
				public:
					IGAProgramParameterImp();
					~IGAProgramParameterImp();
				};
			}
		}
	}
}