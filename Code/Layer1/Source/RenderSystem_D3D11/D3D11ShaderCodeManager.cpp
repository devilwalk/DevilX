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

ID3DBlob * NSDevilX::NSRenderSystem::NSD3D11::CShaderCodeManager::registerShader(const String & key,const String & code,IEnum::EShaderType type,IEnum::EShaderCodeType codeType,const D3D_SHADER_MACRO * macros)
{
	ID3DBlob * ret=nullptr;
	UINT flag=0;
#if DEVILX_DEBUG
	flag=D3DCOMPILE_DEBUG|D3DCOMPILE_SKIP_OPTIMIZATION|D3DCOMPILE_WARNINGS_ARE_ERRORS;
#else
	flag=D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif
	String target;
	switch(type)
	{
	case IEnum::EShaderType_VS:target="vs_";break;
	case IEnum::EShaderType_PS:target="ps_";break;
	case IEnum::EShaderType_CS:target="cs_";break;
	case IEnum::EShaderType_GS:target="gs_";break;
	}
	String real_code="#define DEVILX_HLSL_VERSION ";
	switch(codeType)
	{
	case IEnum::EShaderCodeType_HLSL_4_0:
		target+="4_1";
		real_code+="410";
		break;
	case IEnum::EShaderCodeType_HLSL_5_0:
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
	D3DCompile(&real_code[0],real_code.size(),nullptr,nullptr,nullptr,"main",target.c_str(),flag,0,&ret,&error);
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