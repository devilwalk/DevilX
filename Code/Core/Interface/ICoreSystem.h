#pragma once
#include "ICoreMemoryManager.h"
#include "ICoreThreadManager.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI ISystem
		{
		protected:
			~ISystem(){}
		public:
			void shutdown();
			IThreadManager*getThreadManager()const;
			IMemoryManager*getMemoryManager()const;
			double getTimeNowInSeconds()const;
		};
		DLLAPI ISystem*getSystem();
	}
}