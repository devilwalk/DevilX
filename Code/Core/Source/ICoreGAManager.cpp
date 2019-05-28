#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::IGAManager::~IGAManager()
{}

IGAHighLevelDevice* NSDevilX::NSCore::IGAManager::createDevice(IGAEnum::EHighLevelDeviceVersion version)
{
	switch(version)
	{
	case IGAEnum::EHighLevelDeviceVersion_DirectX11:
		return NSDirectX::CGAManager::getSingleton().createDevice11();
	case IGAEnum::EHighLevelDeviceVersion_OpenGL:
	case IGAEnum::EHighLevelDeviceVersion_OpenGLES:
		return NSOpenGL::CGAManager::getSingleton().createDevice(version);
	default:
		return nullptr;
	}
}

IGASwapChain* NSDevilX::NSCore::IGAManager::createSwapChain(IGADevice* dev,const IGAStruct::SGISwapChainDesc& desc)
{
	auto high_level_dev=dynamic_cast<IGAHighLevelDevice*>(dev);
	if(high_level_dev)
	{
		switch(high_level_dev->getVersion())
		{
		case IGAEnum::EHighLevelDeviceVersion_DirectX11:
			return NSDirectX::CGAManager::getSingleton().createSwapChain(static_cast<NSDirectX::NSVersion11::IGADeviceImp*>(dev),desc);
		case IGAEnum::EHighLevelDeviceVersion_OpenGL:
		case IGAEnum::EHighLevelDeviceVersion_OpenGLES:
			return NSOpenGL::CGAManager::getSingleton().createSwapChain(static_cast<NSOpenGL::CGADeviceImp*>(dev),desc);
		default:
			return nullptr;
		}
	}
	else
	{
		auto low_level_dev=dynamic_cast<IGALowLevelDevice*>(dev);
		switch(low_level_dev->getVersion())
		{
		case IGAEnum::ELowLevelDeviceVersion_DirectX12:
		case IGAEnum::ELowLevelDeviceVersion_Vulkan:
		default:
			return nullptr;
		}
	}
}
