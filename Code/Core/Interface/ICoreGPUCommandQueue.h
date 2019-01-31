#pragma once
#include "ICoreGPUCommandList.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGPUCommandQueue
		{
		protected:
			virtual ~IGPUCommandQueue(){ }
		public:
			virtual Void executeCommandLists(UInt32 numCommandLists,)
		};
	}
}