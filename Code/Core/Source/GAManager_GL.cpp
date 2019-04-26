#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

NSDevilX::NSCore::NSOpenGL::CGAManager::CGAManager()
{
}

NSDevilX::NSCore::NSOpenGL::CGAManager::~CGAManager()
{
	mSwapChains.destroyAll();
	mDevices.destroyAll();
}

IGADeviceImp* NSDevilX::NSCore::NSOpenGL::CGAManager::createDevice(IGAEnum::EDeviceVersion version)
{
	auto ret=DEVILX_NEW IGADeviceImp(version);
	mDevices.push_back(ret);
	return ret;
}

IGASwapChainImp* NSDevilX::NSCore::NSOpenGL::CGAManager::createSwapChain(IGADeviceImp* device,const IGAStruct::SGISwapChainDesc& desc)
{
	auto ret=DEVILX_NEW IGASwapChainImp(device,desc.OutputWindow);
	mSwapChains.push_back(ret);
	return ret;
}
