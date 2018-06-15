#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::IMemoryManager::~IMemoryManager(){}

void * NSDevilX::NSCore::IMemoryManager::allocateBytes(size_t sizeInBytes)
{
	return CMemoryManager::getSingleton().allocateBytes(sizeInBytes);
}

void NSDevilX::NSCore::IMemoryManager::deallocateBytes(void * address)
{
	CMemoryManager::getSingleton().deallocateBytes(address);
}

void * NSDevilX::NSCore::IMemoryManager::alignedAllocateBytes(size_t sizeInBytes,size_t alignment)
{
	return CMemoryManager::getSingleton().alignedAllocateBytes(sizeInBytes,alignment);
}

void NSDevilX::NSCore::IMemoryManager::alignedDeallocateBytes(void * address)
{
	CMemoryManager::getSingleton().alignedDeallocateBytes(address);
}
