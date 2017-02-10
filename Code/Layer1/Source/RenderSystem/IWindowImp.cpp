#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IWindowImp::IWindowImp(VoidPtr handle)
	:mHandle(handle)
{}

NSDevilX::NSRenderSystem::IWindowImp::~IWindowImp()
{}

IRenderTarget * NSDevilX::NSRenderSystem::IWindowImp::queryInterface_IRenderTarget() const
{
	return const_cast<IWindowImp*>(this);
}

UInt32 NSDevilX::NSRenderSystem::IWindowImp::getWidth() const
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	RECT rc;
	::GetClientRect(static_cast<HWND>(getHandle()),&rc);
	return rc.right-rc.left+1;
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
}

UInt32 NSDevilX::NSRenderSystem::IWindowImp::getHeight() const
{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	RECT rc;
	::GetClientRect(static_cast<HWND>(getHandle()),&rc);
	return rc.bottom-rc.top+1;
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
}

Void NSDevilX::NSRenderSystem::IWindowImp::resize()
{
	notify(EMessage_Resize);
}