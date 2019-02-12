#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDX11
		{
			class IGPUDeviceImp
				:public TBaseObject<IGPUDeviceImp>
				,public IGPUDevice
			{
			protected:
				ID3D11Device * mDevice;
				ID3D11DeviceContext * mImmediateContext;
			public:
				IGPUDeviceImp();
				~IGPUDeviceImp();

				// Í¨¹ý IGPUDevice ¼Ì³Ð
				virtual IGPUBuffer * createBuffer(const IGPUStruct::SBufferDesc & desc,const IGPUStruct::SSubResourceData * initialData=nullptr) override;
				virtual IGPUTexture1D * createTexture1D(const IGPUStruct::STexture1DDesc & desc,const IGPUStruct::SSubResourceData * initialData=nullptr) override;
				virtual IGPUTexture2D * createTexture2D(const IGPUStruct::STexture2DDesc & desc,const IGPUStruct::SSubResourceData * initialData=nullptr) override;
				virtual IGPUTexture3D * createTexture3D(const IGPUStruct::STexture3DDesc & desc,const IGPUStruct::SSubResourceData * initialData=nullptr) override;
				virtual IGPUInputLayout * createInputLayout(const IGPUStruct::SInputLayoutDesc & desc) override;
				virtual IGPUShader * createShader(ConstVoidPtr code,SizeT codeSize,IGPUEnum::EShaderType type) override;
				virtual IGPUPipelineState * createBlendState(const IGPUStruct::SBlendDesc & desc) override;
				virtual IGPUPipelineState * createDepthStencilState(const IGPUStruct::SDepthStencilDesc & desc) override;
				virtual IGPUPipelineState * createRasterizerState(const IGPUStruct::SRasterizerDesc & desc) override;
				virtual IGPUSampler * createSampler(const IGPUStruct::SSamplerDesc & desc) override;
			};
		}
	}
}