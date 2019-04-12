#pragma once
#include "ICoreGAStruct.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGAShaderReflection
		{
		protected:
			virtual ~IGAShaderReflection(){ }
		public:
			virtual IGAStruct::SShaderDesc getDesc()=0;
			virtual IGAStruct::SShaderSignatureParameterDesc getInputParameterDesc(UInt32 parameterIndex)=0;
			virtual IGAStruct::SShaderBufferDesc getBufferDesc(UInt32 index)=0;
			virtual IGAStruct::SShaderVariableDesc getVariableDesc(UInt32 bufferIndex,UInt32 variableIndex)=0;
		};
	}
}