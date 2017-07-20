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
	String real_code="#define DEVILX_HLSL_VERSION ";
	switch(modeType)
	{
	case CEnum::EShaderModelType_4_1:
		target+="4_1";
		real_code+="410";
		break;
	case CEnum::EShaderModelType_5:
		target+="5_0";
		real_code+="500";
		break;
	}
	real_code+="\r\n";
	if(macros)
	{
		while(macros->Definition&&macros->Name)
		{
			real_code+=String("#define ")+macros->Name+" "+macros->Definition+"\r\n";
			macros++;
		}
	}
	real_code+=code;
	CComPtr<ID3DBlob> error;
	D3DCompile(&real_code[0],real_code.size(),nullptr,nullptr,nullptr,entry.c_str(),target.c_str(),flag,0,&ret,&error);
	if(error.p)
	{
		OutputDebugStringA(static_cast<LPCSTR>(error->GetBufferPointer()));
		OutputDebugStringA("\r\n");
		auto handle=CreateFileA((key+".hlsl").c_str(),GENERIC_WRITE,FILE_SHARE_READ,nullptr,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
		DWORD write_size=static_cast<DWORD>(real_code.size());
		WriteFile(handle,&real_code[0],write_size,&write_size,nullptr);
		CloseHandle(handle);
	}
	if(ret)
	{
		mCodes.add(key,ret);
	}
	return ret;
}