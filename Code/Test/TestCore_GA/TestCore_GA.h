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
		auto inst = NSDevilX::NSCore::getSystem()->getGraphicsDriverSystem()->createInstance(nullptr,0);
		NSDevilX::TVector<NSDevilX::NSCore::NSGraphicsDriver::IPhysicsDevice*> physics_devices;
		physics_devices.resize(inst->enumPhysicsDevices(nullptr));
		inst->enumPhysicsDevices(&physics_devices[0]);
	}

	NSDevilX::Void update()
	{
	}
};