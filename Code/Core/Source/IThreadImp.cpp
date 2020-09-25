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
	delete mThread;
}

Void NSDevilX::NSCore::IThreadImp::startup(WorkFunction function,VoidPtr parameters)
{
	if(mThread)
		mThread->detach();
	auto context=DEVILX_NEW SContext(this,parameters);
	mThread=new std::thread(function,context);
}

Void NSDevilX::NSCore::IThreadImp::finish()
{
	mThread->join();
}
