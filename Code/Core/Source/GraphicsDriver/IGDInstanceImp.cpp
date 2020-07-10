#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IInstanceImp::IInstanceImp(IEnum::EInstance type)
	:mType(type)
{
}

NSDevilX::NSCore::NSGraphicsDriver::IInstanceImp::~IInstanceImp()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IInstanceImp::IInstanceImp(IEnum::EInstance type)
	:NSGraphicsDriver::IInstanceImp(type)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IInstanceImp::~IInstanceImp()
{
}

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IInstanceImp::enumPhysicsDevices(IPhysicsDevice** outDevices)
{
	if(mInternal)
	{
		CComPtr<IDXGIAdapter> adapter;
		UINT index=0;
		while(SUCCEEDED(mInternal->EnumAdapters(index,&adapter)))
		{
			if(outDevices)
			{
				auto dev =new NSDXGI::IPhysicsDeviceImp(adapter);
				outDevices[index]=dev;
				mPhysicsDevices.push_back(dev);
			}
			++index;
		}
		return index;
	}
	return 0;
}

Boolean NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IInstanceImp::initialize()
{
	Boolean success=false;
	switch(mType)
	{
	case IEnum::EInstance_D3D12_0:
	case IEnum::EInstance_D3D11_3:
	case IEnum::EInstance_D3D11_2:
	case IEnum::EInstance_D3D11_1:
	{
		IDXGIFactory1* ptr=nullptr;
		success=SUCCEEDED(CreateDXGIFactory1(__uuidof(IDXGIFactory1),reinterpret_cast<void**>(&ptr)));
		mInternal=ptr;
	}
	break;
	default:
		success=SUCCEEDED(CreateDXGIFactory1(__uuidof(mInternal),reinterpret_cast<void**>(&mInternal)));
	}
	return success;
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::IInstanceImp()
	:NSGraphicsDriver::IInstanceImp(IEnum::EInstance_Vulkan)
	,mInternal(VK_NULL_HANDLE)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::~IInstanceImp()
{
	if(mInternal!=VK_NULL_HANDLE)
	{
		vkDestroyInstance(mInternal,nullptr);
	}
}

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::enumPhysicsDevices(IPhysicsDevice** outDevices)
{
	uint32_t count=0;
	auto success=vkEnumeratePhysicalDeviceGroups(mInternal,&count,nullptr);
	if((VK_SUCCESS==success)&&(outDevices!=nullptr))
	{
		TVector(VkPhysicalDeviceGroupProperties) devices;
		devices.resize(count);
		success=vkEnumeratePhysicalDeviceGroups(mInternal,&count,&devices[0]);
		if(VK_SUCCESS==success)
		{
			UInt32 index=0;
			for(uint32_t i=0; i<count; i++)
			{
				for(uint32_t j=0; j<devices[i].physicalDeviceCount; j++)
				{
					auto dev=new NSVulkan::IPhysicsDeviceImp(devices[i].physicalDevices[j],i);
					mPhysicsDevices.push_back(dev);
					outDevices[index]=dev;
				}
			}
		}
	}
	return count;
}

Boolean NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::initialize()
{
	auto success=VK_ERROR_INITIALIZATION_FAILED;
	success= volkInitialize();
	if(success==VK_SUCCESS)
	{
		VkInstanceCreateInfo info={};
		memset(&info,0,sizeof(info));
		info.sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		#ifdef DEVILX_DEBUG
		VkValidationFeaturesEXT validation_features={};
		memset(&validation_features,0,sizeof(validation_features));
		validation_features.sType=VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
		VkValidationFeatureEnableEXT enable_validation_features[]=
		{
			VkValidationFeatureEnableEXT::VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
			VkValidationFeatureEnableEXT::VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
			VkValidationFeatureEnableEXT::VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT
		};
		validation_features.enabledValidationFeatureCount=_countof(enable_validation_features);
		validation_features.pEnabledValidationFeatures=enable_validation_features;
		info.pNext=&validation_features;
		#endif
		#ifdef DEVILX_FINAL
		VkValidationFlagsEXT validation_flags={};
		memset(&validation_flags,0,sizeof(validation_flags));
		VkValidationCheckEXT check[]={VkValidationCheckEXT::VK_VALIDATION_CHECK_ALL_EXT};
		validation_flags.disabledValidationCheckCount=_countof(check);
		validation_flags.pDisabledValidationChecks=check;
		info.pNext=&validation_flags;
		#endif
		success = vkCreateInstance(&info,nullptr,&mInternal);
		if(success>=VK_SUCCESS)
		{
			volkLoadInstance(mInternal);
		}
	}
	return success>=VK_SUCCESS;
}
