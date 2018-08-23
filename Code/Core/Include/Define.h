#pragma once

#define DEVILX_MEMORY_TRACK_INFO __FILE__,__FUNCTION__,__LINE__
//#undef DEVILX_MEMORY_TRACK_ENABLE
#ifdef DEVILX_MEMORY_TRACK_ENABLE
#define DEVILX_ALLOC(sizeInBytes) CMemoryManager::getSingleton().allocateBytes(sizeInBytes,DEVILX_MEMORY_TRACK_INFO)
#define DEVILX_FREE(address) CMemoryManager::getSingleton().deallocateBytes(address,DEVILX_MEMORY_TRACK_INFO)
#define DEVILX_ALIGNED_ALLOC(sizeInBytes,alignment) CMemoryManager::getSingleton().alignedAllocateBytes(sizeInBytes,alignment,DEVILX_MEMORY_TRACK_INFO)
#define DEVILX_ALIGNED_FREE(address) CMemoryManager::getSingleton().alignedDeallocateBytes(address,DEVILX_MEMORY_TRACK_INFO)
#define DEVILX_NEW new(DEVILX_MEMORY_TRACK_INFO)
#define DEVILX_NORMAL_NEW(x) CMemoryManager::getSingleton().newNormal<x>(DEVILX_MEMORY_TRACK_INFO)
#define DEVILX_OBJECT_NEW(x) CMemoryManager::getSingleton().newObject<x>(DEVILX_MEMORY_TRACK_INFO)
#define DEVILX_DELETE(x) {CMemoryManager::getSingleton().getMemoryTracker()->deallocate(x,DEVILX_MEMORY_TRACK_INFO);delete x;}
#define DEVILX_OBJECT_DELETE(x) {CMemoryManager::getSingleton().deleteObject(x,DEVILX_MEMORY_TRACK_INFO);}
#else
#define DEVILX_ALLOC(sizeInBytes) CMemoryManager::getSingleton().allocateBytes(sizeInBytes)
#define DEVILX_FREE(address) CMemoryManager::getSingleton().deallocateBytes(address)
#define DEVILX_ALIGNED_ALLOC(sizeInBytes,alignment) CMemoryManager::getSingleton().alignedAllocateBytes(sizeInBytes,alignment)
#define DEVILX_ALIGNED_FREE(address) CMemoryManager::getSingleton().alignedDeallocateBytes(address)
#define DEVILX_NEW new
#define DEVILX_NORMAL_NEW(x) CMemoryManager::getSingleton().newNormal<x>()
#define DEVILX_OBJECT_NEW(x) CMemoryManager::getSingleton().newObject<x>()
#define DEVILX_DELETE delete
#define DEVILX_OBJECT_DELETE(x) {CMemoryManager::getSingleton().deleteObject(x);}
#endif
#define DEVILX_TYPED_ALLOC(type,count) static_cast<type*>(DEVILX_ALLOC(sizeof(type)*count))
#define DEVILX_NORMAL_DELETE(x) DEVILX_FREE(x)
