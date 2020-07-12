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
	if(mPhysicsDeviceGroups.empty())
	{
		_enumPhysicsDevicesAndGroups();
	}
	UInt32 ret=0;
	if(outDevices)
	{
		for(auto group:mPhysicsDeviceGroups)
		{
			for(UInt32 i=0; i<group->getDeviceCount(); i++)
			{
				outDevices[ret++]=group->getDevice(i);
			}
		}
	}
	else
	{
		for(auto group:mPhysicsDeviceGroups)
		{
			ret+=group->getDeviceCount();
		}
	}
	return ret;
}

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IInstanceImp::enumPhysicsDeviceGroups(IPhysicsDeviceGroup** outGroups)
{
	if(mPhysicsDeviceGroups.empty())
	{
		_enumPhysicsDevicesAndGroups();
	}
	if(outGroups)
	{
		UInt32 ptr=0;
		for(auto group:mPhysicsDeviceGroups)
		{
			outGroups[ptr++]=group;
		}
	}
	return static_cast<UInt32>(mPhysicsDeviceGroups.size());
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

Void NSDevilX::NSCore::NSGraphicsDriver::NSDXGI::IInstanceImp::_enumPhysicsDevicesAndGroups()
{
	if(mInternal)
	{
		CComPtr<IDXGIAdapter> adapter;
		UINT index=0;
		while(SUCCEEDED(mInternal->EnumAdapters(index,&adapter)))
		{
			auto group=DEVILX_NEW NSDXGI::IPhysicsDeviceGroupImp(adapter);
			auto dev=DEVILX_NEW NSDXGI::IPhysicsDeviceImp(0,group);
			group->addDevice(dev);
			mPhysicsDeviceGroups.push_back(group);
			++index;
		}
	}
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
	if(mPhysicsDeviceGroups.empty())
	{
		_enumPhysicsDevicesAndGroups();
	}
	UInt32 ret=0;
	if(outDevices)
	{
		for(auto group:mPhysicsDeviceGroups)
		{
			for(UInt32 i=0; i<group->getDeviceCount(); i++)
			{
				outDevices[ret++]=group->getDevice(i);
			}
		}
	}
	else
	{
		for(auto group:mPhysicsDeviceGroups)
		{
			ret+=group->getDeviceCount();
		}
	}
	return static_cast<UInt32>(mPhysicsDeviceGroups.size());
}

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::enumPhysicsDeviceGroups(IPhysicsDeviceGroup** outGroups)
{
	if(mPhysicsDeviceGroups.empty())
	{
		_enumPhysicsDevicesAndGroups();
	}
	if(outGroups)
	{
		UInt32 ptr=0;
		for(auto dev:mPhysicsDeviceGroups)
		{
			outGroups[ptr++]=dev;
		}
	}
	return static_cast<UInt32>(mPhysicsDeviceGroups.size());
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

void NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::_enumPhysicsDevicesAndGroups()
{
	uint32_t count=0;
	auto success=vkEnumeratePhysicalDeviceGroups(mInternal,&count,nullptr);
	if(VK_SUCCESS==success)
	{
		TVector(VkPhysicalDeviceGroupProperties) groups;
		groups.resize(count);
		success=vkEnumeratePhysicalDeviceGroups(mInternal,&count,&groups[0]);
		if(VK_SUCCESS==success)
		{
			UInt32 index=0;
			for(uint32_t i=0; i<count; i++)
			{
				auto group=DEVILX_NEW IPhysicsDeviceGroupImp(i);
				for(uint32_t j=0; j<groups[i].physicalDeviceCount; j++)
				{
					auto dev=new NSVulkan::IPhysicsDeviceImp(groups[i].physicalDevices[j],group);
					group->addDevice(dev);
				}
				mPhysicsDeviceGroups.push_back(group);
			}
		}
	}
}
