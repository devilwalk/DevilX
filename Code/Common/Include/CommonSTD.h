#pragma once
#include "CommonDefine.h"
#include "CommonPlatformDefine.h"
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
#if DEVILX_DEBUG
#define _CRTDBG_MAP_ALLOC  
#endif
#endif
#include <stdlib.h>  
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
#if DEVILX_DEBUG
#include <crtdbg.h>
#endif
#endif
#include <list>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <mutex>
#include <atomic>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <assert.h>
#include <algorithm>
#include <thread>
#include <bitset>
#include <array>
#include <math.h>