#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;

NSDevilX::NSCore::NSDirectX::CGAManager::CGAManager()
	:mFactory(nullptr)
{
	CreateDXGIFactory2(0,__uuidof(mFactory),reinterpret_cast<VoidPtr*>(&mFactory));
}

NSDevilX::NSCore::NSDirectX::CGAManager::~CGAManager()
{
	mSwapChains.destroyAll();
	mDevices11.destroyAll();
	DEVILX_COM_SAFE_RELEASE(mFactory);
}

NSVersion11::IGADeviceImp * NSDevilX::NSCore::NSDirectX::CGAManager::createDevice11()
{
	auto ret=DEVILX_NEW NSVersion11::IGADeviceImp();
	mDevices11.push_back(ret);
	return ret;
}

IGASwapChainImp * NSDevilX::NSCore::NSDirectX::CGAManager::createSwapChain(NSVersion11::IGADeviceImp * device,const IGAStruct::SGISwapChainDesc & desc)
{
	auto ret=DEVILX_NEW IGASwapChainImp(device->getInternal(),CUtility::mapping(desc));
	mSwapChains.push_back(ret);
	return ret;
}
