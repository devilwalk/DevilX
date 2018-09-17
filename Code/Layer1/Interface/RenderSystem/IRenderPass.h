#pragma once
#include "IRenderBuffer.h"
#include "IRenderTexture.h"
#include "IRenderProgram.h"
#include "IRenderSamplerState.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITechnique;
		class IPass
		{
		protected:
			virtual ~IPass(){ }
		public:
			virtual ITechnique * getTechnique()const=0;
			virtual Void setProgram(IProgram * program)=0;
			virtual IProgram * getProgram()const=0;
			virtual Void setProgramResource(UInt32 resourceLocation,IBuffer * buffer)=0;
			virtual Void setProgramResource(UInt32 resourceLocation,ITexture * texture)=0;
			virtual Void setProgramResource(UInt32 resourceLocation,ISamplerState * state)=0;
		};
	}
}