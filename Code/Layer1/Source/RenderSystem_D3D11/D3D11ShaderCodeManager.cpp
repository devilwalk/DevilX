#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CShaderCodeManager::CShaderCodeManager()
{}

NSDevilX::NSRenderSystem::NSD3D11::CShaderCodeManager::~CShaderCodeManager()
{
	for(auto const & code_pair:mCodes)
		code_pair.second->Release();
}

ID3DBlob * NSDevilX::NSRenderSystem::NSD3D11::CShaderCodeManager::registerShader(const String & key,const String & code,CEnum::EShaderType type,CEnum::EShaderModelType modeType,const D3D_SHADER_MACRO * macros)
{
	ID3DBlob * ret=nullptr;
	UINT flag=0;
#ifdef DEVILX_DEBUG
	flag=D3DCOMPILE_DEBUG|D3DCOMPILE_SKIP_OPTIMIZATION|D3DCOMPILE_WARNINGS_ARE_ERRORS;
#else
	flag=D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif
	String entry;
	String target;
	switch(type)
	{
	case CEnum::EShaderType_VertexShader:entry="vsMain";target="vs_";break;
	case CEnum::EShaderType_HullShader:entry="hsMain";target="hs_";break;
	case CEnum::EShaderType_DomainShader:entry="dsMain";target="ds_";break;
	case CEnum::EShaderType_PixelShader:entry="psMain";target="ps_";break;
	case CEnum::EShaderType_ComputeShader:entry="csMain";target="cs_";break;
	}
	CComPtr<ID3DBlob> error;
	switch(modeType)
	{
	case CEnum::EShaderModelType_4_1:
		target+="4_1";
		break;
	case CEnum::EShaderModelType_5:
		target+="5_0";
		break;
	}
	D3DCompile(&code[0],code.size(),nullptr,macros,nullptr,entry.c_str(),target.c_str(),flag,0,&ret,&error);
	if(error.p)
	{
		OutputDebugStringA(static_cast<LPCSTR>(error->GetBufferPointer()));
		OutputDebugStringA("\r\n");
	}
	if(ret)
	{
		mCodes.add(key,ret);
	}
	return ret;
}