#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CWindow::CWindow()
	:mHandle(nullptr)
	,mPosition(CInt2::sZero)
	,mSize(CUInt2::sZero)
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
				wnd_class.hCursor=LoadCursor(nullptr,IDC_ARROW);
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
						TVector<CWindowEventListener*> listeners;
						listeners.insert(listeners.end(),window->mEventListeners.begin(),window->mEventListeners.end());
						switch(msg)
						{
						case WM_IME_COMPOSITION:
							break;
						case WM_CHAR:
							for(auto listener:listeners)
								listener->onCharEvent(window,CUTF16Char(&wParam));
							break;
						case WM_LBUTTONDOWN:
							for(auto listener:listeners)
								listener->onMouseButtonEvent(window,CWindowEventListener::EMouseButtonType_Left,CWindowEventListener::EMouseButtonEventType_Down,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_LBUTTONUP:
							for(auto listener:listeners)
								listener->onMouseButtonEvent(window,CWindowEventListener::EMouseButtonType_Left,CWindowEventListener::EMouseButtonEventType_Up,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_LBUTTONDBLCLK:
							for(auto listener:listeners)
								listener->onMouseButtonEvent(window,CWindowEventListener::EMouseButtonType_Left,CWindowEventListener::EMouseButtonEventType_DoubleClick,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_RBUTTONDOWN:
							for(auto listener:listeners)
								listener->onMouseButtonEvent(window,CWindowEventListener::EMouseButtonType_Right,CWindowEventListener::EMouseButtonEventType_Down,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_RBUTTONUP:
							for(auto listener:listeners)
								listener->onMouseButtonEvent(window,CWindowEventListener::EMouseButtonType_Right,CWindowEventListener::EMouseButtonEventType_Up,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_RBUTTONDBLCLK:
							for(auto listener:listeners)
								listener->onMouseButtonEvent(window,CWindowEventListener::EMouseButtonType_Right,CWindowEventListener::EMouseButtonEventType_DoubleClick,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_MBUTTONDOWN:
							for(auto listener:listeners)
								listener->onMouseButtonEvent(window,CWindowEventListener::EMouseButtonType_Middle,CWindowEventListener::EMouseButtonEventType_Down,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_MBUTTONUP:
							for(auto listener:listeners)
								listener->onMouseButtonEvent(window,CWindowEventListener::EMouseButtonType_Middle,CWindowEventListener::EMouseButtonEventType_Up,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_MBUTTONDBLCLK:
							for(auto listener:listeners)
								listener->onMouseButtonEvent(window,CWindowEventListener::EMouseButtonType_Middle,CWindowEventListener::EMouseButtonEventType_DoubleClick,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_MOUSEMOVE:
							for(auto listener:listeners)
								listener->onMouseMoveEvent(window,CUInt2(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
							break;
						case WM_MOUSEWHEEL:
							for(auto listener:listeners)
								listener->onMouseWheelEvent(window,GET_WHEEL_DELTA_WPARAM(wParam));
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

CInt2 NSDevilX::CWindow::getCursorPosition() const
{
	CInt2 ret;
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	::GetCursorPos(reinterpret_cast<LPPOINT>(&ret));
	::ScreenToClient(static_cast<HWND>(getHandle()),reinterpret_cast<LPPOINT>(&ret));
#endif
	return ret;
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