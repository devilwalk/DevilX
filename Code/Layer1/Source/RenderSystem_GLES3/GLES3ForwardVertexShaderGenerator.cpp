#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;
ConstCharPtr CForwardVertexShaderGenerator::msDefines[EOutput_Count]=
{
	"OUTPUT_WORLD_POSITION",
	"OUTPUT_WORLD_NORMAL",
	"OUTPUT_WORLD_TANGENT",
	"OUTPUT_MAIN_UV",
	"OUTPUT_DIFFUSE"
};

NSDevilX::NSRenderSystem::NSGLES3::CForwardVertexShaderGenerator::CForwardVertexShaderGenerator()
	:mOutputs(0)
{}

NSDevilX::NSRenderSystem::NSGLES3::CForwardVertexShaderGenerator::~CForwardVertexShaderGenerator()
{}

GLuint NSDevilX::NSRenderSystem::NSGLES3::CForwardVertexShaderGenerator::generate() const
{
	String code_key="Forward_VertexShader_";
	for(auto i=0;i<EOutput_Count;++i)
	{
		code_key+=CStringConverter::toString(_hasOutput(*reinterpret_cast<EOutput*>(&i))?1:0);
	}
	auto ret=CSystemImp::getSingleton().getShaderManager()->getShader(code_key);
	if(0==ret)
	{
		ret=CSystemImp::getSingleton().getShaderManager()->registerVertexShader(code_key,CSystemImp::getSingleton().getDefinitionShader()->ForwardShaderVertex,generateMacro());
	}
	return ret;
}

TVector<std::pair<String,String> > NSDevilX::NSRenderSystem::NSGLES3::CForwardVertexShaderGenerator::generateMacro() const
{
	TVector<std::pair<String,String> > macro_list;
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
