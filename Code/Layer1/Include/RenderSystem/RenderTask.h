#pragma once
#include "RenderCommandList.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CRenderTask
		{
		protected:
			CRenderCommandList * mCommandList;
			TResourcePtrVector(CRenderTask) mTasks;
		public:
			CRenderTask();
			virtual ~CRenderTask();
			Void setCommandList(CRenderCommandList * commandList)
			{
				mCommandList=mCommandList;
			}
			Void addChild(CRenderTask * task)
			{
				mTasks.push_back(task);
			}
			virtual Void prepare();
			virtual Void process();
		protected:
			virtual Void _prepare();
			virtual Void _process();
		};
		class CRenderTaskRoot
			:public CRenderTask
			,public TBaseObject<CRenderTaskRoot>
		{
		public:
			CRenderTaskRoot(){ }
			~CRenderTaskRoot(){ }
		};
	}
}
#include "RenderTaskMT.h"