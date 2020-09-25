#pragma once
namespace NSDevilX
{
	class CTimer
		:public TMemoryAllocatorObject<CTimer>
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