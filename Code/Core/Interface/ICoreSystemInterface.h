#pragma once
#if defined(_MSC_VER)
#ifdef DLLEXPORT
#define DLLAPI _declspec(dllexport)
#else
#define DLLAPI _declspec(dllimport)
#endif
#else
#define DLLAPI
#endif
#include "Common.h"
#include "ICoreCPPScriptEnvironment.h"
#include "ICoreDirectory.h"
#include "ICoreEnum.h"
#include "ICoreFile.h"
#include "ICoreFileManager.h"
#include "ICoreFileProcesser.h"
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
#include "GraphicsDriver/IGDInterface.h"
