#pragma once
#include "ICoreGAStruct.h"
#include "ICoreGAHighLevelResource.h"
#include "ICoreGAView.h"
#include "ICoreGADeviceContext.h"
#include "ICoreGAProgramReflection.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGAHighLevelDeviceFeature_SeparateVAO
		{
		protected:
			virtual ~IGAHighLevelDeviceFeature_SeparateVAO()
			{
			}
		public:
			virtual IGAInputLayout* createInputLayout(const TVector<IGAStruct::SInputElementDesc>& inputElements)=0;
		};
		class IGAHighLevelDeviceFeature_ComputeShader
		{
		protected:
			virtual ~IGAHighLevelDeviceFeature_ComputeShader()
			{
			}
		public:
			virtual IGAUnorderedAccessBuffer* createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr)=0;
			virtual IGAUnorderedAccessView* createUnorderedAccessView(IGATexture1D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0,UInt32 arrayCount=1)=0;
			virtual IGAUnorderedAccessView* createUnorderedAccessView(IGATexture2D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0,UInt32 arrayCount=1)=0;
			virtual IGAUnorderedAccessView* createUnorderedAccessView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice,UInt32 depthCount)=0;
			virtual IGAComputeShader* createComputeShader(const std::string& code)=0;
			virtual IGAComputeShaderParameter* createComputeShaderParameter()=0;
		};
		class IGAHighLevelDeviceFeature_SeparateProgram
		{
		protected:
			virtual ~IGAHighLevelDeviceFeature_SeparateProgram()
			{
			}
		public:
			virtual IGAShaderParameter* createShaderParameter()=0;
			virtual Void destroyShaderParameter(IGAShaderParameter* parameter)=0;
			virtual IGAShaderReflection* createReflection(IGAShader* shader)=0;
			virtual Void destroyReflection(IGAShaderReflection* reflection)=0;
		};
		class IGAHighLevelDevice
		{
		protected:
			virtual ~IGAHighLevelDevice(){ }
		public:
			virtual IGADevice* queryInterface_IGADevice()const=0;
			virtual IGAHighLevelDeviceFeature_SeparateVAO* queryFeature_SeparateVAO()const=0;
			virtual IGAHighLevelDeviceFeature_ComputeShader* queryFeature_ComputeShader()const=0;
			virtual IGAHighLevelDeviceFeature_SeparateProgram* queryFeature_SeparateProgram()const=0;
			virtual IGAEnum::EHighLevelDeviceVersion getVersion()const=0;
			virtual IGADeviceContext * getImmediateContext()const=0;
			virtual IGADeviceContext * createDeferredContext()=0;
			virtual IGAVertexBuffer * createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags=0,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr)=0;
			virtual IGAIndexBuffer * createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags=0,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr)=0;
			virtual IGAConstantBuffer * createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr)=0;
			virtual IGAShaderResourceBuffer* createShaderResourceBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags=0,UInt32 shaderResourceBufferFlags=0,UInt32 structureByteStride=0,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,ConstVoidPtr initialData=nullptr)=0;
			virtual IGATexture1D * createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture2D * createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture3D * createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture2D * createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGARenderTargetView* createRenderTargetView(IGATexture1D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0)=0;
			virtual IGARenderTargetView* createRenderTargetView(IGATexture2D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0)=0;
			virtual IGARenderTargetView* createRenderTargetView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice)=0;
			virtual IGADepthStencilView* createDepthStencilView(IGATexture1D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0)=0;
			virtual IGADepthStencilView* createDepthStencilView(IGATexture2D* resource,UInt32 mipSlice=0,UInt32 firstArraySlice=0)=0;
			virtual IGATextureView* createShaderResourceView(IGATexture1D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1,UInt32 firstArraySlice=0,UInt32 arrayCount=0)=0;
			virtual IGATextureView* createShaderResourceView(IGATexture2D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1,UInt32 firstArraySlice=0,UInt32 arrayCount=0)=0;
			virtual IGATextureView* createShaderResourceView(IGATexture3D* resource,UInt32 mostDetailedMip=0,UInt32 numMipLevels=-1)=0;
			virtual IGAShaderResourceBufferView* createShaderResourceView(IGAShaderResourceBuffer* resource,IGAEnum::EGIFormat format=IGAEnum::EGIFormat_UNKNOWN,UInt32 elementOffset=0,UInt32 numElements=-1)=0;
			virtual IGAVertexShader * createVertexShader(const std::string & code)=0;
			virtual IGAPixelShader * createPixelShader(const std::string & code)=0;
			virtual IGAGeometryShader * createGeometryShader(const std::string & code)=0;
			virtual IGAHullShader * createHullShader(const std::string & code)=0;
			virtual IGADomainShader * createDomainShader(const std::string & code)=0;
			virtual IGABlendState * createBlendState(const IGAStruct::SBlendDesc & desc)=0;
			virtual IGARasterizerState * createRasterizerState(const IGAStruct::SRasterizerDesc & desc)=0;
			virtual IGADepthStencilState * createDepthStencilState(const IGAStruct::SDepthStencilDesc & desc)=0;
			virtual IGASamplerState * createSamplerState(const IGAStruct::SSamplerDesc & desc)=0;
			virtual IGAProgram * createProgram(IGAVertexShader * vertexShader,IGAPixelShader * pixelShader,IGAGeometryShader * geometryShader=nullptr,IGAHullShader * hullShader=nullptr,IGADomainShader * domainShader=nullptr)=0;
			virtual IGAProgramReflection * createReflection(IGAProgram * program)=0;
			virtual Void destroyReflection(IGAProgramReflection * reflection)=0;
			virtual IGAProgramParameter * createProgramParameter()=0;
			virtual Void destroyProgramParameter(IGAProgramParameter * parameter)=0;
			virtual IGAVertexArrayObject* createVertexArrayObject(const TVector<IGAStruct::SVAOElementDesc>& inputElements)=0;
		};
	}
}