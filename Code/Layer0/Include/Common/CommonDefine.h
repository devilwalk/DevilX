#pragma once
#if defined(DEBUG)||defined(_DEBUG)
#define DEVILX_DEBUG
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