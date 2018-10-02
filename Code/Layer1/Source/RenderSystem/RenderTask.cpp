#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::CRenderTask::CRenderTask()
	:mCommandList(nullptr)
{
}

NSDevilX::NSRenderSystem::CRenderTask::~CRenderTask()
{
}

Void NSDevilX::NSRenderSystem::CRenderTask::prepare()
{
	_prepare();
	for(auto task:mTasks)
	{
		if(task)
			task->prepare();
	}
}

Void NSDevilX::NSRenderSystem::CRenderTask::process()
{
	_process();
	for(auto task:mTasks)
	{
		if(task)
			task->process();
	}
}

Void NSDevilX::NSRenderSystem::CRenderTask::_prepare()
{
}

Void NSDevilX::NSRenderSystem::CRenderTask::_process()
{
	if(mCommandList)
		mCommandList->execute();
}
