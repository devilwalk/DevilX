#pragma once
#include "CommonType.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CThread
		:public TBaseObject<CThread>
	{
	public:
		typedef Void (*ThreadFunction)(VoidPtr);
	protected:
		VoidPtr mHandle;
		ThreadFunction mFunction;
		VoidPtr mParameter;
	public:
		CThread(ThreadFunction func,VoidPtr parameter);
		~CThread();
		ThreadFunction getFunction()const
		{
			return mFunction;
		}
		VoidPtr getParameter()const
		{
			return mParameter;
		}
	};
}