#pragma once
#if defined(_MSC_VER)
#ifdef DLLEXPORT
#define DLLAPI _declspec(dllexport)
#else
#define DLLAPI _declspec(dllimport)
#endif
#elif defined(GCC)
#endif
#include "ICoreBuffer.h"
#include "ICoreDevice.h"
#include "ICoreEnum.h"
#include "ICoreFileManager.h"
#include "ICoreMemoryManager.h"
#include "ICoreReadWriteLock.h"
#include "ICoreResource.h"
#include "ICoreSystem.h"
#include "ICoreSemaphore.h"
#include "ICoreThread.h"
#include "ICoreThreadManager.h"
#include "ICoreThreadPool.h"
