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
#include "ICoreCPPScriptEnvironment.h"
#include "ICoreDirectory.h"
#include "ICoreDirectXManager.h"
#include "ICoreEnum.h"
#include "ICoreFile.h"
#include "ICoreFileManager.h"
#include "ICoreFileProcesser.h"
#include "ICoreMemoryManager.h"
#include "ICoreNetworkConnection.h"
#include "ICoreNetworkHost.h"
#include "ICoreNetworkManager.h"
#include "ICoreReadWriteLock.h"
#include "ICoreResource.h"
#include "ICoreSystem.h"
#include "ICoreScriptManager.h"
#include "ICoreSemaphore.h"
#include "ICoreThread.h"
#include "ICoreThreadManager.h"
#include "ICoreThreadPool.h"
#include "ICoreTimer.h"
#include "ICoreGPUInterface.h"
