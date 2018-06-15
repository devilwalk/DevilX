#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IThreadPool
		{
		public:
			typedef void(*WorkFunction)(void*);
		protected:
			virtual ~IThreadPool(){}
		public:
			virtual void setMaxThreadCount(unsigned int count)=0;
			virtual unsigned int getMaxThreadCount()const=0;
			virtual void submit(WorkFunction func,void*parameter,int syncGroupID=-1)=0;
			virtual void doNextWork(bool wait=false)=0;
			virtual void wait(int syncGroupID)=0;
		};
	}
}