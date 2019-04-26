#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::IGAManager::~IGAManager()
{}

IGADevice* NSDevilX::NSCore::IGAManager::createDevice(IGAEnum::EDeviceVersion version)
{
	switch(version)
	{
	case IGAEnum::EDeviceVersion_DirectX11:
		return NSDirectX::CGAManager::getSingleton().createDevice11();
	case IGAEnum::EDeviceVersion_OpenGL:
	case IGAEnum::EDeviceVersion_OpenGLES:
		return NSOpenGL::CGAManager::getSingleton().createDevice(version);
	default:
		return nullptr;
	}
}

IGASwapChain* NSDevilX::NSCore::IGAManager::createSwapChain(IGADevice* dev,const IGAStruct::SGISwapChainDesc& desc)
{
	switch(dev->getVersion())
	{
	case IGAEnum::EDeviceVersion_DirectX11:
		return NSDirectX::CGAManager::getSingleton().createSwapChain(static_cast<NSDirectX::NSVersion11::IGADeviceImp*>(dev),desc);
	case IGAEnum::EDeviceVersion_OpenGL:
	case IGAEnum::EDeviceVersion_OpenGLES:
		return NSOpenGL::CGAManager::getSingleton().createSwapChain(static_cast<NSOpenGL::IGADeviceImp*>(dev),desc);
	default:
		return nullptr;
	}
}
