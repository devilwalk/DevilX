#pragma once
#include "PlatformDefine.h"
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
#include <Windows.h>
#include <Windowsx.h>
#include <process.h>
#include <tchar.h>
#include <direct.h>
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#include <dlfcn.h>
#include <endian.h>
#include <dirent.h>
#endif
