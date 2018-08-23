#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class ITimer
		{
		protected:
			virtual ~ITimer(){ }
		public:
			virtual DoubleFloat getDeltaInSecond()=0;
		};
	}
}