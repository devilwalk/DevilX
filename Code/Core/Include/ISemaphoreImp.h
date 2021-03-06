#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class ISemaphoreImp
			:public ISemaphore
			,public TMemoryAllocatorObject<ISemaphoreImp>
		{
		protected:
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
			HANDLE mInternal;
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
		public:
			ISemaphoreImp();
			~ISemaphoreImp();

			// ͨ�� ISemaphore �̳�
			virtual void notify() override;
			virtual void wait(UInt32 timeOut) override;
		};
	}
}