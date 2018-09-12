#pragma once
#include "IRenderEnum.h"
#include "IRenderShader.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IProgram
		{
		protected:
			virtual ~IProgram(){ }
		public:
			virtual Void setShader(IEnum::EShaderType type,IShader * shader)=0;
			virtual IShader * getShader(IEnum::EShaderType type)const=0;
			virtual IEnum::EProgramResourceType getResourceType(const String & name)const=0;
			virtual SizeT getResourceIndex(const String & name)const=0;
		};
	}
}