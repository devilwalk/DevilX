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
	mDevices.destroyAll();
	mPhysicsDeviceGroups.destroyAll();
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IInstanceImp::IInstanceImp(IEnum::EInstance type)
	:NSGraphicsDriver::IInstanceImp(type)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IInstanceImp::~IInstanceImp()
{
}

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IInstanceImp::enumPhysicalDevices(IPhysicalDevice** outDevices)
{
	if(mPhysicsDeviceGroups.empty())
	{
		_enumPhysicalDevicesAndGroups();
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

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IInstanceImp::enumPhysicalDeviceGroups(IPhysicalDeviceGroup** outGroups)
{
	if(mPhysicsDeviceGroups.empty())
	{
		_enumPhysicalDevicesAndGroups();
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

Boolean NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IInstanceImp::initialize()
{
	Boolean success=false;
	switch(mType)
	{
	case IEnum::EInstance_D3D12_1:
	case IEnum::EInstance_D3D12_0:
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

Void NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IInstanceImp::_enumPhysicalDevicesAndGroups()
{
	if(mInternal)
	{
		IDXGIAdapter* adapter=nullptr;
		UINT index=0;
		while(SUCCEEDED(mInternal->EnumAdapters(index,&adapter)))
		{
			auto group=DEVILX_NEW NSD3D::IPhysicalDeviceGroupImp(adapter,this);
			NSGraphicsDriver::IPhysicalDeviceImp* dev=nullptr;
			switch(mType)
			{
			case IEnum::EInstance_D3D12_1:
			case IEnum::EInstance_D3D12_0:
				dev=DEVILX_NEW NSD3D12::IPhysicalDeviceImp(0,group);
				break;
			case IEnum::EInstance_D3D11_1:
			case IEnum::EInstance_D3D11_0:
			case IEnum::EInstance_D3D10_1:
			case IEnum::EInstance_D3D10_0:
				dev=DEVILX_NEW INonePhysicalDeviceImp(group);
				break;
			}
			group->addDevice(dev);
			mPhysicsDeviceGroups.push_back(group);
			++index;
		}
	}
}

IDevice* NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IInstanceImp::createDevice(IPhysicalDeviceGroup* deviceGroup)
{
	IDeviceImp* ret=nullptr;
	switch(mType)
	{
	case IEnum::EInstance_D3D12_1:
	case IEnum::EInstance_D3D12_0:
		ret=_createDevice12(static_cast<IPhysicalDeviceGroupImp*>(deviceGroup));
		break;
	case IEnum::EInstance_D3D11_1:
	case IEnum::EInstance_D3D11_0:
		ret=_createDevice11(static_cast<IPhysicalDeviceGroupImp*>(deviceGroup));
		break;
	case IEnum::EInstance_D3D10_1:
	case IEnum::EInstance_D3D10_0:
		break;
	}
	if(ret)
	{
		mDevices.push_back(ret);
	}
	return ret;
}

IDeviceImp* NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IInstanceImp::_createDevice12(IPhysicalDeviceGroup* deviceGroup)
{
	ID3D12Device* dev=nullptr;
	auto success=SUCCEEDED(D3D12CreateDevice(static_cast<IPhysicalDeviceGroupImp*>(deviceGroup)->getInternal(),D3D_FEATURE_LEVEL_10_0,__uuidof(dev),reinterpret_cast<VoidPtr*>(&dev)));
	IDeviceImp* ret=nullptr;
	if(success)
	{
		ret=DEVILX_NEW NSD3D12::IDeviceImp(dev,static_cast<IPhysicalDeviceGroupImp*>(deviceGroup));
	}
	return ret;
}

IDeviceImp* NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IInstanceImp::_createDevice11(IPhysicalDeviceGroup* deviceGroup)
{
	ID3D11Device* dev=nullptr;
	D3D_FEATURE_LEVEL levels[]={D3D_FEATURE_LEVEL_12_1,D3D_FEATURE_LEVEL_12_0,D3D_FEATURE_LEVEL_11_1,D3D_FEATURE_LEVEL_11_0,D3D_FEATURE_LEVEL_10_1,D3D_FEATURE_LEVEL_10_0,D3D_FEATURE_LEVEL_9_3};
	D3D_FEATURE_LEVEL o_level;
#ifdef DEVILX_DEBUG
	UINT flag=D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT flag=0;
#endif
	auto success=SUCCEEDED(D3D11CreateDevice(static_cast<IPhysicalDeviceGroupImp*>(deviceGroup)->getInternal(),D3D_DRIVER_TYPE_HARDWARE,NULL
		,flag,levels,_countof(levels),D3D_SDK_VERSION,&dev,&o_level,nullptr));
	IDeviceImp* ret=nullptr;
	if(success)
	{
		ret=DEVILX_NEW NSD3D11::IDeviceImp(dev,static_cast<IPhysicalDeviceGroupImp*>(deviceGroup));
	}
	return ret;
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

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::enumPhysicalDevices(IPhysicalDevice** outDevices)
{
	if(mPhysicsDeviceGroups.empty())
	{
		_enumPhysicalDevicesAndGroups();
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

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::enumPhysicalDeviceGroups(IPhysicalDeviceGroup** outGroups)
{
	if(mPhysicsDeviceGroups.empty())
	{
		_enumPhysicalDevicesAndGroups();
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
	auto success=false;
	success=volkInitialize()>=VK_SUCCESS;
	if(success)
	{
		VkInstanceCreateInfo info={};
		memset(&info,0,sizeof(info));
		info.sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		#ifdef DEVILX_DEBUG

		uint32_t count=0;
		success&=(vkEnumerateInstanceLayerProperties(&count,nullptr)>=VK_SUCCESS);
		TVector(VkLayerProperties) layer_props;
		layer_props.resize(count);
		success&=(vkEnumerateInstanceLayerProperties(&count,&layer_props[0])>=VK_SUCCESS);
		TVector(ConstCharPtr) layer_names;
		layer_names.reserve(count);
		for(auto const& prop:layer_props)
		{
			//layer_names.push_back(prop.layerName);
		}
		if(!layer_names.empty())
		{
			info.enabledLayerCount=static_cast<uint32_t>(layer_names.size());
			info.ppEnabledLayerNames=reinterpret_cast<const char* const*>(&layer_names[0]);
		}

		TSet(ConstCharPtr) ext_names;
		TVector(VkExtensionProperties) ext_props;
		success&=(vkEnumerateInstanceExtensionProperties(nullptr,&count,nullptr)>=VK_SUCCESS);
		if(count)
		{
			ext_props.resize(count);
			success&=(vkEnumerateInstanceExtensionProperties(nullptr,&count,&ext_props[0])>=VK_SUCCESS);
			for(auto const& prop:ext_props)
			{
				ext_names.insert(prop.extensionName);
			}
		}
		for(auto const & name:layer_names)
		{
			success&=(vkEnumerateInstanceExtensionProperties(name,&count,nullptr)>=VK_SUCCESS);
			if(count)
			{
				ext_props.resize(count);
				success&=(vkEnumerateInstanceExtensionProperties(name,&count,&ext_props[0])>=VK_SUCCESS);
				for(auto const& prop:ext_props)
				{
					ext_names.insert(prop.extensionName);
				}
			}
		}
		TVector(ConstCharPtr) ext_name_array(ext_names.size());
		if(!ext_names.empty())
		{
			std::copy(ext_names.begin(),ext_names.end(),ext_name_array.begin());
			info.enabledExtensionCount=ext_name_array.size();
			info.ppEnabledExtensionNames=reinterpret_cast<const char* const*>(&ext_name_array[0]);
		}

		VkApplicationInfo app_info={};
		app_info.sType=VK_STRUCTURE_TYPE_APPLICATION_INFO;
		success&=(vkEnumerateInstanceVersion(&app_info.apiVersion)>=VK_SUCCESS);
		app_info.applicationVersion=1;
		app_info.pApplicationName="DevilX";
		info.pApplicationInfo=&app_info;

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
		success=(vkCreateInstance(&info,nullptr,&mInternal)>=VK_SUCCESS);
		if(success)
		{
			volkLoadInstance(mInternal);
		}
	}
	return success;
}

void NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::_enumPhysicalDevicesAndGroups()
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
				auto group=DEVILX_NEW IPhysicalDeviceGroupImp(i,this);
				for(uint32_t j=0; j<groups[i].physicalDeviceCount; j++)
				{
					auto dev=new NSVulkan::IPhysicalDeviceImp(groups[i].physicalDevices[j],group);
					group->addDevice(dev);
				}
				mPhysicsDeviceGroups.push_back(group);
			}
		}
	}
}

IDevice* NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::createDevice(IPhysicalDeviceGroup* deviceGroup)
{
	bool success=false;

	VkDeviceGroupDeviceCreateInfo dev_group_create_info={};
	dev_group_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO;
	dev_group_create_info.physicalDeviceCount=static_cast<IPhysicalDeviceGroupImp*>(deviceGroup)->getDeviceCount();
	TVector(VkPhysicalDevice) devs;
	devs.reserve(static_cast<IPhysicalDeviceGroupImp*>(deviceGroup)->getDeviceCount());
	for(auto dev:static_cast<IPhysicalDeviceGroupImp*>(deviceGroup)->getDevices())
	{
		devs.push_back(static_cast<IPhysicalDeviceImp*>(dev)->getInternal());
	}
	dev_group_create_info.pPhysicalDevices=&devs[0];

	uint32_t queue_family_count=0;
	vkGetPhysicalDeviceQueueFamilyProperties(devs[0],&queue_family_count,nullptr);
	TVector(VkQueueFamilyProperties) queue_family_props(queue_family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(devs[0],&queue_family_count,&queue_family_props[0]);

	TVector(float) queue_priors(256,0);
	TVector(VkDeviceQueueCreateInfo) queue_create_infos(queue_family_count);
	for(uint32_t i=0;i<queue_family_count;++i)
	{
		VkDeviceQueueCreateInfo& queue_create_info=queue_create_infos[i];
		queue_create_info={};
		queue_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_create_info.pNext=&dev_group_create_info;
		queue_create_info.queueCount=queue_family_props[i].queueCount;
		queue_create_info.queueFamilyIndex=i;
		queue_create_info.pQueuePriorities=&queue_priors[0];
	}

	VkPhysicalDeviceFeatures2 phy_dev_features={};
	vkGetPhysicalDeviceFeatures2(devs[0],&phy_dev_features);

	uint32_t dev_ext_prop_count=0;
	success&=(vkEnumerateDeviceExtensionProperties(devs[0],nullptr,&dev_ext_prop_count,nullptr)>=VK_SUCCESS);
	TVector(VkExtensionProperties) ext_props(dev_ext_prop_count);
	success&=(vkEnumerateDeviceExtensionProperties(devs[0],nullptr,&dev_ext_prop_count,&ext_props[0])>=VK_SUCCESS);
	TVector(ConstCharPtr) ext_prop_names;
	ext_prop_names.reserve(ext_props.size());
	for(auto const& prop:ext_props)
	{
		ext_prop_names.push_back(prop.extensionName);
	}

	VkDeviceCreateInfo dev_create_info={};
	dev_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	dev_create_info.pQueueCreateInfos=&queue_create_infos[0];
	dev_create_info.queueCreateInfoCount=static_cast<uint32_t>(queue_create_infos.size());
	dev_create_info.pEnabledFeatures=&phy_dev_features.features;
	if(!ext_props.empty())
	{
		dev_create_info.enabledExtensionCount=static_cast<uint32_t>(ext_props.size());
		dev_create_info.ppEnabledExtensionNames=&ext_prop_names[0];
	}

	VkDevice dev;
	success=(vkCreateDevice(devs[0],&dev_create_info,nullptr,&dev)>=VK_SUCCESS);

	IDeviceImp* ret=nullptr;
	if(success)
	{
		ret=DEVILX_NEW IDeviceImp(dev,static_cast<IPhysicalDeviceGroupImp*>(deviceGroup));
		mDevices.push_back(ret);
	}

	return ret;
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IInstanceImp::IInstanceImp(IEnum::EInstance type)
	:NSGraphicsDriver::IInstanceImp(type)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IInstanceImp::~IInstanceImp()
{
}

Boolean NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IInstanceImp::initialize()
{
	auto success = glewInit()>=0;
	if(success)
	{
		success&=eglInitialize(eglGetDisplay(EGL_DEFAULT_DISPLAY),NULL,NULL);
		eglBindAPI(EGL_OPENGL_API);
		mPhysicsDeviceGroups.push_back(DEVILX_NEW IPhysicalDeviceGroupImp(this));
	}
	return success;
}

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IInstanceImp::enumPhysicalDevices(IPhysicalDevice** outDevices)
{
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

UInt32 NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IInstanceImp::enumPhysicalDeviceGroups(IPhysicalDeviceGroup** outGroups)
{
	if(outGroups)
	{
		UInt32 index=0;
		for(auto group:mPhysicsDeviceGroups)
		{
			outGroups[index++]=group;
		}
	}
	return static_cast<UInt32>(mPhysicsDeviceGroups.size());
}

IDevice* NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IInstanceImp::createDevice(IPhysicalDeviceGroup* deviceGroup)
{
	eglCreateContext(eglGetDisplay(EGL_DEFAULT_DISPLAY),)
	return nullptr;
}
