#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
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
				ID3DBlob * generateCode()const;
				TVector<D3D_SHADER_MACRO> generateMacro()const;
			protected:
				Boolean _hasOutput(EOutput output)const
				{
					return 0!=(mOutputs&(1<<output));
				}
			};
		}
	}
}