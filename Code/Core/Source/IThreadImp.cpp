#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::IThreadImp::IThreadImp()
	:mThread(nullptr)
{
}

NSDevilX::NSCore::IThreadImp::~IThreadImp()
{
	if(!mThread->joinable())
		mThread->join();
	mThread->detach();
	DEVILX_OBJECT_DELETE(mThread);
}

Void NSDevilX::NSCore::IThreadImp::startup(WorkFunction function,VoidPtr parameters)
{
	if(mThread)
		mThread->detach();
	auto context=DEVILX_TYPED_ALLOC(SContext,1);
	context->SContext::SContext(this,parameters);
	mThread=DEVILX_TYPED_ALLOC(std::thread,1);
	mThread->std::thread::thread(function,context);
}

Void NSDevilX::NSCore::IThreadImp::finish()
{
	mThread->join();
}
