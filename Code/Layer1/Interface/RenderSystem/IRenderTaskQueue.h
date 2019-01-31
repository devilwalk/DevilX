#pragma once
#include "IRenderTask.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderTaskQueueListener
		{
		public:
			enum ETaskProcessFlag
			{
				ETaskProcessFlag_Skip = 1,
				ETaskProcessFlag_SkipChildren = 1<<1,
			};
		protected:
			virtual ~IRenderTaskQueueListener(){ }
		public:
			virtual Void onTaskPrepare(IRenderTask * task,OUT UInt32 & processValue)=0;
			virtual Void onTaskExecute(IRenderTask * task,OUT UInt32 & processValue)=0;
		};
		class IRenderTaskQueue
		{
		protected:
			virtual ~IRenderTaskQueue(){ }
		public:
			virtual IRenderTask * getRootTask()const=0;
			virtual Void setListener(IRenderTaskQueueListener * listener)=0;
			virtual IRenderTaskQueueListener * getListener()const=0;
		};
	}
}