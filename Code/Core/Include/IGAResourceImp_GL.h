#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			template<class TClass,class TInterface,typename TInternal=GLuint>
			class TGAResourceImp
				:public TBaseObject<TClass>
				,public TInterface
				,public IGAResource
			{
			protected:
				TInternal mInternal;
			public:
				TGAResourceImp(TInternal obj=0)
					:mInternal(obj)
				{
				}
				virtual ~TGAResourceImp()
				{
					assert(mInternal==0);
				}

				virtual IGAResource * queryInterface_IGAResource()override
				{
					return this;
				}

				TInternal getInternal() const
				{
					return mInternal;
				}
			};
			class IGABufferImp
				:public TGAResourceImp<IGABufferImp,IGABuffer>
				,public IGAVertexBuffer
				,public IGAIndexBuffer
				,public IGAConstantBuffer
				,public IGAUnorderedAccessBuffer
			{
			public:
				IGABufferImp(UInt32 sizeInByte,IGAEnum::EUsage usage,UInt32 cpuAccessFlags,const IGAStruct::SSubResourceData * initialData=nullptr);
				~IGABufferImp();

				virtual IGABuffer * queryInterface_IGABuffer()override;
			};
			class IGATextureImp
				:public TGAResourceImp<IGATextureImp,IGATexture>
				,public IGATexture1D
				,public IGATexture2D
				,public IGATexture3D
			{
			protected:
			public:
				IGATextureImp(UInt32 width,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr);
				IGATextureImp(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,Bool cubemap=False,const IGAStruct::SSubResourceData * initialData=nullptr);
				IGATextureImp(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,const IGAStruct::SSubResourceData * initialData=nullptr);
				~IGATextureImp();

				virtual IGATexture * queryInterface_IGATexture()override;

			protected:
				Void _initialize1D(UInt32 width,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr);
				Void _initialize2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,Bool cubemap=False,const IGAStruct::SSubResourceData * initialData=nullptr);
				Void _initialize3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,const IGAStruct::SSubResourceData * initialData=nullptr);
			};
			class IGAInputLayoutImp
				:public TGAResourceImp<IGAInputLayoutImp,IGAInputLayout>
			{
			public:
				IGAInputLayoutImp(const IGAStruct::SInputLayoutDesc & desc);
				~IGAInputLayoutImp();
			};
			class IGAShaderImp
				:public TGAResourceImp<IGAShaderImp,IGAShader>
			{
			public:
				IGAShaderImp(const String & glsl,IGAEnum::EShaderType type);
				~IGAShaderImp();
			};
			class IGASamplerStateImp
				:public TGAResourceImp<IGASamplerStateImp,IGASamplerState>
			{
			public:
				IGASamplerStateImp(const IGAStruct::SSamplerDesc & desc);
				~IGASamplerStateImp();
			};
		}
	}
}