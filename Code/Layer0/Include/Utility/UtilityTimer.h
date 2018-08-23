#pragma once
namespace NSDevilX
{
	class CTimer
		:public TBaseObject<CTimer>
	{
	protected:
		NSCore::ITimer * mInternal;
	public:
		static Void sleep(UInt32 milliseconds);
		CTimer();
		~CTimer();
		SizeT getInMillisecond();
	};
}