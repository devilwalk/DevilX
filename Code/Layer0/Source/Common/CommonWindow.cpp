#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CWindow::CWindow()
	:mHandle(nullptr)
	,mPosition(CInt2::sZero)
	,mSize(CUInt2::sZero)
	,mEventListener(nullptr)
{

}

NSDevilX::CWindow::~CWindow()
{
	if(getHandle())
	{
		DestroyWindow(static_cast<HWND>(getHandle()));
	}
}

Void NSDevilX::CWindow::setPosition(const CInt2 & position)
{
	if(position!=getPosition())
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

Void NSDevilX::CWindow::setSize(const CUInt2 & size)
{
	if(size!=getSize())
	{
		mSize=size;
		if(getSize()>CUInt2::sZero)
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
					static std::map<HWND,CWindow*> windows;
					CWindow * window=nullptr;
					switch(msg)
					{
					case WM_CREATE:
						windows[wnd]=static_cast<CWindow*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
						break;
					default:
					{
						auto iter=windows.find(wnd);
						if(windows.end()!=iter)
						{
							window=iter->second;
						}
					}
					}
					if(window)
					{
						switch(msg)
						{
						case WM_IME_CHAR:
							window->getEventListener()->onCharEvent(window,CUTF8Char(wParam));
							break;
						case WM_LBUTTONDOWN:
							window->getEventListener()->onButtonEvent(window,CWindowEventListener::EButtonType_Left,CWindowEventListener::EButtonEventType_ButtonDown,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_LBUTTONUP:
							window->getEventListener()->onButtonEvent(window,CWindowEventListener::EButtonType_Left,CWindowEventListener::EButtonEventType_ButtonUp,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_LBUTTONDBLCLK:
							window->getEventListener()->onButtonEvent(window,CWindowEventListener::EButtonType_Left,CWindowEventListener::EButtonEventType_ButtonDoubleClick,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_RBUTTONDOWN:
							window->getEventListener()->onButtonEvent(window,CWindowEventListener::EButtonType_Right,CWindowEventListener::EButtonEventType_ButtonDown,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_RBUTTONUP:
							window->getEventListener()->onButtonEvent(window,CWindowEventListener::EButtonType_Right,CWindowEventListener::EButtonEventType_ButtonUp,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_RBUTTONDBLCLK:
							window->getEventListener()->onButtonEvent(window,CWindowEventListener::EButtonType_Right,CWindowEventListener::EButtonEventType_ButtonDoubleClick,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_MBUTTONDOWN:
							window->getEventListener()->onButtonEvent(window,CWindowEventListener::EButtonType_Middle,CWindowEventListener::EButtonEventType_ButtonDown,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_MBUTTONUP:
							window->getEventListener()->onButtonEvent(window,CWindowEventListener::EButtonType_Middle,CWindowEventListener::EButtonEventType_ButtonUp,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_MBUTTONDBLCLK:
							window->getEventListener()->onButtonEvent(window,CWindowEventListener::EButtonType_Middle,CWindowEventListener::EButtonEventType_ButtonDoubleClick,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						}
					}
					return DefWindowProc(wnd,msg,wParam,lParam);
				};
				wnd_class.lpszClassName=_T("WindowDef");
				wnd_class.lpszMenuName=nullptr;
				wnd_class.style=CS_HREDRAW|CS_VREDRAW;
				RegisterClassEx(&wnd_class);
				mHandle=CreateWindowEx(0,wnd_class.lpszClassName,_T("WindowDef"),WS_POPUP,getPosition().x,getPosition().y,getSize().x,getSize().y,nullptr,nullptr,wnd_class.hInstance,this);
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

NSDevilX::CDesktop::CDesktop()
{}

NSDevilX::CDesktop::~CDesktop()
{}

VoidPtr NSDevilX::CDesktop::getHandle() const
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	return GetDesktopWindow();
#endif
}

CUInt2 NSDevilX::CDesktop::getSize()
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	RECT rc;
	GetClientRect(static_cast<HWND>(getHandle()),&rc);
	return CUInt2(rc.right-rc.left,rc.bottom-rc.top);
#endif
}