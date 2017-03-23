#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IWindowImp::IWindowImp(CWindow * window)
	:mWindow(window)
{}

NSDevilX::NSRenderSystem::IWindowImp::~IWindowImp()
{}

IRenderTarget * NSDevilX::NSRenderSystem::IWindowImp::queryInterface_IRenderTarget() const
{
	return const_cast<IWindowImp*>(this);
}

CWindow * NSDevilX::NSRenderSystem::IWindowImp::getWindow() const
{
	return mWindow;
}