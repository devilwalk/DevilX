#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

IGADeviceImp::IGADeviceImp()
{
}

IGADeviceImp::~IGADeviceImp()
{

}

IGADeviceContext * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::getImmediateContext() const
{
	return const_cast<IGADeviceImp*>(this);
}

IGADeviceContext * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createDeferredContext()
{
	return nullptr;
}

IGAVertexBuffer * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGAIndexBuffer * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGAConstantBuffer * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGAUnorderedAccessBuffer * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage=IGAEnum::EUsage_DEFAULT,UInt32 bindFlags=0,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGATexture1D * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGATexture2D * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGATexture3D * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGATexture2D * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount=0,UInt32 arrayCount=1,const IGAStruct::SSubResourceData * initialData=nullptr)
{
	return nullptr;
}

IGAShaderResourceView * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createShaderResourceView(IGAResource * resource,const IGAStruct::SShaderResourceViewDesc * desc=nullptr)
{
	return nullptr;
}

IGAInputLayout * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createInputLayout(const IGAStruct::SInputLayoutDesc & desc)
{
	return nullptr;
}

IGABlendState * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createBlendState(const IGAStruct::SBlendDesc & blend)
{
	return nullptr;
}

IGARasterizerState * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createRasterizerState(const IGAStruct::SRasterizerDesc & blend)
{
	return nullptr;
}

IGADepthStencilState * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createDepthStencilState(const IGAStruct::SDepthStencilDesc & blend)
{
	return nullptr;
}

IGASamplerState * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createSamplerState(const IGAStruct::SSamplerDesc & desc)
{
	return nullptr;
}

IGAVertexShader * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createVertexShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}

IGAPixelShader * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createPixelShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}

IGAGeometryShader * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createGeometryShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}

IGAHullShader * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createHullShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}

IGADomainShader * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createDomainShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}

IGAComputeShader * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createComputeShader(ConstVoidPtr code,SizeT codeSize)
{
	return nullptr;
}

IGAShaderReflection * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createShaderReflection(IGAShader * const * shaders,UInt32 numShaders)
{
	return nullptr;
}
