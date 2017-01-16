#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;
ConstCharPtr CForwardVertexShaderGenerator::msDefines[EOutput_Count]=
{
	"OUTPUT_WORLD_POSITION",
	"OUTPUT_WORLD_NORMAL",
	"OUTPUT_WORLD_TANGENT",
	"OUTPUT_MAIN_UV",
	"OUTPUT_DIFFUSE"
};

NSDevilX::NSRenderSystem::NSD3D11::CForwardVertexShaderGenerator::CForwardVertexShaderGenerator()
	:mOutputs(0)
{}

NSDevilX::NSRenderSystem::NSD3D11::CForwardVertexShaderGenerator::~CForwardVertexShaderGenerator()
{}

ID3DBlob * NSDevilX::NSRenderSystem::NSD3D11::CForwardVertexShaderGenerator::generateCode() const
{
	String code_key="Forward_VertexShader_";
	for(auto i=0;i<EOutput_Count;++i)
	{
		code_key+=CStringConverter::toString(_hasOutput(*reinterpret_cast<EOutput*>(&i))?1:0);
	}
	ID3DBlob * ret=CSystemImp::getSingleton().getShaderCodeManager()->getCode(code_key);
	if(nullptr==ret)
	{
		TVector<D3D_SHADER_MACRO> macro_list=generateMacro();
		D3D_SHADER_MACRO null_macro={nullptr,nullptr};
		macro_list.push_back(null_macro);
		switch(CSystemImp::getSingleton().getShaderModelType())
		{
		case CEnum::EShaderModelType_4_1:
			ret=CSystemImp::getSingleton().getShaderCodeManager()->registerVertexShader(code_key,CSystemImp::getSingleton().getDefinitionShader4_1()->ForwardShader,CSystemImp::getSingleton().getShaderModelType(),&macro_list[0]);
			break;
		case CEnum::EShaderModelType_5:
			ret=CSystemImp::getSingleton().getShaderCodeManager()->registerVertexShader(code_key,CSystemImp::getSingleton().getDefinitionShader5()->ForwardShader,CSystemImp::getSingleton().getShaderModelType(),&macro_list[0]);
			break;
		}
	}
	return ret;
}

TVector<D3D_SHADER_MACRO> NSDevilX::NSRenderSystem::NSD3D11::CForwardVertexShaderGenerator::generateMacro() const
{
	TVector<D3D_SHADER_MACRO> macro_list;
	class CMacro
		:public D3D_SHADER_MACRO
	{
	public:
		CMacro()
		{
			Name=nullptr;
			Definition=nullptr;
		}
		Void set(decltype(Name) name)
		{
			Name=name;
			Definition="1";
		}
	};
	CMacro def;
	for(auto i=0;i<EOutput_Count;++i)
	{
		if(_hasOutput(*reinterpret_cast<EOutput*>(&i)))
		{
			def.set(msDefines[i]);
			macro_list.push_back(def);
		}
	}
	return macro_list;
}
