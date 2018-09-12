#pragma once
#include "IRenderProgram.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IPipelineState
		{
		protected:
			virtual ~IPipelineState(){ }
		public:
			virtual Void addProgram(IProgram * program)=0;
			virtual Void removeProgram(IProgram * program)=0;
		};
	}
}