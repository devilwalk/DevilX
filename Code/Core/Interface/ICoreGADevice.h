#pragma once
#include "ICoreGAStruct.h"
#include "ICoreGAResource.h"
#include "ICoreGAView.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGADevice
		{
		protected:
			virtual ~IGADevice(){ }
		public:
			virtual IGAVertexBuffer * createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGAIndexBuffer * createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGAConstantBuffer * createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGAUnorderedAccessBuffer * createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture1D * createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture2D * createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture3D * createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture2D * createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGAShaderResourceView * createShaderResourceView(IGAResource * resource,const IGAStruct::SShaderResourceViewDesc * desc=nullptr)=0;
			virtual IGAInputLayout * createInputLayout(const IGAStruct::SInputLayoutDesc & desc)=0;
			virtual IGAShader * createShader(IGAEnum::EShaderType type,ConstVoidPtr code,SizeT codeSize)=0;
			virtual IGABlendState * createBlendState(const IGAStruct::SBlendDesc & blend)=0;
			virtual IGARasterizerState * createBlendState(const IGAStruct::SRasterizerDesc & blend)=0;
			virtual IGADepthStencilState * createBlendState(const IGAStruct::SDepthStencilDesc & blend)=0;
			virtual IGASamplerState * createSamplerState(const IGAStruct::SSamplerDesc & desc)=0;
		};
	}
}