#pragma once
#include "IRenderEnum.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IShader
		{
		protected:
			virtual ~IShader()
			{}
		public:
			virtual const String & getName()const=0;
			virtual Boolean compile(IEnum::EShaderType type,IEnum::EShaderCodeType codeType,const String & code)=0;
			virtual IEnum::EShaderType getType()const=0;
			virtual IEnum::EShaderCodeType getCodeType()const=0;
		};
	}
}