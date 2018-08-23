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

			// ͨ�� ITimer �̳�
			virtual DoubleFloat getDeltaInSecond() override;
		};
	}
}