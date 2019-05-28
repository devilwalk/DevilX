#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

NSDevilX::NSCore::NSOpenGL::CGAManager::CGAManager()
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	WNDCLASSEX wnd_class;
	wnd_class.cbClsExtra=0;
	wnd_class.cbSize=sizeof(WNDCLASSEX);
	wnd_class.cbWndExtra=0;
	wnd_class.hbrBackground=reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wnd_class.hCursor=LoadCursor(GetModuleHandle(nullptr),IDC_ARROW);
	wnd_class.hIcon=nullptr;
	wnd_class.hIconSm=nullptr;
	wnd_class.hInstance=GetModuleHandle(nullptr);
	wnd_class.lpfnWndProc=DefWindowProc;
	wnd_class.lpszClassName=_T("Temp");
	wnd_class.lpszMenuName=nullptr;
	wnd_class.style=CS_HREDRAW|CS_VREDRAW;
	RegisterClassEx(&wnd_class);
	auto wnd=CreateWindowEx(0,wnd_class.lpszClassName,_T("Temp"),WS_POPUP,0,0,1,1,nullptr,nullptr,wnd_class.hInstance,nullptr);
	ShowWindow(wnd,SW_NORMAL);
	UpdateWindow(wnd);
	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};
	auto dc=GetDC(wnd);
	auto fmt=ChoosePixelFormat(dc,&pfd);
	SetPixelFormat(dc,fmt,&pfd);
	auto context=wglCreateContext(dc);
	wglMakeCurrent(dc,context);
	glewInit();
	wglMakeCurrent(nullptr,nullptr);
	wglDeleteContext(context);
	ReleaseDC(wnd,dc);
	DestroyWindow(wnd);
#endif
}

NSDevilX::NSCore::NSOpenGL::CGAManager::~CGAManager()
{
	mSwapChains.destroyAll();
	mDevices.destroyAll();
}

CGADeviceImp* NSDevilX::NSCore::NSOpenGL::CGAManager::createDevice(IGAEnum::EHighLevelDeviceVersion version)
{
	auto ret=DEVILX_NEW CGADeviceImp(version);
	mDevices.push_back(ret);
	return ret;
}

IGASwapChainImp* NSDevilX::NSCore::NSOpenGL::CGAManager::createSwapChain(CGADeviceImp* device,const IGAStruct::SGISwapChainDesc& desc)
{
	auto ret=DEVILX_NEW IGASwapChainImp(device,desc.OutputWindow);
	mSwapChains.push_back(ret);
	return ret;
}
