#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;
#if _MSC_VER==1910 
//#pragma comment(lib,"RenderSystem_D3D11.2017.lib")
#pragma comment(lib,"RenderSystem_GL4.2017.lib")
//#pragma comment(lib,"RenderSystem_GLES3.2017.lib")
#elif _MSC_VER==1900
//#pragma comment(lib,"RenderSystem_D3D11.2015.lib")
//#pragma comment(lib,"RenderSystem_GL4.2015.lib")
#pragma comment(lib,"RenderSystem_GLES3.2015.lib")
#endif
Void main()
{
	CApp::getSingleton().run();
}