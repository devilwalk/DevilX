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
					CComPtr<ID3D11ShaderReflection> mReflection;
				public:
					IGAShaderReflectionImp(ID3DBlob * blob);
					~IGAShaderReflectionImp();

					// Í¨¹ý IGAShaderReflection ¼Ì³Ð
					virtual IGAStruct::SShaderDesc getDesc() override;
					virtual IGAStruct::SShaderSignatureParameterDesc getInputParameterDesc(UInt32 parameterIndex) override;
					virtual IGAStruct::SShaderBufferDesc getBufferDesc(UInt32 index) override;
					virtual IGAStruct::SShaderVariableDesc getVariableDesc(UInt32 bufferIndex,UInt32 variableIndex) override;
				};
			}
		}
	}
}