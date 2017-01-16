#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;
ConstCharPtr CForwardPixelShaderCodeGenerator::msDefines[EFlag_Count]=
{
	"USE_LIGHTING",
	"USE_DIRECTION_LIGHT",
	"USE_POINT_LIGHT",
	"USE_SPOT_LIGHT",
	"USE_DIFFUSE_TEXTURE",
	"USE_NORMAL_TEXTURE",
	"USE_ALPHA_TEST",
	"USE_SPECULAR"
};

NSDevilX::NSRenderSystem::NSGL4::CForwardPixelShaderCodeGenerator::CForwardPixelShaderCodeGenerator()
	:mFlags(0)
{}
  
NSDevilX::NSRenderSystem::NSGL4::CForwardPixelShaderCodeGenerator::~CForwardPixelShaderCodeGenerator()
{}

GLuint NSDevilX::NSRenderSystem::NSGL4::CForwardPixelShaderCodeGenerator::generate(const TVector<std::pair<String,String> > * extensionMacros) const
{
	String code_key="Forward_PixelShader_";
	for(auto i=0;i<EFlag_Count;++i)
	{
		code_key+=CStringConverter::toString(_hasFlag(*reinterpret_cast<EFlag*>(&i))?1:0);
	}
	auto ret=CSystemImp::getSingleton().getShaderManager()->getShader(code_key);
	if(0==ret)
	{
		TVector<std::pair<String,String> > macro_list;
		if(extensionMacros)
			macro_list=*extensionMacros;
		class CMacro
			:public std::pair<String,String>
		{
		public:
			CMacro()
			{
			}
			Void set(const String & name)
			{
				this->first=name;
				this->second="1";
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
		ret=CSystemImp::getSingleton().getShaderManager()->registerPixelShader(code_key,CSystemImp::getSingleton().getDefinitionShader()->ForwardShaderPixel,macro_list);
	}
	return ret;
}
