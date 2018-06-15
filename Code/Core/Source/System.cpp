#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CSystem::CSystem()
	:mSystem(nullptr)
	,mMemoryManager(nullptr)
	,mThreadManager(nullptr)
{
	mSystem=static_cast<ISystem*>(CMemoryManager::getSingleton().allocateBytes(sizeof(ISystem)));
	mMemoryManager=static_cast<IMemoryManager*>(CMemoryManager::getSingleton().allocateBytes(sizeof(IMemoryManager)));
	mThreadManager=static_cast<IThreadManager*>(CMemoryManager::getSingleton().allocateBytes(sizeof(IThreadManager)));
}

NSDevilX::NSCore::CSystem::~CSystem()
{
	CMemoryManager::getSingleton().deallocateBytes(mMemoryManager);
	CMemoryManager::getSingleton().deallocateBytes(mThreadManager);
}