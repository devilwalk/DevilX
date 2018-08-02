#pragma once
#include "ICoreMemoryManager.h"
#include "ICoreThreadManager.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class ISystem
		{
		protected:
			~ISystem(){}
		public:
			void shutdown();
			IThreadManager*getThreadManager()const;
			IMemoryManager*getMemoryManager()const;
			DoubleFloat getTimeNowInSeconds()const;
		};
		DLLAPI ISystem*getSystem();
	}
}