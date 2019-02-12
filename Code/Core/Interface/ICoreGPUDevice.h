#pragma once
#include "ICoreGPUStruct.h"
#include "ICoreGPUCommandQueue.h"
#include "ICoreGPUResource.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGPUDevice
		{
		protected:
			virtual ~IGPUDevice(){ }
		public:
			virtual IGPUBuffer * createBuffer(const IGPUStruct::SBufferDesc & desc,const IGPUStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGPUTexture1D * createTexture1D(const IGPUStruct::STexture1DDesc & desc,const IGPUStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGPUTexture2D * createTexture2D(const IGPUStruct::STexture2DDesc & desc,const IGPUStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGPUTexture3D * createTexture3D(const IGPUStruct::STexture3DDesc & desc,const IGPUStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGPUInputLayout * createInputLayout(const IGPUStruct::SInputLayoutDesc & desc)=0;
			virtual IGPUShader * createShader(ConstVoidPtr code,SizeT codeSize,IGPUEnum::EShaderType type)=0;
			virtual IGPUPipelineState * createBlendState(const IGPUStruct::SBlendDesc & desc)=0;
			virtual IGPUPipelineState * createDepthStencilState(const IGPUStruct::SDepthStencilDesc & desc)=0;
			virtual IGPUPipelineState * createRasterizerState(const IGPUStruct::SRasterizerDesc & desc)=0;
			virtual IGPUSampler * createSampler(const IGPUStruct::SSamplerDesc & desc)=0;
		};
		class IGPUDevice12
		{
		protected:
			virtual ~IGPUDevice12(){}
		public:
			virtual IGPUDevice * queryInterface_IGPUDevice()=0;
			virtual IGPUHeap * createHeap(const IGPUStruct::SHeapDesc & desc)=0;
			virtual IGPUDeviceResource * createPlacedResource(IGPUHeap * heap,UInt64 heapOffset,const IGPUStruct::SResourceDesc & desc,IGPUEnum::EResourceState initialState,const IGPUStruct::SClearValue * clearValue=nullptr)=0;
		};
	}
}