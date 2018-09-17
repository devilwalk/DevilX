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

CProgramBufferLayoutImp * NSDevilX::NSRenderSystem::NSD3D11::CShaderImp::getBufferLayout(const String & name)
{
	auto ret=mBufferLayout.get(name);
	if((!ret)&&(mShader->getSlot(name)!=static_cast<UInt32>(-1)))
	{
		CComPtr<ID3D11ShaderReflection> reflection;
		D3DReflect(mShader->getBlob()->GetBufferPointer(),mShader->getBlob()->GetBufferSize(),__uuidof(ID3D11ShaderReflection),reinterpret_cast<VoidPtr*>(&reflection));	
		ret=DEVILX_NEW CProgramBufferLayoutImp(reflection->GetConstantBufferByName(name.c_str()));
		mBufferLayout.add(name,ret);
	}
	return ret;
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
	_rebuildResourceNames();
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
					ret=IEnum::EProgramResourceType_ConstantBuffer;
					break;
				case D3D_SIT_TBUFFER:
					ret=IEnum::EProgramResourceType_TextureBuffer;
					break;
				case  D3D_SIT_TEXTURE:
					ret=IEnum::EProgramResourceType_Texture;
					break;
				case D3D_SIT_SAMPLER:
					ret=IEnum::EProgramResourceType_Sampler;
					break;
				}
			}
		}
	}
	return ret;
}

UInt32 NSDevilX::NSRenderSystem::NSD3D11::CProgramImp::getResourceLocation(const String & name) const
{
	auto iter=mResourceNames.find(name);
	if(mResourceNames.end()==iter)
		return -1;
	else
		return iter-mResourceNames.begin();
}

IProgramBufferLayout * NSDevilX::NSRenderSystem::NSD3D11::CProgramImp::getBufferLayout(UInt32 resourceLocation) const
{
	CProgramBufferLayoutImp * ret=nullptr;
	for(auto s:mShaders)
	{
		if(s&&(ret=s->getBufferLayout(mResourceNames[resourceLocation])))
		{
			break;
		}
	}
	return ret;
}

Void NSDevilX::NSRenderSystem::NSD3D11::CProgramImp::_rebuildResourceNames()
{
	mResourceNames.clear();
	for(auto shader:mShaders)
	{
		if(shader)
		{
			for(auto & res:shader->getShader()->getResourceSlots())
			{
				if(!mResourceNames.has(res.first))
				{
					mResourceNames.push_back(res.first);
				}
			}
		}
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CProgramBufferLayoutImp::CProgramBufferLayoutImp(ID3D11ShaderReflectionConstantBuffer * internalObj)
{
	setInternal(internalObj);
}

NSDevilX::NSRenderSystem::NSD3D11::CProgramBufferLayoutImp::~CProgramBufferLayoutImp()
{}

UInt32 NSDevilX::NSRenderSystem::NSD3D11::CProgramBufferLayoutImp::getOffset(const String & name) const
{
	CComPtr<ID3D11ShaderReflectionVariable> var=getInternal()->GetVariableByName(name.c_str());
	if(var.p)
	{
		D3D11_SHADER_VARIABLE_DESC desc;
		var->GetDesc(&desc);
		return desc.StartOffset;
	}
	else
		return -1;
}

UInt32 NSDevilX::NSRenderSystem::NSD3D11::CProgramBufferLayoutImp::getSize(const String & name) const
{
	CComPtr<ID3D11ShaderReflectionVariable> var=getInternal()->GetVariableByName(name.c_str());
	if(var.p)
	{
		D3D11_SHADER_VARIABLE_DESC desc;
		var->GetDesc(&desc);
		return desc.Size;
	}
	else
		return -1;
}
