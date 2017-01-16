#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CForwardVertexShaderGenerator
				:public TBaseObject<CForwardVertexShaderGenerator>
			{
			public:
				enum EOutput
				{
					EOutput_WorldPosition,
					EOutput_WorldNormal,
					EOutput_WorldTangent,
					EOutput_MainUV,
					EOutput_Diffuse,
					EOutput_Count
				};
				static ConstCharPtr msDefines[EOutput_Count];
			protected:
				Int32 mOutputs;
			public:
				CForwardVertexShaderGenerator();
				~CForwardVertexShaderGenerator();
				Void addOutput(EOutput output)
				{
					mOutputs|=1<<output;
				}
				GLuint generate()const;
				TVector<std::pair<String,String> > generateMacro()const;
			protected:
				Boolean _hasOutput(EOutput output)const
				{
					return 0!=(mOutputs&(1<<output));
				}
			};
		}
	}
}