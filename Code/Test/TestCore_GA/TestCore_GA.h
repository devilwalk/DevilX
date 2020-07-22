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
	}

	NSDevilX::Void update()
	{
	}
};