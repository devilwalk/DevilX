#include "Precompiler.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			namespace NSInternal
			{
				class ID3DIncludeImp_HLSL5
					:public ID3DInclude
				{
					// Inherited via ID3DInclude
					virtual HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType,LPCSTR pFileName,LPCVOID pParentData,LPCVOID * ppData,UINT * pBytes) override
					{
						if(0==strcmp(pFileName,"ConstantBuffer.hlsl"))
						{
							*ppData=&CSystemImp::getSingleton().getDefinitionShader5()->ConstantBuffer[0];
							*pBytes=static_cast<UINT>(CSystemImp::getSingleton().getDefinitionShader5()->ConstantBuffer.size());
						}
						else if(0==strcmp(pFileName,"Function.hlsl"))
						{
							*ppData=&CSystemImp::getSingleton().getDefinitionShader5()->Function[0];
							*pBytes=static_cast<UINT>(CSystemImp::getSingleton().getDefinitionShader5()->Function.size());
						}
						return S_OK;
					}
					virtual HRESULT __stdcall Close(LPCVOID pData) override
					{
						return S_OK;
					}
				};
				class ID3DIncludeImp_HLSL4_1
					:public ID3DInclude
				{
					// Inherited via ID3DInclude
					virtual HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType,LPCSTR pFileName,LPCVOID pParentData,LPCVOID * ppData,UINT * pBytes) override
					{
						if(0==strcmp(pFileName,"ConstantBuffer.hlsl"))
						{
							*ppData=&CSystemImp::getSingleton().getDefinitionShader4_1()->ConstantBuffer[0];
							*pBytes=static_cast<UINT>(CSystemImp::getSingleton().getDefinitionShader4_1()->ConstantBuffer.size());
						}
						else if(0==strcmp(pFileName,"Function.hlsl"))
						{
							*ppData=&CSystemImp::getSingleton().getDefinitionShader4_1()->Function[0];
							*pBytes=static_cast<UINT>(CSystemImp::getSingleton().getDefinitionShader4_1()->Function.size());
						}
						return S_OK;
					}
					virtual HRESULT __stdcall Close(LPCVOID pData) override
					{
						return S_OK;
					}
				};
			}
		}
	}
}
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

ID3DBlob * NSDevilX::NSRenderSystem::NSD3D11::CShaderCodeManager::registerVertexShader(const String & key,const String & code,CEnum::EShaderModelType smType,const D3D_SHADER_MACRO * macros)
{
	ID3DBlob * ret=nullptr;
	UINT flag=0;
#ifdef DEVILX_DEBUG
	flag=D3DCOMPILE_DEBUG|D3DCOMPILE_SKIP_OPTIMIZATION|D3DCOMPILE_WARNINGS_ARE_ERRORS;
#else
	flag=D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif
	CComPtr<ID3DBlob> error;
	switch(smType)
	{
	case CEnum::EShaderModelType_4_1:
	{
		NSInternal::ID3DIncludeImp_HLSL4_1 include;
		D3DCompile(&code[0],code.size(),nullptr,macros,&include,"vsMain","vs_4_1",flag,0,&ret,&error);
	}
	break;
	case CEnum::EShaderModelType_5:
	{
		NSInternal::ID3DIncludeImp_HLSL5 include;
		D3DCompile(&code[0],code.size(),nullptr,macros,&include,"vsMain","vs_5_0",flag,0,&ret,&error);
	}
	break;
	}
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

ID3DBlob * NSDevilX::NSRenderSystem::NSD3D11::CShaderCodeManager::registerPixelShader(const String & key,const String & code,CEnum::EShaderModelType smType,const D3D_SHADER_MACRO * macros)
{
	ID3DBlob * ret=nullptr;
	UINT flag=0;
#ifdef DEVILX_DEBUG
	flag=D3DCOMPILE_DEBUG|D3DCOMPILE_SKIP_OPTIMIZATION|D3DCOMPILE_WARNINGS_ARE_ERRORS;
#else
	flag=D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif
	CComPtr<ID3DBlob> error;
	switch(smType)
	{
	case CEnum::EShaderModelType_4_1:
	{
		NSInternal::ID3DIncludeImp_HLSL4_1 include;
		D3DCompile(&code[0],code.size(),nullptr,macros,&include,"psMain","ps_4_1",flag,0,&ret,&error);
	}
	break;
	case CEnum::EShaderModelType_5:
	{
		NSInternal::ID3DIncludeImp_HLSL5 include;
		D3DCompile(&code[0],code.size(),nullptr,macros,&include,"psMain","ps_5_0",flag,0,&ret,&error);
	}
	break;
	}
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
