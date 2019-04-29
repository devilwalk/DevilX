#pragma once
#include "GAObject.h"
#include "IGAResourceImp.h"
#include "IGAViewImp_GL.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			template<class TInterface,class TInternal=GLuint>
			class TGAGLResourceImp
				:public TGAResourceImp<TInterface>
				,public TGLObjectContainer<TInternal>
			{
			public:
				TGAGLResourceImp(TInternal obj=0)
					:TGLObjectContainer<TInternal>(obj)
				{
				}
				virtual ~TGAGLResourceImp()
				{
				}
			};
			class IGABufferImp
				:public TGAGLResourceImp<IGABuffer>
				,public IGAVertexBuffer
				,public IGAIndexBuffer
				,public IGAConstantBuffer
				,public IGAUnorderedAccessBuffer
				,public TBaseObject<IGABufferImp>
			{
			public:
				IGABufferImp(GLenum target,GLuint sizeInByte,GLbitfield flags,ConstVoidPtr initialData);
				~IGABufferImp();

				virtual IGABuffer * queryInterface_IGABuffer()override;
			};
			class IGATextureImp
				:public TGAGLResourceImp<IGATexture>
				,public IGATexture1D
				,public IGATexture2D
				,public IGATexture3D
				,public TGAViewImp<IGAShaderResourceView>
				,public TGAViewImp<IGARenderTargetView>
				,public TGAViewImp<IGADepthStencilView>
				,public TBaseObject<IGATextureImp>
				,public TGAViewImp<IGATextureView>
			{
			protected:
			public:
				IGATextureImp(GLsizei width,GLenum internalFormat,GLint mipLevel,UInt32 arrayCount,const IGAStruct::SSubResourceData* initialData);
				IGATextureImp(GLsizei width,GLsizei height,GLenum internalFormat,GLint mipLevel,UInt32 arrayCount,Bool cubemap,const IGAStruct::SSubResourceData * initialData);
				IGATextureImp(GLsizei width,GLsizei height,GLsizei depth,GLenum internalFormat,GLint mipLevel,const IGAStruct::SSubResourceData* initialData);
				~IGATextureImp();

				virtual IGATexture * queryInterface_IGATexture()override;

			protected:
				Void _initialize1D(GLsizei width,GLenum internalFormat,GLint mipLevel,UInt32 arrayCount,const IGAStruct::SSubResourceData* initialData);
				Void _initialize2D(GLsizei width,GLsizei height,GLenum internalFormat,GLint mipLevel,UInt32 arrayCount,Bool cubemap,const IGAStruct::SSubResourceData* initialData);
				Void _initialize3D(GLsizei width,GLsizei height,GLsizei depth,GLenum internalFormat,GLint mipLevel,const IGAStruct::SSubResourceData* initialData);
			};
			class IGAInputLayoutImp
				:public TGAGLResourceImp<IGAInputLayout>
				,public TBaseObject<IGAInputLayoutImp>
			{
			protected:
				TVector(IGAStruct::SInputElementDesc) mInputElementDescs;
			public:
				IGAInputLayoutImp(const TVector(IGAStruct::SInputElementDesc)& inputElementDescs);
				~IGAInputLayoutImp();

				const decltype(mInputElementDescs)& getInputElementDescs()const
				{
					return mInputElementDescs;
				}
			};
			class IGAProgramParameterImp;
			class IGAProgramReflectionImp;
			class IGAProgramImp
				:public TGAResourceImp<IGAProgram>
			{
			public:
				IGAProgramImp();
				virtual ~IGAProgramImp();

				virtual Void apply()=0;
				virtual IGAProgramReflectionImp* createReflection()=0;
			};
			class IGAShaderImp
				:public TGAGLResourceImp<IGAShader>
				,public TBaseObject<IGAShaderImp>
				,public IGAVertexShader
				,public IGAPixelShader
				,public IGAGeometryShader
				,public IGAHullShader
				,public IGADomainShader
				,public IGAComputeShader
				,public IGAProgramImp
			{
			public:
				IGAShaderImp(const String & glsl,IGAEnum::EShaderType type);
				~IGAShaderImp();

				virtual IGAShader* queryInterface_IGAShader() override;
				virtual Void apply() override;
				virtual IGAProgramReflectionImp* createReflection() override;
			};
			class CGAProgramImp
				:public IGAProgramImp
				,public TGLObjectContainer<>
				,public TBaseObject<IGAProgramImp>
			{
			public:
				CGAProgramImp(GLuint vertexShader,GLuint pixelShader,GLuint geometryShader,GLuint hullShader,GLuint domainShader);
				~CGAProgramImp();

				virtual Void apply() override;
				virtual IGAProgramReflectionImp* createReflection() override;
			};
			class CGAProgramPipelineImp
				:public IGAProgramImp
				,public TBaseObject<CGAProgramPipelineImp>
			{
			protected:
				static GLuint msProgramPipeline;
				static UInt32 msRefCount;
				std::array<GLuint,5> mPrograms;
			public:
				CGAProgramPipelineImp(GLuint vertexShader,GLuint pixelShader,GLuint geometryShader,GLuint hullShader,GLuint domainShader);
				~CGAProgramPipelineImp();

				virtual Void apply() override;
				virtual IGAProgramReflectionImp* createReflection() override;
			protected:
				Void _createInternal();
			};
			class IGABlendStateImp
				:public TGAResourceImp<IGABlendState>
				,public TBaseObject<IGABlendStateImp>
				,public CReferenceObject
			{
			protected:
				IGAStruct::SBlendDesc mDescription;
			public:
				IGABlendStateImp(const IGAStruct::SBlendDesc& desc);
				~IGABlendStateImp();

				const decltype(mDescription)& getDesc()const
				{
					return mDescription;
				}
			};
			class IGARasterizerStateImp
				:public TGAResourceImp<IGARasterizerState>
				,public TBaseObject<IGARasterizerStateImp>
				,public CReferenceObject
			{
			protected:
				IGAStruct::SRasterizerDesc mDescription;
			public:
				IGARasterizerStateImp(const IGAStruct::SRasterizerDesc& desc);
				~IGARasterizerStateImp();

				const decltype(mDescription)& getDesc()const
				{
					return mDescription;
				}
			};
			class IGADepthStencilStateImp
				:public TGAResourceImp<IGADepthStencilState>
				,public TBaseObject<IGADepthStencilStateImp>
				,public CReferenceObject
			{
			protected:
				IGAStruct::SDepthStencilDesc mDescription;
			public:
				IGADepthStencilStateImp(const IGAStruct::SDepthStencilDesc& desc);
				~IGADepthStencilStateImp();

				const decltype(mDescription)& getDesc()const
				{
					return mDescription;
				}
			};
			class IGASamplerStateImp
				:public TGAGLResourceImp<IGASamplerState>
				,public TBaseObject<IGASamplerStateImp>
				,public CReferenceObject
			{
			protected:
				IGAStruct::SSamplerDesc mDescription;
			public:
				IGASamplerStateImp(const IGAStruct::SSamplerDesc & desc);
				~IGASamplerStateImp();

				const decltype(mDescription)& getDesc()const
				{
					return mDescription;
				}
			};
			class IGAProgramParameterImp
				:public TGAResourceImp<IGAProgramParameter>
				,public TBaseObject<IGAProgramParameterImp>
			{
			protected:
				std::array<TVector(GLuint),5> mConstantBuffers;
				std::array<TVector(GLuint),5> mSamplers;
			public:
				IGAProgramParameterImp();
				~IGAProgramParameterImp();

				const decltype(mConstantBuffers)& getConstantBuffers()const
				{
					return mConstantBuffers;
				}
				const decltype(mSamplers)& getSamplers()const
				{
					return mSamplers;
				}

				Void apply();
				Void apply(IGAEnum::EShaderType type);

				// Í¨¹ý TGAResourceImp ¼Ì³Ð
				virtual Void setConstantBuffer(UInt32 slot,IGAConstantBuffer* buffer) override;
				virtual Void setSampler(UInt32 slot,IGASamplerState* sampler) override;
				virtual Void setResourceView(UInt32 slot,IGATextureView* view) override;
				virtual Void setResourceView(UInt32 slot,IGATextureBufferView* view) override;
				virtual Void setResourceView(UInt32 slot,IGAUnorderedAccessView* view) override;
			};
		}
	}
}