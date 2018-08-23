#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class ITimerImp
			:public TBaseObject<ITimerImp>
			,public ITimer
		{
		protected:
			tbb::tick_count mInit;
		public:
			ITimerImp();
			~ITimerImp();

			// Í¨¹ý ITimer ¼Ì³Ð
			virtual DoubleFloat getDeltaInSecond() override;
		};
	}
}