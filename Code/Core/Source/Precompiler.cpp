#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

#pragma comment(lib,"Common.lib")
#pragma comment(lib,"tinyxml.lib")
#pragma comment(lib,"FreeImage.lib")
#pragma comment(lib,"freetype.lib")
#pragma comment(lib,"libfbxsdk.lib")
#pragma comment(lib,"glew.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3d10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
//#pragma comment(lib,"libEGL.lib")
#pragma comment(lib,"egl.lib")
#if DEVILX_DEBUG
#pragma comment(lib,"tbb_debug.lib")
#else
#pragma comment(lib,"tbb.lib")
#endif