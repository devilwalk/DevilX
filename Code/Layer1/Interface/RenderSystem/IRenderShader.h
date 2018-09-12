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
			virtual IEnum::EShaderType getType()const=0;
			virtual IEnum::EShaderCodeType getCodeType()const=0;
		};
	}
}