#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IEnum
		{
		public:
			enum EShaderType
			{
				EShaderType_VS_HLSL_6_0,
				EShaderType_PS_HLSL_6_0,
				EShaderType_VS_HLSL_5_0,
				EShaderType_PS_HLSL_5_0,
				EShaderType_VS_GLSL_4_5,
				EShaderType_PS_GLSL_4_5,
			};
			enum EShaderRegisterType
			{
				EShaderRegisterType_Unknown,
				EShaderRegisterType_ConstantBuffer,
				EShaderRegisterType_TextureBuffer,
				EShaderRegisterType_Texture,
				EShaderRegisterType_Sampler
			};
		};
	}
}