#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IReadWriteLock
		{
		protected:
			virtual ~IReadWriteLock(){}
		public:
			virtual void lockRead()=0;
			virtual void lockWrite()=0;
			virtual bool tryLockRead()=0;
			virtual bool tryLockWrite()=0;
			virtual void unLockRead()=0;
			virtual void unLockWrite()=0;
		};
	}
}