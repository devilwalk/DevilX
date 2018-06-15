#pragma once
#include "MemoryAllocatorObjectTemplate.h"
#include "ISemaphoreImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CFunctionWorker
			:public TBaseObject<CFunctionWorker>
		{
		public:
			typedef Void(*WorkFunction)(VoidPtr);
		protected:
			const WorkFunction mWorkFunction;
			const VoidPtr mParameter;
			ISemaphoreImp * const mSemaphore;
		public:
			CFunctionWorker(WorkFunction func=nullptr,VoidPtr parameter=nullptr,ISemaphoreImp * mSemaphore=nullptr)
				:mWorkFunction(func)
				,mParameter(parameter)
				,mSemaphore(mSemaphore)
			{}
			~CFunctionWorker()
			{
			}
			Void operator()()
			{
				assert(nullptr!=mWorkFunction);
				mWorkFunction(mParameter);
				if(getSemaphore())
				{
					getSemaphore()->notify();
				}
			}
			WorkFunction getWorkFunction()const
			{
				return mWorkFunction;
			}
			VoidPtr getParameter()const
			{
				return mParameter;
			}
			ISemaphoreImp * getSemaphore()const
			{
				return mSemaphore;
			}
		};
	}
}