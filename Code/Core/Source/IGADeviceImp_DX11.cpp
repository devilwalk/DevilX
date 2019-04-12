#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;
using namespace NSVersion11;

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::IGADeviceImp()
	:mFeatureLevel(D3D_FEATURE_LEVEL_9_3)
{
	UINT flags=0;
#if DEVILX_DEBUG
	flags|=D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL levels[]={D3D_FEATURE_LEVEL_11_1,D3D_FEATURE_LEVEL_11_0,D3D_FEATURE_LEVEL_10_1,D3D_FEATURE_LEVEL_10_0,D3D_FEATURE_LEVEL_9_3};
	D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,flags,levels,_countof(levels),D3D11_SDK_VERSION,&mInternal,levels,nullptr);
	mFeatureLevel=levels[0];
	mContexts.push_back(DEVILX_NEW IGADeviceContextImp(False));
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::~IGADeviceImp()
{
	mContexts.destroyAll();
}

IGADeviceContext * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::getImmediateContext() const
{
	return mContexts[0];
}

IGADeviceContext * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createDeferredContext()
{
	IGADeviceContextImp * ret=nullptr;
	D3D11_FEATURE_DATA_THREADING feature={0};
	mInternal->CheckFeatureSupport(D3D11_FEATURE_THREADING,&feature,sizeof(feature));
	if(feature.DriverCommandLists)
	{
		ret=DEVILX_NEW IGADeviceContextImp(True);
		mContexts.push_back(ret);
	}
	return ret;
}

IGAVertexBuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGAIndexBuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGAConstantBuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGAUnorderedAccessBuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGATexture1D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGATexture2D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGATexture3D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGATexture2D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGAShaderResourceView * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createShaderResourceView(IGAResource * resource,const IGAStruct::SShaderResourceViewDesc * desc=nullptr)
{
	return nullptr;
}

IGAInputLayout * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createInputLayout(const IGAStruct::SInputLayoutDesc & desc)
{
	return nullptr;
}

IGABlendState * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createBlendState(const IGAStruct::SBlendDesc & desc)
{
	auto d3d_desc=CUtility::mapping(desc);
	auto & ret=mBlendStates[d3d_desc];
	if(!ret)
		ret=DEVILX_NEW IGABlendStateImp(mInternal,d3d_desc);
	return ret;
}

IGARasterizerState * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createRasterizerState(const IGAStruct::SRasterizerDesc & desc)
{
	return nullptr;
}

IGADepthStencilState * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createDepthStencilState(const IGAStruct::SDepthStencilDesc & desc)
{
	return nullptr;
}

IGASamplerState * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createSamplerState(const IGAStruct::SSamplerDesc & desc)
{
	return nullptr;
}

IGAVertexShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createVertexShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}

IGAPixelShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createPixelShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}

IGAGeometryShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createGeometryShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}

IGAHullShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createHullShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}

IGADomainShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createDomainShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}

IGAComputeShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createComputeShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}