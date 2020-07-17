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
		NSDevilX::NSCore::NSGraphicsDriver::IEnum::EInstance instance_type=NSDevilX::NSCore::NSGraphicsDriver::IEnum::EInstance_D3D11_0;
		auto inst = NSDevilX::NSCore::getSystem()->getGraphicsDriverSystem()->createInstance(&instance_type,1);
		NSDevilX::TVector<NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceGroup*> physics_device_groups;
		physics_device_groups.resize(inst->enumPhysicalDeviceGroups(nullptr));
		inst->enumPhysicalDeviceGroups(&physics_device_groups[0]);
		auto dev=inst->createDevice(physics_device_groups[0]);
		auto queu_3d=dev->createQueue(NSDevilX::NSCore::NSGraphicsDriver::IEnum::EQueue_3D);
	}

	NSDevilX::Void update()
	{
	}
};