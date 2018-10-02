#pragma once
#include "CommonPlatformDefine.h"
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
#include <Windows.h>
#include <Windowsx.h>
#include <process.h>
#include <tchar.h>
#include <dxgi1_6.h>
#include <d3d9.h>
#include <d3d10_1.h>
#include <d3d11_4.h>
#include <d3d12.h>
#include <atlcomcli.h>
#include <d3dcompiler.h>
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#include <dlfcn.h>
#include <endian.h>
#endif
