#pragma once
#if (!defined(DEVILX_DEBUG))&&(defined(DEBUG)||defined(_DEBUG))
#define DEVILX_DEBUG 1
#endif
#ifndef OUT
#define OUT
#endif
#define DEVILX_MEMORY_TRACK_INFO __FILE__,__FUNCTION__,__LINE__
#define DEVILX_TRACK_NEW new(DEVILX_MEMORY_TRACK_INFO)
#define DEVILX_TRACK_DELETE(address) if(address){getDefaultMemoryTracker()->deallocate(address,DEVILX_MEMORY_TRACK_INFO);delete address;}
#define DEVILX_TRACK_ALLOC(sizeInBytes) NSDevilX::trackAllocateBytes(sizeInBytes,DEVILX_MEMORY_TRACK_INFO)
#define DEVILX_TRACK_FREE(address) NSDevilX::trackDeallocateBytes(address,DEVILX_MEMORY_TRACK_INFO)
#undef DEVILX_MEMORY_TRACK_ENABLE
#ifdef DEVILX_MEMORY_TRACK_ENABLE
#define DEVILX_NEW DEVILX_TRACK_NEW
#define DEVILX_DELETE DEVILX_TRACK_DELETE
#define DEVILX_ALLOC(sizeInBytes) DEVILX_TRACK_ALLOC_SIZE(sizeInBytes)
#define DEVILX_FREE(address) DEVILX_TRACK_FREE_SIZE(address)
#define DEVILX_TRACK_SHUTDOWN destroyMemoryTracker();
#else
#define DEVILX_NEW new
#define DEVILX_DELETE delete
#define DEVILX_ALLOC(sizeInBytes) NSDevilX::allocateBytes(sizeInBytes)
#define DEVILX_FREE(address) NSDevilX::deallocateBytes(address)
#define DEVILX_TRACK_SHUTDOWN
#endif
#define DEVILX_SAFE_DELETE(x) DEVILX_DELETE(x);x=0;
#define DEVILX_BYTE_ORDER_LITTLE_ENDIAN 0
#define DEVILX_BYTE_ORDER_BIG_ENDIAN 1
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
#define DEVILX_BYTE_ORDER DEVILX_BYTE_ORDER_LITTLE_ENDIAN
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#endif