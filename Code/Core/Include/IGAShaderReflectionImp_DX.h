#pragma once
#include "IGAResourceImp_DX11.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			namespace NSVersion11
			{
				class IGAShaderReflectionImp
					:public IGAShaderReflection
					,public TBaseObject<IGAShaderReflectionImp>
				{
				protected:
					TCOMResourcePtrVector(ID3D11ShaderReflection) mReflections;
				public:
					IGAShaderReflectionImp(const TVector(ID3DBlob*) & shaders);
					~IGAShaderReflectionImp();
				};
			}
		}
	}
}