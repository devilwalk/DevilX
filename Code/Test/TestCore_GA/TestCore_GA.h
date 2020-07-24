#pragma once

#include "resource.h"

class CGATester
	:public NSDevilX::TSingletonEx<CGATester>
{
protected:
public:
	CGATester()
	{
	}
	~CGATester()
	{
	}

	NSDevilX::Void initialize(HWND wnd)
	{
		auto instance_major_type=NSDevilX::NSCore::NSGraphicsDriver::IEnum::EInstanceMajorType_GL;
		auto instance_minor_type=NSDevilX::NSCore::NSGraphicsDriver::IEnum::EInstanceMinorType_GL_4_5;
		auto inst=NSDevilX::NSCore::getSystem()->getGraphicsDriverSystem()->createInstance(instance_major_type,instance_minor_type);
		NSDevilX::TVector<NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceGroup*> physics_device_groups;
		physics_device_groups.resize(inst->enumPhysicalDeviceGroups(nullptr));
		inst->enumPhysicalDeviceGroups(&physics_device_groups[0]);
		auto dev=inst->createDevice(physics_device_groups[0]);
		auto queu_3d=dev->createQueue(NSDevilX::NSCore::NSGraphicsDriver::IEnum::EQueue_3D);
		DXGI_SWAP_CHAIN_DESC1 desc={};
		desc.BufferCount=2;
		desc.BufferUsage=DXGI_USAGE_BACK_BUFFER|DXGI_USAGE_RENDER_TARGET_OUTPUT|DXGI_USAGE_DISCARD_ON_PRESENT;
		desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		desc.SampleDesc.Count=1;
		desc.SwapEffect=DXGI_SWAP_EFFECT_FLIP_DISCARD;
		queu_3d->createSwapChain(wnd,desc);
	}

	NSDevilX::Void update()
	{
	}
};