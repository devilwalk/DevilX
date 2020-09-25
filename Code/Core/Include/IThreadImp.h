#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IThreadImp
			:public TMemoryAllocatorObject<IThreadImp>
			,public IThread
		{
		public:
			struct SContext
				:public TMemoryAllocatorObject<SContext>
			{
				IThreadImp * const mThread;
				VoidPtr const mParameters;
				SContext(IThreadImp * thread,VoidPtr parameters)
					:mThread(thread)
					,mParameters(parameters)
				{

				}
			};
		protected:
			std::thread * mThread;
		public:
			IThreadImp();
			~IThreadImp();

			// Í¨¹ý IThread ¼Ì³Ð
			virtual Void startup(WorkFunction function,VoidPtr parameters) override;
			virtual Void finish() override;
		};
	}
}