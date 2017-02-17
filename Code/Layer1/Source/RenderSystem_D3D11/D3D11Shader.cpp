#include "Precompiler.h"
#include "..\..\Include\RenderSystem_D3D11\D3D11Shader.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CShader::CShader(ID3DBlob * code)
	:mCode(code)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CShader::~CShader()
{
}

UInt32 NSDevilX::NSRenderSystem::NSD3D11::CShader::getSlot(const String & name) const
{
	return mResourceSlots.has(name)?mResourceSlots.get(name):-1;
}

NSDevilX::NSRenderSystem::NSD3D11::CVertexShader::CVertexShader(ID3DBlob * code)
	:CShader(code)
	,mInputLayout(nullptr)
{
	memset(mInputSlots,-1,sizeof(mInputSlots));
	decltype(getInternal()) temp_internal=nullptr;
	CSystemImp::getSingleton().getDevice()->CreateVertexShader(mCode->GetBufferPointer(),mCode->GetBufferSize(),NULL,&temp_internal);
	setInternal(temp_internal);
	CComPtr<ID3D11ShaderReflection> reflection;
	D3DReflect(mCode->GetBufferPointer(),mCode->GetBufferSize(),__uuidof(ID3D11ShaderReflection),reinterpret_cast<VoidPtr*>(&reflection));
	D3D11_SHADER_DESC shader_desc;
	reflection->GetDesc(&shader_desc);
	for(decltype(shader_desc.InputParameters) i=0;i<shader_desc.InputParameters;++i)
	{
		D3D11_SIGNATURE_PARAMETER_DESC input_parameter_desc;
		reflection->GetInputParameterDesc(i,&input_parameter_desc);
		if(("SV_VertexID"==String(input_parameter_desc.SemanticName)))
			continue;
		D3D11_INPUT_ELEMENT_DESC input_element_desc;
		input_element_desc.AlignedByteOffset=0;
		if((strcmp(input_parameter_desc.SemanticName,"SV_Position")==0)
			||(strcmp(input_parameter_desc.SemanticName,"NORMAL")==0)
			||(strcmp(input_parameter_desc.SemanticName,"TANGENT")==0)
			)
		{
			input_element_desc.Format=DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if(strcmp(input_parameter_desc.SemanticName,"TEXCOORD")==0)
		{
			input_element_desc.Format=DXGI_FORMAT_R32G32_FLOAT;
		}
		else if(strcmp(input_parameter_desc.SemanticName,"BLENDWEIGHT")==0)
		{
			input_element_desc.Format=DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
		else if(strcmp(input_parameter_desc.SemanticName,"BLENDINDICES")==0)
		{
			input_element_desc.Format=DXGI_FORMAT_R8G8B8A8_UINT;
		}
		else if(strcmp(input_parameter_desc.SemanticName,"DIFFUSE")==0)
		{
			input_element_desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
		}
		else
		{
			input_element_desc.Format=DXGI_FORMAT_UNKNOWN;
		}
		input_element_desc.InputSlot=i;
		input_element_desc.InputSlotClass=D3D11_INPUT_PER_VERTEX_DATA;
		input_element_desc.InstanceDataStepRate=0;
		input_element_desc.SemanticIndex=input_parameter_desc.SemanticIndex;
		input_element_desc.SemanticName=input_parameter_desc.SemanticName;
		mInputElementDescs.push_back(input_element_desc);
		if(strcmp(input_element_desc.SemanticName,"SV_Position")==0)
		{
			mInputSlots[i]=CEnum::EVertexBufferType_Position;
		}
		else if(strcmp(input_element_desc.SemanticName,"NORMAL")==0)
		{
			mInputSlots[i]=CEnum::EVertexBufferType_Normal;
		}
		else if(strcmp(input_element_desc.SemanticName,"TANGENT")==0)
		{
			mInputSlots[i]=CEnum::EVertexBufferType_Tangent;
		}
		else if(strcmp(input_element_desc.SemanticName,"TEXCOORD")==0)
		{
			switch(input_element_desc.SemanticIndex)
			{
			case 0:mInputSlots[i]=CEnum::EVertexBufferType_TextureCoord0;break;
			case 1:mInputSlots[i]=CEnum::EVertexBufferType_TextureCoord1;break;
			}		
		}
		else if(strcmp(input_element_desc.SemanticName,"BLENDWEIGHT")==0)
		{
			mInputSlots[i]=CEnum::EVertexBufferType_BlendWeight;
		}
		else if(strcmp(input_element_desc.SemanticName,"BLENDINDICES")==0)
		{
			mInputSlots[i]=CEnum::EVertexBufferType_BlendIndex;
		}
		else if(strcmp(input_element_desc.SemanticName,"DIFFUSE")==0)
		{
			mInputSlots[i]=CEnum::EVertexBufferType_Diffuse;
		}
	}
	for(decltype(shader_desc.BoundResources) i=0;i<shader_desc.BoundResources;++i)
	{
		D3D11_SHADER_INPUT_BIND_DESC input_bind_desc;
		reflection->GetResourceBindingDesc(i,&input_bind_desc);
		mResourceSlots[input_bind_desc.Name]=input_bind_desc.BindPoint;
	}
	for(decltype(shader_desc.ConstantBuffers) i=0;i<shader_desc.ConstantBuffers;++i)
	{
		ID3D11ShaderReflectionConstantBuffer * cb_reflection=reflection->GetConstantBufferByIndex(i);
		D3D11_SHADER_BUFFER_DESC shader_buffer_desc;
		cb_reflection->GetDesc(&shader_buffer_desc);
		CSystemImp::getSingleton().getConstantBufferDescriptionManager()->registerDescription(cb_reflection);
	}
	if(!mInputElementDescs.empty())
		mInputLayout=CSystemImp::getSingleton().getInputLayout(&mInputElementDescs[0],static_cast<UINT>(mInputElementDescs.size()));
}

NSDevilX::NSRenderSystem::NSD3D11::CVertexShader::~CVertexShader()
{
}

NSDevilX::NSRenderSystem::NSD3D11::CPixelShader::CPixelShader(ID3DBlob * code)
	:CShader(code)
{
	decltype(getInternal()) temp_internal=nullptr;
	CSystemImp::getSingleton().getDevice()->CreatePixelShader(mCode->GetBufferPointer(),mCode->GetBufferSize(),NULL,&temp_internal);
	setInternal(temp_internal);
	CComPtr<ID3D11ShaderReflection> reflection;
	D3DReflect(mCode->GetBufferPointer(),mCode->GetBufferSize(),__uuidof(ID3D11ShaderReflection),reinterpret_cast<VoidPtr*>(&reflection));
	D3D11_SHADER_DESC shader_desc;
	reflection->GetDesc(&shader_desc);
	for(decltype(shader_desc.BoundResources) i=0;i<shader_desc.BoundResources;++i)
	{
		D3D11_SHADER_INPUT_BIND_DESC input_bind_desc;
		reflection->GetResourceBindingDesc(i,&input_bind_desc);
		mResourceSlots[input_bind_desc.Name]=input_bind_desc.BindPoint;
	}
	for(decltype(shader_desc.ConstantBuffers) i=0;i<shader_desc.ConstantBuffers;++i)
	{
		ID3D11ShaderReflectionConstantBuffer * cb_reflection=reflection->GetConstantBufferByIndex(i);
		D3D11_SHADER_BUFFER_DESC shader_buffer_desc;
		cb_reflection->GetDesc(&shader_buffer_desc);
		CSystemImp::getSingleton().getConstantBufferDescriptionManager()->registerDescription(cb_reflection);
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CPixelShader::~CPixelShader()
{
}

NSDevilX::NSRenderSystem::NSD3D11::CHullShader::CHullShader(ID3DBlob * code)
	:CShader(code)
{
	decltype(getInternal()) temp_internal=nullptr;
	CSystemImp::getSingleton().getDevice()->CreateHullShader(mCode->GetBufferPointer(),mCode->GetBufferSize(),NULL,&temp_internal);
	setInternal(temp_internal);
	CComPtr<ID3D11ShaderReflection> reflection;
	D3DReflect(mCode->GetBufferPointer(),mCode->GetBufferSize(),__uuidof(ID3D11ShaderReflection),reinterpret_cast<VoidPtr*>(&reflection));
	D3D11_SHADER_DESC shader_desc;
	reflection->GetDesc(&shader_desc);
	for(decltype(shader_desc.BoundResources) i=0;i<shader_desc.BoundResources;++i)
	{
		D3D11_SHADER_INPUT_BIND_DESC input_bind_desc;
		reflection->GetResourceBindingDesc(i,&input_bind_desc);
		mResourceSlots[input_bind_desc.Name]=input_bind_desc.BindPoint;
	}
	for(decltype(shader_desc.ConstantBuffers) i=0;i<shader_desc.ConstantBuffers;++i)
	{
		ID3D11ShaderReflectionConstantBuffer * cb_reflection=reflection->GetConstantBufferByIndex(i);
		D3D11_SHADER_BUFFER_DESC shader_buffer_desc;
		cb_reflection->GetDesc(&shader_buffer_desc);
		CSystemImp::getSingleton().getConstantBufferDescriptionManager()->registerDescription(cb_reflection);
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CHullShader::~CHullShader()
{}

NSDevilX::NSRenderSystem::NSD3D11::CDomainShader::CDomainShader(ID3DBlob * code)
	:CShader(code)
{
	decltype(getInternal()) temp_internal=nullptr;
	CSystemImp::getSingleton().getDevice()->CreateDomainShader(mCode->GetBufferPointer(),mCode->GetBufferSize(),NULL,&temp_internal);
	setInternal(temp_internal);
	CComPtr<ID3D11ShaderReflection> reflection;
	D3DReflect(mCode->GetBufferPointer(),mCode->GetBufferSize(),__uuidof(ID3D11ShaderReflection),reinterpret_cast<VoidPtr*>(&reflection));
	D3D11_SHADER_DESC shader_desc;
	reflection->GetDesc(&shader_desc);
	for(decltype(shader_desc.BoundResources) i=0;i<shader_desc.BoundResources;++i)
	{
		D3D11_SHADER_INPUT_BIND_DESC input_bind_desc;
		reflection->GetResourceBindingDesc(i,&input_bind_desc);
		mResourceSlots[input_bind_desc.Name]=input_bind_desc.BindPoint;
	}
	for(decltype(shader_desc.ConstantBuffers) i=0;i<shader_desc.ConstantBuffers;++i)
	{
		ID3D11ShaderReflectionConstantBuffer * cb_reflection=reflection->GetConstantBufferByIndex(i);
		D3D11_SHADER_BUFFER_DESC shader_buffer_desc;
		cb_reflection->GetDesc(&shader_buffer_desc);
		CSystemImp::getSingleton().getConstantBufferDescriptionManager()->registerDescription(cb_reflection);
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CDomainShader::~CDomainShader()
{}
