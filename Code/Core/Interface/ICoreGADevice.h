#pragma once
#include "ICoreGAStruct.h"
#include "ICoreGAResource.h"
#include "ICoreGAView.h"
#include "ICoreGADeviceContext.h"
#include "ICoreGAShaderReflection.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGADevice
		{
		protected:
			virtual ~IGADevice(){ }
		public:
			virtual IGADeviceContext * getImmediateContext()const=0;
			virtual IGADeviceContext * createDeferredContext()=0;
			virtual IGAVertexBuffer * createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr)=0;
			virtual IGAIndexBuffer * createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr)=0;
			virtual IGAConstantBuffer * createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr)=0;
			virtual IGAUnorderedAccessBuffer * createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr)=0;
			virtual IGATexture1D * createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture2D * createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture3D * createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture2D * createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGAShaderResourceView * createShaderResourceView(IGAResource * resource,const IGAStruct::SShaderResourceViewDesc * desc=nullptr)=0;
			virtual IGAInputLayout * createInputLayout(const TVector<IGAStruct::SInputElementDesc> & inputElements)=0;
			virtual IGAVertexShader * createVertexShader(const std::string & code)=0;
			virtual IGAPixelShader * createPixelShader(const std::string & code)=0;
			virtual IGAGeometryShader * createGeometryShader(const std::string & code)=0;
			virtual IGAHullShader * createHullShader(const std::string & code)=0;
			virtual IGADomainShader * createDomainShader(const std::string & code)=0;
			virtual IGAComputeShader * createComputeShader(const std::string & code)=0;
			virtual IGABlendState * createBlendState(const IGAStruct::SBlendDesc & desc)=0;
			virtual IGARasterizerState * createRasterizerState(const IGAStruct::SRasterizerDesc & desc)=0;
			virtual IGADepthStencilState * createDepthStencilState(const IGAStruct::SDepthStencilDesc & desc)=0;
			virtual IGASamplerState * createSamplerState(const IGAStruct::SSamplerDesc & desc)=0;
			virtual IGAProgram * createProgram(IGAVertexShader * vertexShader,IGAPixelShader * pixelShader,IGAGeometryShader * geometryShader=nullptr,IGAHullShader * hullShader=nullptr,IGADomainShader * domainShader=nullptr)=0;
			virtual IGAProgram * createProgram(IGAComputeShader * computeShader)=0;
			virtual IGAShaderReflection * createShaderReflection(IGAProgram * program)=0;
			virtual Void destroyShaderReflection(IGAShaderReflection * reflection)=0;
			virtual IGAProgramParameter * createProgramParameter()=0;
			virtual Void destroyProgramParameter(IGAProgramParameter * parameter)=0;
		};
	}
}