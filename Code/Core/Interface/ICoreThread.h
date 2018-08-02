#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IThread
		{
		public:
			typedef Void(*WorkFunction)(VoidPtr);
		protected:
			virtual ~IThread(){}
		public:
			virtual void startup(WorkFunction function,VoidPtr parameters)=0;
			virtual void finish()=0;
		};
	}
}