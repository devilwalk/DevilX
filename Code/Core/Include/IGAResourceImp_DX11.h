#pragma once
#include "IGAResourceImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			template<class TInterface,class TInternal>
			class TGAD3DResourceImp
				:public TGAResourceImp<TInterface>
				,public TD3DObjectContainer<TInternal>
			{
			public:
				TGAD3DResourceImp(TInternal * obj=nullptr)
					:TD3DObjectContainer<TInternal>(obj)
				{}
				virtual ~TGAD3DResourceImp()
				{}
			};
			namespace NSVersion11
			{
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
					,public TD3DObjectContainer<ID3D11Texture1D>
					,public TBaseObject<IGATexture1DImp>
				{
				protected:
				public:
					IGATexture1DImp(ID3D11Device * device,const D3D11_TEXTURE1D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData=nullptr);
					~IGATexture1DImp();
				};
				class IGATexture2DImp
					:public TD3DObjectContainer<ID3D11Texture2D>
					,public IGATextureImp
					,public TBaseObject<IGATexture2DImp>
				{
				protected:
				public:
					IGATexture2DImp(ID3D11Device * device,const D3D11_TEXTURE2D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData=nullptr);
					~IGATexture2DImp();
				};
				class IGATexture3DImp
					:public TD3DObjectContainer<ID3D11Texture3D>
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

					decltype(mInputElementDescs) const & getInputElementDescs()const
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
					:public TD3DObjectContainer<ID3D11VertexShader>
					,public IGAShaderImp
					,public TBaseObject<IGAVertexShaderImp>
				{
				public:
					IGAVertexShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAVertexShaderImp();

					using TD3DObjectContainer<ID3D11VertexShader>::getInternal;
				};
				class IGAGeometryShaderImp
					:public TD3DObjectContainer<ID3D11GeometryShader>
					,public IGAShaderImp
					,public TBaseObject<IGAGeometryShaderImp>
				{
				public:
					IGAGeometryShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAGeometryShaderImp();

					using TD3DObjectContainer<ID3D11GeometryShader>::getInternal;
				};
				class IGAPixelShaderImp
					:public TD3DObjectContainer<ID3D11PixelShader>
					,public IGAShaderImp
					,public TBaseObject<IGAPixelShaderImp>
				{
				public:
					IGAPixelShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAPixelShaderImp();

					using TD3DObjectContainer<ID3D11PixelShader>::getInternal;
				};
				class IGAHullShaderImp
					:public TD3DObjectContainer<ID3D11HullShader>
					,public IGAShaderImp
					,public TBaseObject<IGAHullShaderImp>
				{
				public:
					IGAHullShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAHullShaderImp();

					using TD3DObjectContainer<ID3D11HullShader>::getInternal;
				};
				class IGADomainShaderImp
					:public TD3DObjectContainer<ID3D11DomainShader>
					,public IGAShaderImp
					,public TBaseObject<IGAVertexShaderImp>
				{
				public:
					IGADomainShaderImp(ID3D11Device * device,const String & hlsl);
					~IGADomainShaderImp();

					using TD3DObjectContainer<ID3D11DomainShader>::getInternal;
				};
				class IGAProgramParameterImp;
				class IGAProgramReflectionImp;
				class IGAProgramImp
					:public TGAResourceImp<IGAProgram>
				{
				public:
					IGAProgramImp();
					virtual ~IGAProgramImp();

					virtual Void apply(ID3D11DeviceContext * context,IGAProgramParameterImp * parameter)=0;
					virtual IGAProgramReflectionImp* createReflection()=0;
				};
				class IGAComputeShaderImp
					:public TD3DObjectContainer<ID3D11ComputeShader>
					,public IGAShaderImp
					,public TBaseObject<IGAComputeShaderImp>
					,public IGAProgramImp
				{
				public:
					IGAComputeShaderImp(ID3D11Device * device,const String & hlsl);
					~IGAComputeShaderImp();

					using TD3DObjectContainer<ID3D11ComputeShader>::getInternal;

					// 通过 CGAProgram 继承
					virtual Void apply(ID3D11DeviceContext * context,IGAProgramParameterImp * parameter) override;
					virtual IGAProgramReflectionImp* createReflection() override;
				};
				class IGABlendStateImp
					:public TGAD3DResourceImp<IGABlendState,ID3D11BlendState>
					,public CReferenceObject
					,public TBaseObject<IGABlendStateImp>
				{
				public:
					IGABlendStateImp(ID3D11Device * device,const D3D11_BLEND_DESC & desc);
					IGABlendStateImp(ID3D11Device1 * device,const D3D11_BLEND_DESC1 & desc);
					~IGABlendStateImp();
				};
				class IGARasterizerStateImp
					:public TGAD3DResourceImp<IGARasterizerState,ID3D11RasterizerState>
					,public CReferenceObject
					,public TBaseObject<IGARasterizerStateImp>
				{
				public:
					IGARasterizerStateImp(ID3D11Device * device,const D3D11_RASTERIZER_DESC & desc);
					IGARasterizerStateImp(ID3D11Device1 * device,const D3D11_RASTERIZER_DESC1 & desc);
					IGARasterizerStateImp(ID3D11Device3 * device,const D3D11_RASTERIZER_DESC2 & desc);
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
					:public IGAProgramImp
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
					virtual Void apply(ID3D11DeviceContext * context,IGAProgramParameterImp * parameter) override;
					virtual IGAProgramReflectionImp* createReflection() override;
				};
				class IGAProgramParameterImp
					:public TGAResourceImp<IGAProgramParameter>
					,public TBaseObject<IGAProgramParameterImp>
				{
				protected:
					std::array<TVector(IGABufferImp*),5> mConstantBuffers;
					std::array<TVector(IGASamplerStateImp*),5> mSamplers;
				public:
					IGAProgramParameterImp();
					~IGAProgramParameterImp();

					const decltype(mConstantBuffers) & getConstantBuffers()const
					{
						return mConstantBuffers;
					}
					const decltype(mSamplers) & getSamplers()const
					{
						return mSamplers;
					}

					// 通过 TGAResourceImp 继承
					virtual Void setConstantBuffer(UInt32 slot,IGAConstantBuffer * buffer) override;
					virtual Void setSampler(UInt32 slot,IGASamplerState * sampler) override;
					virtual Void setResourceView(UInt32 slot,IGAShaderResourceView * view) override;
				};
			}
		}
	}
}