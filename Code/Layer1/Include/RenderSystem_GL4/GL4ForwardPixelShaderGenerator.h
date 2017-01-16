#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CForwardPixelShaderCodeGenerator
				:public TBaseObject<CForwardPixelShaderCodeGenerator>
			{
			public:
				enum EFlag
				{
					EFlag_UseLighting,
					EFlag_UseDirectionLight,
					EFlag_UsePointLight,
					EFlag_UseSpotLight,
					EFlag_UseDiffuseTexture,
					EFlag_UseNormalTexture,
					EFlag_UseAlphaTest,
					EFlag_UseSpecular,
					EFlag_Count
				};
				static ConstCharPtr msDefines[EFlag_Count];
			protected:
				Int32 mFlags;
			public:
				CForwardPixelShaderCodeGenerator();
				~CForwardPixelShaderCodeGenerator();
				Void addFlag(EFlag flag)
				{
					mFlags|=1<<flag;
				}
				GLuint generate(const TVector<std::pair<String,String> > * extensionMacros=nullptr)const;
			protected:
				Boolean _hasFlag(EFlag flag)const
				{
					return 0!=(mFlags&(1<<flag));
				}
			};
		}
	}
}