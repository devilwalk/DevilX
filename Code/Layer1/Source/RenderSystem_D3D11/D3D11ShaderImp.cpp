#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CShaderImp::CShaderImp()
	:mType(IEnum::EShaderType_VS)
	,mCodeType(IEnum::EShaderCodeType_HLSL_5_0)
	,mShader(nullptr)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CShaderImp::~CShaderImp()
{
}

Boolean NSDevilX::NSRenderSystem::NSD3D11::CShaderImp::compile(IEnum::EShaderType type,IEnum::EShaderCodeType codeType,const String & code)
{
	mType=type;
	mCodeType=codeType;
	switch(mType)
	{
	case IEnum::EShaderType_VS:
		mShader=CSystemImp::getSingleton().getVertexShader(CSystemImp::getSingleton().getShaderCodeManager()->registerShader(getName(),code,type,codeType));
		break;
	case IEnum::EShaderType_PS:
		mShader=CSystemImp::getSingleton().getPixelShader(CSystemImp::getSingleton().getShaderCodeManager()->registerShader(getName(),code,type,codeType));
		break;
	}
}

IEnum::EShaderType NSDevilX::NSRenderSystem::NSD3D11::CShaderImp::getType() const
{
	return mType;
}

IEnum::EShaderCodeType NSDevilX::NSRenderSystem::NSD3D11::CShaderImp::getCodeType() const
{
	return mCodeType;
}

NSDevilX::NSRenderSystem::NSD3D11::CProgramImp::CProgramImp()
{
	ZeroMemory(&mShaders[0],sizeof(mShaders[0])*mShaders.size());
}

NSDevilX::NSRenderSystem::NSD3D11::CProgramImp::~CProgramImp()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CProgramImp::setShader(IEnum::EShaderType type,IShader * shader)
{
	mShaders[type]=static_cast<CShaderImp*>(shader);
}

IShader * NSDevilX::NSRenderSystem::NSD3D11::CProgramImp::getShader(IEnum::EShaderType type) const
{
	return mShaders[type];
}

IEnum::EProgramResourceType NSDevilX::NSRenderSystem::NSD3D11::CProgramImp::getResourceType(const String & name) const
{
	IEnum::EProgramResourceType ret=IEnum::EProgramResourceType_Unknown;
	for(auto shader:mShaders)
	{
		if(shader)
		{
			CComPtr<ID3D11ShaderReflection> reflection;
			D3DReflect(shader->getShader()->getBlob()->GetBufferPointer(),shader->getShader()->getBlob()->GetBufferSize(),__uuidof(ID3D11ShaderReflection),reinterpret_cast<VoidPtr*>(&reflection));
			D3D11_SHADER_DESC shader_desc;
			reflection->GetDesc(&shader_desc);
			for(decltype(shader_desc.BoundResources) i=0;i<shader_desc.BoundResources;++i)
			{
				D3D11_SHADER_INPUT_BIND_DESC input_bind_desc;
				reflection->GetResourceBindingDesc(i,&input_bind_desc);
				switch(input_bind_desc.Type)
				{
				case D3D_SIT_CBUFFER:
					break;
				case D3D_SIT_TBUFFER:
					break;
				case  D3D_SIT_TEXTURE:
					break;
				case D3D_SIT_SAMPLER:
					break;
				}
			}
		}
	}
	return ret;
}

UInt32 NSDevilX::NSRenderSystem::NSD3D11::CProgramImp::getResourceLocation(const String & name) const
{
	return UInt32();
}

IProgramBufferLayout * NSDevilX::NSRenderSystem::NSD3D11::CProgramImp::getBufferLayout(UInt32 resourceLocation) const
{
	return nullptr;
}
