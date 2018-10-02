#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSInternal
		{
			static Void threadFunction(VoidPtr parameter)
			{
				auto task=static_cast<CRenderTaskMT*>(parameter);
				task->prepare();
			}
		}
	}
}

NSDevilX::NSRenderSystem::CRenderTaskMT::CRenderTaskMT()
	:mThreadSyncGroupID(-1)
{
	mThreadSyncGroupID=ISystemImp::getSingleton().getRenderTaskThreadPool()->nextSyncGroupID();
}

NSDevilX::NSRenderSystem::CRenderTaskMT::~CRenderTaskMT()
{
}

Void NSDevilX::NSRenderSystem::CRenderTaskMT::submit()
{
	if(_needSubmit())
		ISystemImp::getSingleton().getRenderTaskThreadPool()->submitMT(NSInternal::threadFunction,this,mThreadSyncGroupID);
}

Void NSDevilX::NSRenderSystem::CRenderTaskMT::process()
{
	ISystemImp::getSingleton().getRenderTaskThreadPool()->waitMT(mThreadSyncGroupID);
	_process();
	for(auto task:mTasks)
	{
		if(task)
			task->process();
	}
}

Boolean NSDevilX::NSRenderSystem::CRenderTaskMT::_needSubmit() const
{
	return true;
}

NSDevilX::NSRenderSystem::CClearTask::CClearTask()
	:mRenderTarget(nullptr)
{
}

NSDevilX::NSRenderSystem::CClearTask::~CClearTask()
{
}

Void NSDevilX::NSRenderSystem::CClearTask::_prepare()
{
	mCommandList->clearRenderTarget(mRenderTarget);
}

NSDevilX::NSRenderSystem::CRenderSceneTask::CRenderSceneTask()
	:mViewport(nullptr)
{
}

NSDevilX::NSRenderSystem::CRenderSceneTask::~CRenderSceneTask()
{
}

Void NSDevilX::NSRenderSystem::CRenderSceneTask::_prepare()
{
	TVector(CVisibleArea*) visibles;
	mViewport->getCamera()->getScene()->getSceneManager()->findVisibleObjects(mViewport->getCamera()->getPlaneBoundedVolume(),visibles);
	CRenderOperation op;
	for(UInt8 render_queue_id=0;render_queue_id<255;++render_queue_id)
	{
		for(auto area:visibles)
		{
			for(auto obj:area->getAttachedObjects())
			{
				for(auto renderable:obj->getRenderables())
				{
					if(renderable->getRenderQueueID()==render_queue_id)
					{
						if(renderable->createRenderOperation(op))
						{
							mCommandList->renderOperation(op);
						}
					}
				}
			}
		}
	}
}
