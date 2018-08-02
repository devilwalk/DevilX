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
			virtual Void lockRead()=0;
			virtual Void lockWrite()=0;
			virtual Boolean tryLockRead()=0;
			virtual Boolean tryLockWrite()=0;
			virtual Void unLockRead()=0;
			virtual Void unLockWrite()=0;
		};
	}
}