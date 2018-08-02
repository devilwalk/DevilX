#pragma once
#include "CommonDefine.h"
#if DEVILX_DEBUG && (!defined(DEVILX_UNUSE_VLD))
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
#include <vld.h>
#endif
#define _XM_NO_INTRINSICS_
#endif
#include "DirectXMath/DirectXMath.h"
#include "DirectXMath/DirectXPackedVector.h"
#include "DirectXMath/DirectXColors.h"
#include "DirectXMath/DirectXCollision.h"
#undef __TBB_SOURCE_DIRECTLY_INCLUDED
#include "TinyXML/tinyxml.h"
