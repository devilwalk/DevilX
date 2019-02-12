#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDX11;

NSDevilX::NSCore::NSDX11::IGPUDeviceImp::IGPUDeviceImp()
	:mDevice(nullptr)
	,mImmediateContext(nullptr)
{
	UINT flags=0;
#if DEVILX_DEBUG
	flags|=D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL levels[]={D3D_FEATURE_LEVEL_11_1};
	D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,flags,levels,_countof(levels),D3D11_SDK_VERSION,&mDevice,levels,&mImmediateContext);
}

NSDevilX::NSCore::NSDX11::IGPUDeviceImp::~IGPUDeviceImp()
{
	DEVILX_COM_SAFE_RELEASE(mImmediateContext);
	DEVILX_COM_SAFE_RELEASE(mDevice);
}

IGPUBuffer * NSDevilX::NSCore::NSDX11::IGPUDeviceImp::createBuffer(const IGPUStruct::SBufferDesc & desc,const IGPUStruct::SSubResourceData * initialData)
{
	return nullptr;
}

IGPUTexture1D * NSDevilX::NSCore::NSDX11::IGPUDeviceImp::createTexture1D(const IGPUStruct::STexture1DDesc & desc,const IGPUStruct::SSubResourceData * initialData)
{
	return nullptr;
}

IGPUTexture2D * NSDevilX::NSCore::NSDX11::IGPUDeviceImp::createTexture2D(const IGPUStruct::STexture2DDesc & desc,const IGPUStruct::SSubResourceData * initialData)
{
	return nullptr;
}

IGPUTexture3D * NSDevilX::NSCore::NSDX11::IGPUDeviceImp::createTexture3D(const IGPUStruct::STexture3DDesc & desc,const IGPUStruct::SSubResourceData * initialData)
{
	return nullptr;
}

IGPUInputLayout * NSDevilX::NSCore::NSDX11::IGPUDeviceImp::createInputLayout(const IGPUStruct::SInputLayoutDesc & desc)
{
	return nullptr;
}

IGPUShader * NSDevilX::NSCore::NSDX11::IGPUDeviceImp::createShader(ConstVoidPtr code,SizeT codeSize,IGPUEnum::EShaderType type)
{
	return nullptr;
}

IGPUPipelineState * NSDevilX::NSCore::NSDX11::IGPUDeviceImp::createBlendState(const IGPUStruct::SBlendDesc & desc)
{
	return nullptr;
}

IGPUPipelineState * NSDevilX::NSCore::NSDX11::IGPUDeviceImp::createDepthStencilState(const IGPUStruct::SDepthStencilDesc & desc)
{
	return nullptr;
}

IGPUPipelineState * NSDevilX::NSCore::NSDX11::IGPUDeviceImp::createRasterizerState(const IGPUStruct::SRasterizerDesc & desc)
{
	return nullptr;
}

IGPUSampler * NSDevilX::NSCore::NSDX11::IGPUDeviceImp::createSampler(const IGPUStruct::SSamplerDesc & desc)
{
	return nullptr;
}
