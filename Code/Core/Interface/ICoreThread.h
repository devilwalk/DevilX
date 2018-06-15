#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IThread
		{
		public:
			typedef void(*WorkFunction)(void*);
		protected:
			virtual ~IThread(){}
		public:
			virtual void startup(WorkFunction function,void*parameters)=0;
			virtual void finish()=0;
		};
	}
}