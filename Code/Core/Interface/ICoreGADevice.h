#pragma once
#include "ICoreGAStruct.h"
#include "ICoreGACommandQueue.h"
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
			virtual IGABuffer * createBuffer(const IGAStruct::SBufferDesc & desc,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture1D * createTexture1D(const IGAStruct::STexture1DDesc & desc,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture2D * createTexture2D(const IGAStruct::STexture2DDesc & desc,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGATexture3D * createTexture3D(const IGAStruct::STexture3DDesc & desc,const IGAStruct::SSubResourceData * initialData=nullptr)=0;
			virtual IGAShaderResourceView * createShaderResourceView(IGAResource * resource,const IGAStruct::SShaderResourceViewDesc * desc=nullptr)=0;
			virtual IGAInputLayout * createInputLayout(const IGAStruct::SInputLayoutDesc & desc)=0;
			virtual IGAShader * createShader(IGAEnum::EShaderType type,ConstVoidPtr code,SizeT codeSize)=0;
			virtual IGAPipelineState * createPipelineState(const IGAStruct::SBlendDesc & blend,const IGAStruct::SDepthStencilDesc & depthStencil,const IGAStruct::SRasterizerDesc & rasterizer)=0;
			virtual IGASampler * createSampler(const IGAStruct::SSamplerDesc & desc)=0;
			virtual IGACommandQueue * createCommandQueue()
		};
	}
}