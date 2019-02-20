#pragma once
#include "CommonDefine.h"
#define __TBB_SOURCE_DIRECTLY_INCLUDED 1
#include "tbb/tbb.h"
#undef __TBB_SOURCE_DIRECTLY_INCLUDED
#if DEVILX_DEBUG
#define _XM_NO_INTRINSICS_
#endif
#include "DirectXMath.h"
#include "DirectXPackedVector.h"
#include "DirectXColors.h"
#include "DirectXCollision.h"
#include "tinyxml.h"
#include "boost/any.hpp"
#pragma warning(push)
#pragma warning(disable:4819)
#define FREEIMAGE_LIB
#include "FreeImage.h"
#pragma warning(pop)
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include "fbxsdk.h"
#define ASIO_STANDALONE
#include "asio.hpp"
#define GLEW_STATIC
#include "GL/glew.h"
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
#include "GL/wglew.h"
#include "GL/wglext.h"
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#include "GL/glxew.h";
#include "GL/glxext.h";
#endif
#include "lua.h"
#include "noise.h"