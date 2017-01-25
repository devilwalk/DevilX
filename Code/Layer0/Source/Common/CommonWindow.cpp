#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CWindow::CWindow()
	:mHandle(nullptr)
	,mPosition(CSInt2::sZero)
	,mSize(CSInt2::sZero)
{

}

NSDevilX::CWindow::~CWindow()
{
	if(getHandle())
	{
		DestroyWindow(static_cast<HWND>(getHandle()));
	}
}

Void NSDevilX::CWindow::setPosition(const CSInt2 & position)
{
	if(position!=mPosition)
	{
		mPosition=position;
		if(getHandle())
		{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
			MoveWindow(static_cast<HWND>(getHandle()),getPosition().x,getPosition().y,getSize().x,getSize().y,FALSE);
#endif
		}
	}
}

Void NSDevilX::CWindow::setSize(const CSInt2 & size)
{
	if(size!=getSize())
	{
		mSize=size;
		if(getSize()>CSInt2::sZero)
		{
			if(getHandle())
			{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
				MoveWindow(static_cast<HWND>(getHandle()),getPosition().x,getPosition().y,getSize().x,getSize().y,FALSE);
#endif
			}
			else
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
				wnd_class.lpfnWndProc=[](HWND wnd,UINT msg,WPARAM wParam,LPARAM lParam)
				{
					return DefWindowProc(wnd,msg,wParam,lParam);
				};
				wnd_class.lpszClassName=_T("WindowDef");
				wnd_class.lpszMenuName=nullptr;
				wnd_class.style=CS_HREDRAW|CS_VREDRAW;
				RegisterClassEx(&wnd_class);
				mHandle=CreateWindowEx(0,wnd_class.lpszClassName,_T("WindowDef"),WS_POPUP,getPosition().x,getPosition().y,getSize().x,getSize().y,nullptr,nullptr,wnd_class.hInstance,nullptr);
				ShowWindow(static_cast<HWND>(getHandle()),SW_NORMAL);
				UpdateWindow(static_cast<HWND>(getHandle()));
#endif
			}
		}
		else if(getHandle())
		{
			DestroyWindow(static_cast<HWND>(getHandle()));
			mHandle=nullptr;
		}
	}
}