#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;
IGASwapChainImp::IGASwapChainImp(IGADeviceImp* device,EGLNativeWindowType window)
	:mEnvironment(nullptr)
{
	mEnvironment.reset(DEVILX_NEW CGAEnvironment(window,device->getVersion()==IGAEnum::EDeviceVersion_OpenGLES));
	mRenderTargetView.reset(DEVILX_NEW IGARenderTargetViewImp(0,0,0));
	mDepthStencilView.reset(DEVILX_NEW IGADepthStencilViewImp(0,0,0));
}

IGASwapChainImp::~IGASwapChainImp()
{
}

IGARenderTargetView * IGASwapChainImp::getRenderTargetView() const
{
	return mRenderTargetView.get();
}

IGADepthStencilView * IGASwapChainImp::getDepthStencilView() const
{
	return mDepthStencilView.get();
}

Void IGASwapChainImp::present()
{
	eglSwapBuffers(mEnvironment->getDisplay(),mEnvironment->getSurface());
}