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
			virtual void notify()=0;
			virtual void wait(unsigned int timeOut=-1)=0;
		};
	}
}