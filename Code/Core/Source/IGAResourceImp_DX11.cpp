#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;
using namespace NSVersion11;

NSDevilX::NSCore::NSDirectX::NSVersion11::IGABufferImp::IGABufferImp(ID3D11Device * device,const D3D11_BUFFER_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData)
{
	device->CreateBuffer(&desc,initialData,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGABufferImp::~IGABufferImp()
{
}

IGABuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGABufferImp::queryInterface_IGABuffer()
{
	return this;
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture1DImp::IGATexture1DImp(ID3D11Device * device,const D3D11_TEXTURE1D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData)
{
	device->CreateTexture1D(&desc,initialData,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture1DImp::~IGATexture1DImp()
{
}

IGATexture * NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture1DImp::queryInterface_IGATexture()
{
	return this;
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture2DImp::IGATexture2DImp(ID3D11Device * device,const D3D11_TEXTURE2D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData)
{
	device->CreateTexture2D(&desc,initialData,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture2DImp::~IGATexture2DImp()
{
}

IGATexture * NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture2DImp::queryInterface_IGATexture()
{
	return this;
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture3DImp::IGATexture3DImp(ID3D11Device * device,const D3D11_TEXTURE3D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData)
{
	device->CreateTexture3D(&desc,initialData,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture3DImp::~IGATexture3DImp()
{
}

IGATexture * NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture3DImp::queryInterface_IGATexture()
{
	return this;
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAInputLayoutImp::IGAInputLayoutImp(ID3D11Device * device,const TVector<D3D11_INPUT_ELEMENT_DESC>& desc)
{
	String hlsl="void main(";
	for(UInt32 i=0,count=static_cast<UInt32>(desc.size());i<count;++i)
	{
		switch(desc[i].Format)
		{
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			hlsl+="float4";
			break;
		case DXGI_FORMAT_R32G32B32_FLOAT:
			hlsl+="float3";
			break;
		case DXGI_FORMAT_R32G32_FLOAT:
			hlsl+="float2";
			break;
		case DXGI_FORMAT_R32_FLOAT:
			hlsl+="float";
			break;
		case DXGI_FORMAT_R32G32B32A32_UINT:
		case DXGI_FORMAT_R8G8B8A8_UINT:
			hlsl+="uint4";
			break;
		case DXGI_FORMAT_R32G32B32_UINT:
			hlsl+="uint3";
			break;
		case DXGI_FORMAT_R32G32_UINT:
			hlsl+="uint2";
			break;
		case DXGI_FORMAT_R32_UINT:
			hlsl+="uint";
			break;
		case DXGI_FORMAT_R32G32B32A32_SINT:
			hlsl+="int4";
			break;
		case DXGI_FORMAT_R32G32B32_SINT:
			hlsl+="int3";
			break;
		case DXGI_FORMAT_R32G32_SINT:
			hlsl+="int2";
			break;
		case DXGI_FORMAT_R32_SINT:
			hlsl+="int";
			break;
		default:
			assert(0);
		}
		hlsl+=" inputParameter"+CStringUtility::toString(i)+":"+desc[i].SemanticName+CStringUtility::toString(desc[i].SemanticIndex)+",";
	}
	hlsl+="out float4 outputParameter:SV_Position){outputParameter=1;}";
	CComPtr<ID3DBlob> code;
	CComPtr<ID3DBlob> error;
	D3DCompile(&hlsl[0],hlsl.size(),"temp",nullptr,nullptr,"main","vs_5_0",D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3,0,&code,&error);
	if(error.p)
	{
		OutputDebugStringA(static_cast<LPCSTR>(error->GetBufferPointer()));
	}
	device->CreateInputLayout(&desc[0],static_cast<UInt32>(desc.size()),code->GetBufferPointer(),code->GetBufferSize(),&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAInputLayoutImp::~IGAInputLayoutImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAVertexShaderImp::IGAVertexShaderImp(ID3D11Device * device,const String & hlsl)
{
	CComPtr<ID3DBlob> code;
	CComPtr<ID3DBlob> error;
	UInt32 flag=0;
#if DEVILX_DEBUG
	flag=D3DCOMPILE_DEBUG|D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	flag=D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif
	D3DCompile(&hlsl[0],hlsl.size(),"temp",nullptr,nullptr,"main","vs_5_0",flag,0,&code,&error);
	if(error.p)
	{
		OutputDebugStringA(static_cast<LPCSTR>(error->GetBufferPointer()));
	}
	device->CreateVertexShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAVertexShaderImp::~IGAVertexShaderImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAGeometryShaderImp::IGAGeometryShaderImp(ID3D11Device * device,const String & hlsl)
{
	CComPtr<ID3DBlob> code;
	CComPtr<ID3DBlob> error;
	UInt32 flag=0;
#if DEVILX_DEBUG
	flag=D3DCOMPILE_DEBUG|D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	flag=D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif
	D3DCompile(&hlsl[0],hlsl.size(),"temp",nullptr,nullptr,"main","gs_5_0",flag,0,&code,&error);
	if(error.p)
	{
		OutputDebugStringA(static_cast<LPCSTR>(error->GetBufferPointer()));
	}
	device->CreateGeometryShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAGeometryShaderImp::~IGAGeometryShaderImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAPixelShaderImp::IGAPixelShaderImp(ID3D11Device * device,const String & hlsl)
{
	CComPtr<ID3DBlob> code;
	CComPtr<ID3DBlob> error;
	UInt32 flag=0;
#if DEVILX_DEBUG
	flag=D3DCOMPILE_DEBUG|D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	flag=D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif
	D3DCompile(&hlsl[0],hlsl.size(),"temp",nullptr,nullptr,"main","ps_5_0",flag,0,&code,&error);
	if(error.p)
	{
		OutputDebugStringA(static_cast<LPCSTR>(error->GetBufferPointer()));
	}
	device->CreatePixelShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAPixelShaderImp::~IGAPixelShaderImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAHullShaderImp::IGAHullShaderImp(ID3D11Device * device,const String & hlsl)
{
	CComPtr<ID3DBlob> code;
	CComPtr<ID3DBlob> error;
	UInt32 flag=0;
#if DEVILX_DEBUG
	flag=D3DCOMPILE_DEBUG|D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	flag=D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif
	D3DCompile(&hlsl[0],hlsl.size(),"temp",nullptr,nullptr,"main","hs_5_0",flag,0,&code,&error);
	if(error.p)
	{
		OutputDebugStringA(static_cast<LPCSTR>(error->GetBufferPointer()));
	}
	device->CreateHullShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAHullShaderImp::~IGAHullShaderImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADomainShaderImp::IGADomainShaderImp(ID3D11Device * device,const String & hlsl)
{
	CComPtr<ID3DBlob> code;
	CComPtr<ID3DBlob> error;
	UInt32 flag=0;
#if DEVILX_DEBUG
	flag=D3DCOMPILE_DEBUG|D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	flag=D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif
	D3DCompile(&hlsl[0],hlsl.size(),"temp",nullptr,nullptr,"main","ds_5_0",flag,0,&code,&error);
	if(error.p)
	{
		OutputDebugStringA(static_cast<LPCSTR>(error->GetBufferPointer()));
	}
	device->CreateDomainShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADomainShaderImp::~IGADomainShaderImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAComputeShaderImp::IGAComputeShaderImp(ID3D11Device * device,const String & hlsl)
{
	CComPtr<ID3DBlob> code;
	CComPtr<ID3DBlob> error;
	UInt32 flag=0;
#if DEVILX_DEBUG
	flag=D3DCOMPILE_DEBUG|D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	flag=D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif
	D3DCompile(&hlsl[0],hlsl.size(),"temp",nullptr,nullptr,"main","cs_5_0",flag,0,&code,&error);
	if(error.p)
	{
		OutputDebugStringA(static_cast<LPCSTR>(error->GetBufferPointer()));
	}
	device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAComputeShaderImp::~IGAComputeShaderImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGASamplerStateImp::IGASamplerStateImp(ID3D11Device * device,const D3D11_SAMPLER_DESC & desc)
{
	device->CreateSamplerState(&desc,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGASamplerStateImp::~IGASamplerStateImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGABlendStateImp::IGABlendStateImp(ID3D11Device * device,const D3D11_BLEND_DESC & desc)
{
	device->CreateBlendState(&desc,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGABlendStateImp::~IGABlendStateImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGARasterizerStateImp::IGARasterizerStateImp(ID3D11Device * device,const D3D11_RASTERIZER_DESC & desc)
{
	device->CreateRasterizerState(&desc,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGARasterizerStateImp::~IGARasterizerStateImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADepthStencilStateImp::IGADepthStencilStateImp(ID3D11Device * device,const D3D11_DEPTH_STENCIL_DESC & desc)
{
	device->CreateDepthStencilState(&desc,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADepthStencilStateImp::~IGADepthStencilStateImp()
{
}
