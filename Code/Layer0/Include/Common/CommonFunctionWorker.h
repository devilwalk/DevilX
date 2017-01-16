#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonSemaphore.h"
namespace NSDevilX
{
	template<typename TReturn>
	class TFunctionWorker
		:public TBaseObject<TFunctionWorker<TReturn> >
	{
	public:
		typedef TReturn(*WorkFunction)(VoidPtr);
	protected:
		const WorkFunction mWorkFunction;
		const VoidPtr mParameter;
		CSemaphore * const mSemaphore;
	public:
		TFunctionWorker(WorkFunction func=nullptr,VoidPtr parameter=nullptr,CSemaphore * mSemaphore=nullptr)
			:mWorkFunction(func)
			,mParameter(parameter)
			,mSemaphore(mSemaphore)
		{}
		virtual ~TFunctionWorker()
		{
		}
		TReturn operator()()
		{
			assert(nullptr!=mWorkFunction);
			TReturn ret=mWorkFunction(mParameter);
			if(ret&&getSemaphore())
			{
				getSemaphore()->notify();
			}
			return ret;
		}
		WorkFunction getWorkFunction()const
		{
			return mWorkFunction;
		}
		VoidPtr getParameter()const
		{
			return mParameter;
		}
		CSemaphore * getSemaphore()const
		{
			return mSemaphore;
		}
	};
	template<>
	class TFunctionWorker<Void>
		:public TBaseObject<TFunctionWorker<Void> >
	{
	public:
		typedef Void(*WorkFunction)(VoidPtr);
	protected:
		WorkFunction mWorkFunction;
		VoidPtr mParameter;
	public:
		TFunctionWorker(WorkFunction func=nullptr,VoidPtr parameter=nullptr)
			:mWorkFunction(func)
			,mParameter(parameter)
		{}
		virtual ~TFunctionWorker()
		{}
		Void operator()()
		{
			assert(nullptr!=mWorkFunction);
			mWorkFunction(mParameter);
		}
		Void set(WorkFunction func,VoidPtr parameter)
		{
			mWorkFunction=func;
			mParameter=parameter;
		}
		WorkFunction getWorkFunction()const
		{
			return mWorkFunction;
		}
		VoidPtr getParameter()const
		{
			return mParameter;
		}
	};
}