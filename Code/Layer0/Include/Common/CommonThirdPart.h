#pragma once
#include "CommonDefine.h"
#ifdef DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
#include <vld.h>
#endif
#define _XM_NO_INTRINSICS_
#endif
#include "DirectXMath/DirectXMath.h"
#include "DirectXMath/DirectXPackedVector.h"
#include "DirectXMath/DirectXColors.h"
#include "DirectXMath/DirectXCollision.h"
#define __TBB_SOURCE_DIRECTLY_INCLUDED 1
#include "TBB/tbb/tbb_allocator.h"
#include "TBB/tbb/scalable_allocator.h"
#include "TBB/tbb/reader_writer_lock.h"
#include "TBB/tbb/concurrent_queue.h"
#include "TBB/tbb/concurrent_vector.h"
#undef __TBB_SOURCE_DIRECTLY_INCLUDED
#include "TinyXML/tinyxml.h"
#pragma warning(push)
#pragma warning(disable:4819)
#define FREEIMAGE_LIB
#include "FreeImage/FreeImage.h"
#pragma warning(pop)
#include "FreeType/ft2build.h"
#include "FreeType/freetype/freetype.h"
#include FT_GLYPH_H
#include "Lua/lua.hpp"
