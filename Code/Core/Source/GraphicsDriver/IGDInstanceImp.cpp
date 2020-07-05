#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IInstanceImp::IInstanceImp()
{
}

NSDevilX::NSCore::NSGraphicsDriver::IInstanceImp::~IInstanceImp()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IInstanceImp::IInstanceImp()
{
	auto success = CreateDXGIFactory(__uuidof(mInternal),reinterpret_cast<void**>(&mInternal));
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

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::IInstanceImp()
	:mInternal(VK_NULL_HANDLE)
{
	//auto success = volkInitialize();
	//if(success==VK_SUCCESS)
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
		vkCreateInstance(&info,nullptr,&mInternal);
	}
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
