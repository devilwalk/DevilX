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

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATextureImp::IGATextureImp()
{}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATextureImp::~IGATextureImp()
{}

IGATexture * NSDevilX::NSCore::NSDirectX::NSVersion11::IGATextureImp::queryInterface_IGATexture()
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

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture2DImp::IGATexture2DImp(ID3D11Device * device,const D3D11_TEXTURE2D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData)
{
	device->CreateTexture2D(&desc,initialData,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture2DImp::~IGATexture2DImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture3DImp::IGATexture3DImp(ID3D11Device * device,const D3D11_TEXTURE3D_DESC & desc,const D3D11_SUBRESOURCE_DATA * initialData)
{
	device->CreateTexture3D(&desc,initialData,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGATexture3DImp::~IGATexture3DImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAInputLayoutImp::IGAInputLayoutImp(ID3D11Device * device,const TVector(D3D11_INPUT_ELEMENT_DESC)& desc)
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

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderImp::IGAShaderImp()
{}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderImp::~IGAShaderImp()
{}

IGAShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderImp::queryInterface_IGAShader()
{
	return this;
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAVertexShaderImp::IGAVertexShaderImp(ID3D11Device * device,const String & hlsl)
{
	auto & code=IGAShaderImp::mInternal;
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
	auto & internal_ref=TD3DObjectContainer<ID3D11VertexShader>::mInternal;
	device->CreateVertexShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&internal_ref);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAVertexShaderImp::~IGAVertexShaderImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAGeometryShaderImp::IGAGeometryShaderImp(ID3D11Device * device,const String & hlsl)
{
	auto & code=IGAShaderImp::mInternal;
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
	auto & internal_ref=TD3DObjectContainer<ID3D11GeometryShader>::mInternal;
	device->CreateGeometryShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&internal_ref);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAGeometryShaderImp::~IGAGeometryShaderImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAPixelShaderImp::IGAPixelShaderImp(ID3D11Device * device,const String & hlsl)
{
	auto & code=IGAShaderImp::mInternal;
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
	auto & internal_ref=TD3DObjectContainer<ID3D11PixelShader>::mInternal;
	device->CreatePixelShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&internal_ref);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAPixelShaderImp::~IGAPixelShaderImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAHullShaderImp::IGAHullShaderImp(ID3D11Device * device,const String & hlsl)
{
	auto & code=IGAShaderImp::mInternal;
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
	auto & internal_ref=TD3DObjectContainer<ID3D11HullShader>::mInternal;
	device->CreateHullShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&internal_ref);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAHullShaderImp::~IGAHullShaderImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADomainShaderImp::IGADomainShaderImp(ID3D11Device * device,const String & hlsl)
{
	auto & code=IGAShaderImp::mInternal;
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
	auto & internal_ref=TD3DObjectContainer<ID3D11DomainShader>::mInternal;
	device->CreateDomainShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&internal_ref);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADomainShaderImp::~IGADomainShaderImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAComputeShaderImp::IGAComputeShaderImp(ID3D11Device * device,const String & hlsl)
{
	auto & code=IGAShaderImp::mInternal;
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
	auto & internal_ref=TD3DObjectContainer<ID3D11ComputeShader>::mInternal;
	device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&internal_ref);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAComputeShaderImp::~IGAComputeShaderImp()
{
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGAComputeShaderImp::apply(ID3D11DeviceContext * context,IGAProgramParameterImp * parameter)
{
	auto & internal_ref=TD3DObjectContainer<ID3D11ComputeShader>::mInternal;
	context->CSSetShader(internal_ref,nullptr,0);
	thread_local static TVector<VoidPtr> resources;
	resources.clear();
	resources.insert(resources.end(),parameter->getConstantBuffers()[0].begin(),parameter->getConstantBuffers()[0].end());
	context->CSSetConstantBuffers(0,static_cast<UInt32>(parameter->getConstantBuffers()[0].size()),resources.empty()?nullptr:reinterpret_cast<ID3D11Buffer*const*>(&resources[0]));
	resources.clear();
	resources.insert(resources.end(),parameter->getSamplers()[0].begin(),parameter->getSamplers()[0].end());
	context->CSSetSamplers(0,static_cast<UInt32>(parameter->getSamplers()[0].size()),resources.empty()?nullptr:reinterpret_cast<ID3D11SamplerState*const*>(&resources[0]));
}

IGAProgramReflectionImp* NSDevilX::NSCore::NSDirectX::NSVersion11::IGAComputeShaderImp::createReflection()
{
	return DEVILX_NEW IGAProgramReflectionImp(&TD3DObjectContainer<ID3DBlob>::mInternal.p,1);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGABlendStateImp::IGABlendStateImp(ID3D11Device * device,const D3D11_BLEND_DESC & desc)
{
	device->CreateBlendState(reinterpret_cast<const D3D11_BLEND_DESC *>(&desc),&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGABlendStateImp::IGABlendStateImp(ID3D11Device1 * device,const D3D11_BLEND_DESC1 & desc)
{
	ID3D11BlendState1 * state=nullptr;
	device->CreateBlendState1(&desc,&state);
	mInternal=state;
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGABlendStateImp::~IGABlendStateImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGARasterizerStateImp::IGARasterizerStateImp(ID3D11Device * device,const D3D11_RASTERIZER_DESC & desc)
{
	device->CreateRasterizerState(reinterpret_cast<const D3D11_RASTERIZER_DESC *>(&desc),&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGARasterizerStateImp::IGARasterizerStateImp(ID3D11Device1 * device,const D3D11_RASTERIZER_DESC1 & desc)
{
	ID3D11RasterizerState1 * state=nullptr;
	device->CreateRasterizerState1(reinterpret_cast<const D3D11_RASTERIZER_DESC1 *>(&desc),&state);
	mInternal=state;
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGARasterizerStateImp::IGARasterizerStateImp(ID3D11Device3 * device,const D3D11_RASTERIZER_DESC2 & desc)
{
	ID3D11RasterizerState2 * state=nullptr;
	device->CreateRasterizerState2(&desc,&state);
	mInternal=state;
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

NSDevilX::NSCore::NSDirectX::NSVersion11::IGASamplerStateImp::IGASamplerStateImp(ID3D11Device * device,const D3D11_SAMPLER_DESC & desc)
{
	device->CreateSamplerState(&desc,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGASamplerStateImp::~IGASamplerStateImp()
{}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramImp::IGAProgramImp()
{}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramImp::~IGAProgramImp()
{}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGARenderPipelineProgramImp::IGARenderPipelineProgramImp(IGAVertexShaderImp * vertexShader,IGAPixelShaderImp * pixelShader,IGAGeometryShaderImp * geometryShader,IGAHullShaderImp * hullShader,IGADomainShaderImp * domainShader)
{
	mShaders[IGAEnum::EShaderType_Vertex]=vertexShader;
	mShaders[IGAEnum::EShaderType_Pixel]=pixelShader;
	mShaders[IGAEnum::EShaderType_Geometry]=geometryShader;
	mShaders[IGAEnum::EShaderType_Hull]=hullShader;
	mShaders[IGAEnum::EShaderType_Domain]=domainShader;
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGARenderPipelineProgramImp::~IGARenderPipelineProgramImp()
{}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGARenderPipelineProgramImp::apply(ID3D11DeviceContext * context,IGAProgramParameterImp * parameter)
{
	thread_local static TVector<VoidPtr> resources;
	auto vertex_shader=static_cast<IGAVertexShaderImp*>(mShaders[IGAEnum::EShaderType_Vertex]);
	if(vertex_shader)
	{
		context->VSSetShader(vertex_shader->getInternal(),nullptr,0);
		resources.clear();
		resources.insert(resources.end(),parameter->getConstantBuffers()[IGAEnum::EShaderType_Vertex].begin(),parameter->getConstantBuffers()[IGAEnum::EShaderType_Vertex].end());
		context->VSSetConstantBuffers(0,static_cast<UInt32>(resources.size()),resources.empty()?nullptr:reinterpret_cast<ID3D11Buffer*const*>(&resources[0]));
		resources.clear();
		resources.insert(resources.end(),parameter->getSamplers()[IGAEnum::EShaderType_Vertex].begin(),parameter->getSamplers()[IGAEnum::EShaderType_Vertex].end());
		context->VSSetSamplers(0,static_cast<UInt32>(resources.size()),resources.empty()?nullptr:reinterpret_cast<ID3D11SamplerState*const*>(&resources[0]));
	}
	auto pixel_shader=static_cast<IGAPixelShaderImp*>(mShaders[IGAEnum::EShaderType_Pixel]);
	if(pixel_shader)
	{
		context->PSSetShader(pixel_shader->getInternal(),nullptr,0);
		resources.clear();
		resources.insert(resources.end(),parameter->getConstantBuffers()[IGAEnum::EShaderType_Pixel].begin(),parameter->getConstantBuffers()[IGAEnum::EShaderType_Pixel].end());
		context->PSSetConstantBuffers(0,static_cast<UInt32>(resources.size()),resources.empty()?nullptr:reinterpret_cast<ID3D11Buffer*const*>(&resources[0]));
		resources.clear();
		resources.insert(resources.end(),parameter->getSamplers()[IGAEnum::EShaderType_Pixel].begin(),parameter->getSamplers()[IGAEnum::EShaderType_Pixel].end());
		context->PSSetSamplers(0,static_cast<UInt32>(resources.size()),resources.empty()?nullptr:reinterpret_cast<ID3D11SamplerState*const*>(&resources[0]));
	}
	auto geometry_shader=static_cast<IGAGeometryShaderImp*>(mShaders[IGAEnum::EShaderType_Geometry]);
	if(geometry_shader)
	{
		context->GSSetShader(geometry_shader->getInternal(),nullptr,0);
		resources.clear();
		resources.insert(resources.end(),parameter->getConstantBuffers()[IGAEnum::EShaderType_Geometry].begin(),parameter->getConstantBuffers()[IGAEnum::EShaderType_Geometry].end());
		context->GSSetConstantBuffers(0,static_cast<UInt32>(resources.size()),resources.empty()?nullptr:reinterpret_cast<ID3D11Buffer*const*>(&resources[0]));
		resources.clear();
		resources.insert(resources.end(),parameter->getSamplers()[IGAEnum::EShaderType_Geometry].begin(),parameter->getSamplers()[IGAEnum::EShaderType_Geometry].end());
		context->GSSetSamplers(0,static_cast<UInt32>(resources.size()),resources.empty()?nullptr:reinterpret_cast<ID3D11SamplerState*const*>(&resources[0]));
	}
	auto hull_shader=static_cast<IGAHullShaderImp*>(mShaders[IGAEnum::EShaderType_Hull]);
	if(hull_shader)
	{
		context->HSSetShader(hull_shader->getInternal(),nullptr,0);
		resources.clear();
		resources.insert(resources.end(),parameter->getConstantBuffers()[IGAEnum::EShaderType_Hull].begin(),parameter->getConstantBuffers()[IGAEnum::EShaderType_Hull].end());
		context->HSSetConstantBuffers(0,static_cast<UInt32>(resources.size()),resources.empty()?nullptr:reinterpret_cast<ID3D11Buffer*const*>(&resources[0]));
		resources.clear();
		resources.insert(resources.end(),parameter->getSamplers()[IGAEnum::EShaderType_Hull].begin(),parameter->getSamplers()[IGAEnum::EShaderType_Hull].end());
		context->HSSetSamplers(0,static_cast<UInt32>(resources.size()),resources.empty()?nullptr:reinterpret_cast<ID3D11SamplerState*const*>(&resources[0]));
	}
	auto domain_shader=static_cast<IGADomainShaderImp*>(mShaders[IGAEnum::EShaderType_Domain]);
	if(domain_shader)
	{
		context->DSSetShader(domain_shader->getInternal(),nullptr,0);
		resources.clear();
		resources.insert(resources.end(),parameter->getConstantBuffers()[IGAEnum::EShaderType_Domain].begin(),parameter->getConstantBuffers()[IGAEnum::EShaderType_Domain].end());
		context->DSSetConstantBuffers(0,static_cast<UInt32>(resources.size()),resources.empty()?nullptr:reinterpret_cast<ID3D11Buffer*const*>(&resources[0]));
		resources.clear();
		resources.insert(resources.end(),parameter->getSamplers()[IGAEnum::EShaderType_Domain].begin(),parameter->getSamplers()[IGAEnum::EShaderType_Domain].end());
		context->DSSetSamplers(0,static_cast<UInt32>(resources.size()),resources.empty()?nullptr:reinterpret_cast<ID3D11SamplerState*const*>(&resources[0]));
	}
}

IGAProgramReflectionImp* NSDevilX::NSCore::NSDirectX::NSVersion11::IGARenderPipelineProgramImp::createReflection()
{
	std::array<ID3DBlob*,5> blobs={nullptr};
	for(SizeT i=0;i<mShaders.size();++i)
	{
		auto shader=mShaders[i];
		if(shader)
		{
			blobs[i]=shader->getInternal();
		}
	}
	return DEVILX_NEW IGAProgramReflectionImp(&blobs[0],5);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramParameterImp::IGAProgramParameterImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramParameterImp::~IGAProgramParameterImp()
{
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramParameterImp::setConstantBuffer(UInt32 slot,IGAConstantBuffer*buffer)
{
	UInt32 index=0;
	for(UInt32 i=4;i>=0;--i)
	{
		if(slot>IGAProgramReflectionImp::msConstantBufferSlotOffsets[i])
		{
			index=i;
			slot-=IGAProgramReflectionImp::msConstantBufferSlotOffsets[i];
			break;
		}
	}
	mConstantBuffers[index][slot]=static_cast<IGABufferImp*>(buffer);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramParameterImp::setSampler(UInt32 slot,IGASamplerState*sampler)
{
	UInt32 index=0;
	for(UInt32 i=4;i>=0;--i)
	{
		if(slot>IGAProgramReflectionImp::msSamplerSlotOffsets[i])
		{
			index=i;
			slot-=IGAProgramReflectionImp::msSamplerSlotOffsets[i];
			break;
		}
	}
	mSamplers[index][slot]=static_cast<IGASamplerStateImp*>(sampler);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramParameterImp::setResourceView(UInt32 slot,IGAShaderResourceView*view)
{
	UInt32 index=0;
	for(UInt32 i=4;i>=0;--i)
	{
		if(slot>IGAProgramReflectionImp::msShaderResourceSlotOffsets[i])
		{
			index=i;
			slot-=IGAProgramReflectionImp::msShaderResourceSlotOffsets[i];
			break;
		}
	}
}
