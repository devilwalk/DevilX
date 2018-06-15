#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class ISemaphoreImp
			:public ISemaphore
			,public TBaseObject<ISemaphoreImp>
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

			// Í¨¹ý ISemaphore ¼Ì³Ð
			virtual void notify() override;
			virtual void wait(unsigned int timeOut) override;
		};
	}
}