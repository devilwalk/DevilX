#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IThreadPool
		{
		public:
			typedef Void(*WorkFunction)(VoidPtr);
		protected:
			virtual ~IThreadPool(){}
		public:
			virtual Void setMaxThreadCount(UInt32 count)=0;
			virtual UInt32 getMaxThreadCount()const=0;
			virtual Void submit(WorkFunction func,VoidPtr parameter,Int32 syncGroupID=-1)=0;
			virtual Void doNextWork(Boolean wait=false)=0;
			virtual Void wait(Int32 syncGroupID)=0;
		};
	}
}