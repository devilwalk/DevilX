#include "../Precompiler.h"
#include "volk.c"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IInstanceImp::IInstanceImp(IEnum::EInstanceMajorType majorType,Int32 minorType)
	:mMajorType(majorType)
	,mMinorType(minorType)
{
}

NSDevilX::NSCore::NSGraphicsDriver::IInstanceImp::~IInstanceImp()
{
	mDevices.destroyAll();
	mPhysicsDeviceGroups.destroyAll();
}

NSGraphicsDriver::IEnum::EInstanceMajorType NSDevilX::NSCore::NSGraphicsDriver::IInstanceImp::getMajorType() const
{
	return mMajorType;
}

Int32 NSDevilX::NSCore::NSGraphicsDriver::IInstanceImp::getMinorType() const
{
	return mMinorType;
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D::IInstanceImp::IInstanceImp(IEnum::EInstanceMinorType_D3D minorType)
	:NSGraphicsDriver::IInstanceImp(IEnum::EInstanceMajorType_D3D,minorType)
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
#if DEVILX_DEBUG
	switch(mMinorType)
	{
	case IEnum::EInstanceMinorType_D3D_12_1:
	case IEnum::EInstanceMinorType_D3D_12_0:
	{
		D3D12GetDebugInterface(__uuidof(mDebug),reinterpret_cast<VoidPtr*>(&mDebug));
		mDebug->EnableDebugLayer();
		CComPtr<ID3D12Debug1> debug1;
		mDebug->QueryInterface(&debug1);
		if(debug1.p)
		{
			debug1->SetEnableGPUBasedValidation(TRUE);
			debug1->SetEnableSynchronizedCommandQueueValidation(TRUE);
		}
	}
		break;
	}
#endif
	Boolean success=false;
	if(success=SUCCEEDED(CreateDXGIFactory1(__uuidof(mInternal7),reinterpret_cast<void**>(&mInternal7))))
	{
		mInternal=mInternal1=mInternal2=mInternal3=mInternal4=mInternal5=mInternal6=mInternal7;
	}
	else if(success=SUCCEEDED(CreateDXGIFactory1(__uuidof(mInternal6),reinterpret_cast<void**>(&mInternal6))))
	{
		mInternal=mInternal1=mInternal2=mInternal3=mInternal4=mInternal5=mInternal6;
	}
	else if(success=SUCCEEDED(CreateDXGIFactory1(__uuidof(mInternal5),reinterpret_cast<void**>(&mInternal5))))
	{
		mInternal=mInternal1=mInternal2=mInternal3=mInternal4=mInternal5;
	}
	else if(success=SUCCEEDED(CreateDXGIFactory1(__uuidof(mInternal4),reinterpret_cast<void**>(&mInternal4))))
	{
		mInternal=mInternal1=mInternal2=mInternal3=mInternal4;
	}
	else if(success=SUCCEEDED(CreateDXGIFactory1(__uuidof(mInternal3),reinterpret_cast<void**>(&mInternal3))))
	{
		mInternal=mInternal1=mInternal2=mInternal3;
	}
	else if(success=SUCCEEDED(CreateDXGIFactory1(__uuidof(mInternal2),reinterpret_cast<void**>(&mInternal2))))
	{
		mInternal=mInternal1=mInternal2;
	}
	else if(success=SUCCEEDED(CreateDXGIFactory1(__uuidof(mInternal1),reinterpret_cast<void**>(&mInternal1))))
	{
		mInternal=mInternal1;
	}
	else if(success=SUCCEEDED(CreateDXGIFactory1(__uuidof(mInternal),reinterpret_cast<void**>(&mInternal))))
	{

	}
	else
	{
		success=SUCCEEDED(CreateDXGIFactory(__uuidof(mInternal),reinterpret_cast<void**>(&mInternal)));
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
			DXGI_ADAPTER_DESC desc={};
			adapter->GetDesc(&desc);
			auto group=DEVILX_NEW NSD3D::IPhysicalDeviceGroupImp(adapter,this);
			NSGraphicsDriver::IPhysicalDeviceImp* dev=nullptr;
			switch(mMinorType)
			{
			case IEnum::EInstanceMinorType_D3D_12_1:
			case IEnum::EInstanceMinorType_D3D_12_0:
				dev=DEVILX_NEW NSD3D12::IPhysicalDeviceImp(0,group);
				break;
			case IEnum::EInstanceMinorType_D3D_11_1:
			case IEnum::EInstanceMinorType_D3D_11_0:
			case IEnum::EInstanceMinorType_D3D_10_1:
			case IEnum::EInstanceMinorType_D3D_10_0:
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
	switch(mMinorType)
	{
	case IEnum::EInstanceMinorType_D3D_12_1:
	case IEnum::EInstanceMinorType_D3D_12_0:
		ret=_createDevice12(static_cast<IPhysicalDeviceGroupImp*>(deviceGroup));
		break;
	case IEnum::EInstanceMinorType_D3D_11_1:
	case IEnum::EInstanceMinorType_D3D_11_0:
		ret=_createDevice11(static_cast<IPhysicalDeviceGroupImp*>(deviceGroup));
		break;
	case IEnum::EInstanceMinorType_D3D_10_1:
	case IEnum::EInstanceMinorType_D3D_10_0:
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
	D3D_FEATURE_LEVEL levels[]=
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	Boolean success=false;
	for(auto level:levels)
	{
		success=SUCCEEDED(D3D12CreateDevice(static_cast<IPhysicalDeviceGroupImp*>(deviceGroup)->getInternal1(),level,__uuidof(dev),reinterpret_cast<VoidPtr*>(&dev)));
		if(success)
			break;
	}
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
	auto success=SUCCEEDED(D3D11CreateDevice(static_cast<IPhysicalDeviceGroupImp*>(deviceGroup)->getInternal(),D3D_DRIVER_TYPE_UNKNOWN,NULL
		,flag,levels,_countof(levels),D3D11_SDK_VERSION,&dev,&o_level,nullptr));
	IDeviceImp* ret=nullptr;
	if(success)
	{
		ret=DEVILX_NEW NSD3D11::IDeviceImp(dev,static_cast<IPhysicalDeviceGroupImp*>(deviceGroup));
	}
	return ret;
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::IInstanceImp()
	:NSGraphicsDriver::IInstanceImp(IEnum::EInstanceMajorType_Vulkan,-1)
	,mInternal(VK_NULL_HANDLE)
#if DEVILX_DEBUG
	,mDebugReportCallback(0)
#endif
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IInstanceImp::~IInstanceImp()
{
	if(mInternal!=VK_NULL_HANDLE)
	{
#if DEVILX_DEBUG
		vkDestroyDebugReportCallbackEXT(mInternal,mDebugReportCallback,nullptr);
#endif
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
		TVector<VkLayerProperties> layer_props;
		layer_props.resize(count);
		success&=(vkEnumerateInstanceLayerProperties(&count,&layer_props[0])>=VK_SUCCESS);
		TVector<ConstCharPtr> layer_names;
		layer_names.reserve(count);
		for(auto const& prop:layer_props)
		{
			//layer_names.push_back(prop.layerName);
		}
		layer_names.push_back("VK_LAYER_LUNARG_standard_validation");
		layer_names.push_back("VK_LAYER_KHRONOS_validation");
		if(!layer_names.empty())
		{
			info.enabledLayerCount=static_cast<uint32_t>(layer_names.size());
			info.ppEnabledLayerNames=reinterpret_cast<const char* const*>(&layer_names[0]);
		}

		TMap<String,VkExtensionProperties> ext_props_table;
		TVector<VkExtensionProperties> ext_props;
		success&=(vkEnumerateInstanceExtensionProperties(nullptr,&count,nullptr)>=VK_SUCCESS);
		if(count)
		{
			ext_props.resize(count);
			success&=(vkEnumerateInstanceExtensionProperties(nullptr,&count,&ext_props[0])>=VK_SUCCESS);
			for(auto const& prop:ext_props)
			{
				ext_props_table[prop.extensionName].specVersion=prop.specVersion;
				strcpy_s(ext_props_table[prop.extensionName].extensionName,prop.extensionName);
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
					ext_props_table[prop.extensionName].specVersion=prop.specVersion;
					strcpy_s(ext_props_table[prop.extensionName].extensionName,prop.extensionName);
				}
			}
		}
		TVector<ConstCharPtr> ext_names;
		if(!ext_props_table.empty())
		{
			ext_names.reserve(ext_props_table.size());
			for(auto const & pair:ext_props_table)
			{
				ext_names.push_back(pair.second.extensionName);
			}
			info.enabledExtensionCount=static_cast<uint32_t>(ext_names.size());
			info.ppEnabledExtensionNames=reinterpret_cast<const char* const*>(&ext_names[0]);
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
#if DEVILX_DEBUG
			VkDebugReportCallbackCreateInfoEXT debug_report_callback_create_info={};
			debug_report_callback_create_info.sType=VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
			debug_report_callback_create_info.flags=VK_DEBUG_REPORT_INFORMATION_BIT_EXT|VK_DEBUG_REPORT_WARNING_BIT_EXT
				|VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT|VK_DEBUG_REPORT_ERROR_BIT_EXT|VK_DEBUG_REPORT_DEBUG_BIT_EXT;
			debug_report_callback_create_info.pUserData=this;
			debug_report_callback_create_info.pfnCallback=[](
				VkDebugReportFlagsEXT                       flags,
				VkDebugReportObjectTypeEXT                  objectType,
				uint64_t                                    object,
				size_t                                      location,
				int32_t                                     messageCode,
				const char* pLayerPrefix,
				const char* pMessage,
				void* pUserData)
			{
#ifdef _MSC_VER
				if(flags!=VK_DEBUG_REPORT_INFORMATION_BIT_EXT)
				{
					OutputDebugStringA("DevilX Vulkan Message:--------------------------------------------------------\n");
					OutputDebugStringA(pLayerPrefix);
					OutputDebugStringA("\n");
					OutputDebugStringA(pMessage);
					OutputDebugStringA("\n");
					OutputDebugStringA("DevilX Vulkan Message:========================================================\n");
				}
#endif
				return static_cast<VkBool32>(VK_FALSE);
			};
			success=VK_SUCCESS==vkCreateDebugReportCallbackEXT(mInternal,&debug_report_callback_create_info,nullptr,&mDebugReportCallback);
#endif
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
		TVector<VkPhysicalDeviceGroupProperties> groups;
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
					auto dev=new NSVulkan::IPhysicalDeviceImp(groups[i].physicalDevices[j],group,j);
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
	TVector<VkPhysicalDevice> devs;
	devs.reserve(static_cast<IPhysicalDeviceGroupImp*>(deviceGroup)->getDeviceCount());
	for(auto dev:static_cast<IPhysicalDeviceGroupImp*>(deviceGroup)->getDevices())
	{
		devs.push_back(static_cast<IPhysicalDeviceImp*>(dev)->getInternal());
	}
	dev_group_create_info.pPhysicalDevices=&devs[0];

	uint32_t queue_family_count=0;
	vkGetPhysicalDeviceQueueFamilyProperties(devs[0],&queue_family_count,nullptr);
	TVector<VkQueueFamilyProperties> queue_family_props(queue_family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(devs[0],&queue_family_count,&queue_family_props[0]);

	TVector<float> queue_priors(256,0);
	TVector<VkDeviceQueueCreateInfo> queue_create_infos(queue_family_count);
	for(uint32_t i=0;i<queue_family_count;++i)
	{
		VkDeviceQueueCreateInfo& queue_create_info=queue_create_infos[i];
		queue_create_info={};
		queue_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_create_info.queueCount=queue_family_props[i].queueCount;
		queue_create_info.queueFamilyIndex=i;
		queue_create_info.pQueuePriorities=&queue_priors[0];
	}

	VkPhysicalDeviceFeatures2 phy_dev_features={};
	phy_dev_features.sType=VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	vkGetPhysicalDeviceFeatures2(devs[0],&phy_dev_features);

	uint32_t dev_ext_prop_count=0;
	success&=(vkEnumerateDeviceExtensionProperties(devs[0],nullptr,&dev_ext_prop_count,nullptr)>=VK_SUCCESS);
	TVector<VkExtensionProperties> ext_props(dev_ext_prop_count);
	success&=(vkEnumerateDeviceExtensionProperties(devs[0],nullptr,&dev_ext_prop_count,&ext_props[0])>=VK_SUCCESS);
	TSet<ConstCharPtr> ext_prop_name_sets;
	for(auto const& prop:ext_props)
	{
		ext_prop_name_sets.insert(prop.extensionName);
	}
	TVector<ConstCharPtr> ext_prop_names(ext_prop_name_sets.size());
	std::copy(ext_prop_name_sets.begin(),ext_prop_name_sets.end(),ext_prop_names.begin());

	VkDeviceCreateInfo dev_create_info={};
	dev_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	dev_create_info.pQueueCreateInfos=&queue_create_infos[0];
	dev_create_info.queueCreateInfoCount=static_cast<uint32_t>(queue_create_infos.size());
	dev_create_info.pEnabledFeatures=&phy_dev_features.features;
	dev_create_info.pNext=&dev_group_create_info;
	if(!ext_prop_names.empty())
	{
		dev_create_info.enabledExtensionCount=static_cast<uint32_t>(ext_prop_names.size());
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

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IInstanceImp::IInstanceImp(IEnum::EInstanceMinorType_GL minorType)
	:NSGraphicsDriver::IInstanceImp(IEnum::EInstanceMajorType_GL,minorType)
	,mDisplay(EGL_NO_DISPLAY)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IInstanceImp::~IInstanceImp()
{
	eglTerminate(mDisplay);
}

Boolean NSDevilX::NSCore::NSGraphicsDriver::NSOpenGL::IInstanceImp::initialize()
{
	mDisplay=eglGetDisplay(EGL_DEFAULT_DISPLAY);
	auto success=eglInitialize(mDisplay,NULL,NULL)==EGL_TRUE;
	success&=eglBindAPI(EGL_OPENGL_API)==EGL_TRUE;
	mPhysicsDeviceGroups.push_back(DEVILX_NEW IPhysicalDeviceGroupImp(this));
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
	TVector<EGLint> config_attrs;
	if(mMinorType<=IEnum::EInstanceMinorType_GL_2_0)
	{
		config_attrs.push_back(EGL_RENDERABLE_TYPE);
		config_attrs.push_back(EGL_OPENGL_BIT);
	}
	else
	{
		config_attrs.push_back(EGL_RENDERABLE_TYPE);
		config_attrs.push_back(EGL_OPENGL_ES_BIT);
	}
	config_attrs.push_back(EGL_SURFACE_TYPE);
	config_attrs.push_back(EGL_WINDOW_BIT);
	config_attrs.push_back(EGL_NONE);
	EGLConfig config=0;
	EGLint num_config=0;
	if(EGL_TRUE!=eglChooseConfig(mDisplay,&config_attrs[0],&config,1,&num_config))
		return nullptr;
	EGLint major_version=2;
	EGLint minor_version=0;
	if(mMinorType<=IEnum::EInstanceMinorType_GL_4_0)
	{
		major_version=4;
		minor_version=IEnum::EInstanceMinorType_GL_4_0-mMinorType;
	}
	else if(mMinorType<=IEnum::EInstanceMinorType_GL_3_0)
	{
		major_version=3;
		minor_version=IEnum::EInstanceMinorType_GL_3_0-mMinorType;
	}
	else if(mMinorType<=IEnum::EInstanceMinorType_GL_2_0)
	{
		major_version=2;
		minor_version=0;
	}
	else if(mMinorType<=IEnum::EInstanceMinorType_GL_ES3_0)
	{
		major_version=3;
		minor_version=IEnum::EInstanceMinorType_GL_ES3_0-mMinorType;
	}
	else if(mMinorType<=IEnum::EInstanceMinorType_GL_ES2_0)
	{
		major_version=2;
		minor_version=0;
	}
	const EGLint context_attr[]={
		EGL_CONTEXT_MAJOR_VERSION,major_version,
		EGL_CONTEXT_MINOR_VERSION,minor_version,
#ifdef DEVILX_DEBUG
		EGL_CONTEXT_OPENGL_DEBUG,EGL_TRUE,
#endif
		EGL_NONE
	};
	auto context=eglCreateContext(mDisplay,config,EGL_NO_CONTEXT,context_attr);
	auto ret=DEVILX_NEW IDeviceImp(context,static_cast<IPhysicalDeviceGroupImp*>(deviceGroup));
	mDevices.push_back(ret);
	return ret;
}
