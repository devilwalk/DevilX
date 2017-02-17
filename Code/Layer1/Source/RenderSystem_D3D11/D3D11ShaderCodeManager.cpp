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
					,public TBaseObject<ID3DIncludeImp_HLSL5>
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
					,public TBaseObject<ID3DIncludeImp_HLSL4_1>
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
	ID3DInclude * include=nullptr;
	CComPtr<ID3DBlob> error;
	switch(modeType)
	{
	case CEnum::EShaderModelType_4_1:
		include=DEVILX_NEW NSInternal::ID3DIncludeImp_HLSL4_1;
		target+="4_1";
		break;
	case CEnum::EShaderModelType_5:
		include=DEVILX_NEW NSInternal::ID3DIncludeImp_HLSL5;
		target+="5_0";
		break;
	}
	D3DCompile(&code[0],code.size(),nullptr,macros,include,entry.c_str(),target.c_str(),flag,0,&ret,&error);
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