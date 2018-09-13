#pragma once
#include "IRenderEnum.h"
#include "IRenderShader.h"
#include "IRenderProgramBufferLayout.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IProgram
		{
		protected:
			virtual ~IProgram(){ }
		public:
			virtual const String & getName()const=0;
			virtual Void setShader(IEnum::EShaderType type,IShader * shader)=0;
			virtual IShader * getShader(IEnum::EShaderType type)const=0;
			virtual IEnum::EProgramResourceType getResourceType(const String & name)const=0;
			virtual UInt32 getResourceLocation(const String & name)const=0;
			virtual IProgramBufferLayout * getBufferLayout(UInt32 resourceLocation)const=0;
		};
	}
}