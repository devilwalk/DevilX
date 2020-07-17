#pragma once
#include "CommonDefine.h"
#include "CommonPlatformDefine.h"
//#include "tbb/tbb.h"
//#include "tbb/scalable_allocator.h"
#if DEVILX_DEBUG
#define _XM_NO_INTRINSICS_
#endif
//#include "DirectXMath.h"
//#include "DirectXPackedVector.h"
//#include "DirectXColors.h"
//#include "DirectXCollision.h"
#ifdef DEVILX_ANDROID
#define ANDROID_NDK
#endif
#include "tinyxml2.h"
#include "boost/any.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4819)
#endif
#define FREEIMAGE_LIB
#include "FreeImage.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#define ASIO_STANDALONE
#include "asio.hpp"
#define GLEW_STATIC
#define GLEW_EGL
#define GLEW_NO_GLU
#include "GL/glew.h"
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
#include "GL/wglew.h"
#include "GL/wglext.h"
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#include "GL/glxew.h";
#include "GL/glxext.h";
#endif
#define EGLAPI
#include "EGL/egl.h"
//#define VOLK_IMPLEMENTATION
#include "volk/volk.h"
//#include <vulkan/vulkan.h>
#include "lua.h"
#include "noise.h"