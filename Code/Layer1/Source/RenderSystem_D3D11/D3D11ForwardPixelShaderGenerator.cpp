#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;
ConstCharPtr CForwardPixelShaderCodeGenerator::msDefines[EFlag_Count]=
{
	"USE_DIRECTION_LIGHT",
	"USE_POINT_LIGHT",
	"USE_SPOT_LIGHT",
	"USE_CONSTANT_AMBIENT_MODEL",
	"USE_HEMISPHERE_AMBIENT_MODEL",
	"USE_SPHERICALHARMONICS_AMBIENT_MODEL",
	"USE_LAMBERT_DIFFUSE_MODEL",
	"USE_OREN_NAYAR_DIFFUSE_MODEL",
	"USE_MINNAERT_DIFFUSE_MODEL",
	"USE_DISNEY_DIFFUSE_MODEL",
	"USE_PHONG_SPECULAR_MODEL",
	"USE_BLINNPHONG_SPECULAR_MODEL",
	"USE_UE4_SPECULAR_MODEL",
	"USE_COOK_TORRANCE_SPECULAR_MODEL",
	"USE_DIFFUSE_TEXTURE",
	"USE_NORMAL_TEXTURE",
	"USE_SPECULAR_TEXTURE",
	"USE_ALPHA_TEST"
};

NSDevilX::NSRenderSystem::NSD3D11::CForwardPixelShaderCodeGenerator::CForwardPixelShaderCodeGenerator()
	:mFlags(0)
{}

NSDevilX::NSRenderSystem::NSD3D11::CForwardPixelShaderCodeGenerator::~CForwardPixelShaderCodeGenerator()
{}

ID3DBlob * NSDevilX::NSRenderSystem::NSD3D11::CForwardPixelShaderCodeGenerator::generateCode(const TVector(D3D_SHADER_MACRO) * extensionMacros) const
{
	String code_key="Forward_PixelShader_";
	for(auto i=0;i<EFlag_Count;++i)
	{
		code_key+=toString(_hasFlag(*reinterpret_cast<EFlag*>(&i))?1:0);
	}
	ID3DBlob * ret=CSystemImp::getSingleton().getShaderCodeManager()->getCode(code_key);
	if(nullptr==ret)
	{
		TVector(D3D_SHADER_MACRO) macro_list;
		if(extensionMacros)
			macro_list=*extensionMacros;
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
		for(auto i=0;i<EFlag_Count;++i)
		{
			if(_hasFlag(*reinterpret_cast<EFlag*>(&i)))
			{
				def.set(msDefines[i]);
				macro_list.push_back(def);
			}
		}
		macro_list.push_back(CMacro());
		ret=CSystemImp::getSingleton().getShaderCodeManager()->registerShader(code_key,ISystemImp::getSingleton().getDefinitionShader()->ForwardShader_hlsl,CEnum::EShaderType_PixelShader,CSystemImp::getSingleton().getShaderModelType(),&macro_list[0]);
	}
	return ret;
}
