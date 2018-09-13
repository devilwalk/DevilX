#pragma once
#include "IRenderBuffer.h"
#include "IRenderPipelineState.h"
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
			virtual Void setPipelineState(IPipelineState * state)=0;
			virtual IPipelineState * getPipelineState()const=0;
			virtual Void setProgramResource(IProgram * program,IEnum::EProgramResourceType resourceType,UInt32 resourceIndex,IBuffer * buffer)=0;
			virtual Void setProgramResource(IProgram * program,UInt32 resourceIndex,ITexture * texture)=0;
			virtual Void setProgramResource(IProgram * program,UInt32 resourceIndex,ISamplerState * state)=0;
		};
	}
}