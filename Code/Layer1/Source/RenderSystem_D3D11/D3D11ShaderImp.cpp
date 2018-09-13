#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CShaderImp::CShaderImp()
	:mType(IEnum::EShaderType_VS)
	,mCodeType(IEnum::EShaderCodeType_HLSL_5_0)
	,mBlob(nullptr)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CShaderImp::~CShaderImp()
{
	DEVILX_COM_SAFE_RELEASE(mBlob);
}

Boolean NSDevilX::NSRenderSystem::NSD3D11::CShaderImp::compile(IEnum::EShaderType type,IEnum::EShaderCodeType codeType,const String & code)
{
	mType=type;
	mCodeType=codeType;
}

IEnum::EShaderType NSDevilX::NSRenderSystem::NSD3D11::CShaderImp::getType() const
{
	return mType;
}

IEnum::EShaderCodeType NSDevilX::NSRenderSystem::NSD3D11::CShaderImp::getCodeType() const
{
	return mCodeType;
}
