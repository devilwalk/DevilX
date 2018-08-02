#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class ISemaphore
		{
		protected:
			virtual ~ISemaphore(){}
		public:
			virtual Void notify()=0;
			virtual Void wait(UInt32 timeOut=-1)=0;
		};
	}
}