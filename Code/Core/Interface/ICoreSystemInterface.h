#pragma once
#if defined(_MSC_VER)
#ifdef DLLEXPORT
#define DLLAPI _declspec(dllexport)
#else
#define DLLAPI _declspec(dllimport)
#endif
#elif defined(GCC)
#endif
#include "Common.h"
#include "ICoreBuffer.h"
#include "ICoreDevice.h"
#include "ICoreDirectory.h"
#include "ICoreEnum.h"
#include "ICoreFile.h"
#include "ICoreFileManager.h"
#include "ICoreFileProcesser.h"
#include "ICoreMemoryManager.h"
#include "ICoreNetworkConnection.h"
#include "ICoreNetworkManager.h"
#include "ICoreReadWriteLock.h"
#include "ICoreResource.h"
#include "ICoreSystem.h"
#include "ICoreSemaphore.h"
#include "ICoreThread.h"
#include "ICoreThreadManager.h"
#include "ICoreThreadPool.h"
