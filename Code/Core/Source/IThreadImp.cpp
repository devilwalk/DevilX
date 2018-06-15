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
	mThread=new std::thread(function,new SContext(this,parameters));
}

Void NSDevilX::NSCore::IThreadImp::finish()
{
	mThread->join();
}
