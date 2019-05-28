#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;
IGASwapChainImp::IGASwapChainImp(CGADeviceImp* device,EGLNativeWindowType window)
	:mEnvironment(nullptr)
{
	mEnvironment.reset(DEVILX_NEW CGAEnvironment(window,device->getVersion()==IGAEnum::EHighLevelDeviceVersion_OpenGLES));
	device->setEnvironment(mEnvironment.get());
}

IGASwapChainImp::~IGASwapChainImp()
{
}

IGARenderTargetView * IGASwapChainImp::getRenderTargetView() const
{
	return nullptr;
}

IGADepthStencilView * IGASwapChainImp::getDepthStencilView() const
{
	return nullptr;
}

Void IGASwapChainImp::present()
{
	mEnvironment->swapBuffer();
}