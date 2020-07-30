#pragma once

#include "resource.h"

class CGATester
	:public NSDevilX::TSingletonEx<CGATester>
{
protected:
	NSDevilX::NSCore::NSGraphicsDriver::IDevice* mDevice;
	NSDevilX::NSCore::NSGraphicsDriver::IQueue* m3DQueue;
	NSDevilX::NSCore::NSGraphicsDriver::ISwapChain* mSwapChain;
public:
	CGATester()
		:mDevice(nullptr)
		,m3DQueue(nullptr)
		,mSwapChain(nullptr)
	{
	}
	~CGATester()
	{
	}

	NSDevilX::Void initialize(HWND wnd)
	{
		auto instance_major_type=NSDevilX::NSCore::NSGraphicsDriver::IEnum::EInstanceMajorType_D3D;
		auto instance_minor_type=NSDevilX::NSCore::NSGraphicsDriver::IEnum::EInstanceMinorType_D3D_12_1;
		auto inst=NSDevilX::NSCore::getSystem()->getGraphicsDriverSystem()->createInstance(instance_major_type,instance_minor_type);
		NSDevilX::TVector<NSDevilX::NSCore::NSGraphicsDriver::IPhysicalDeviceGroup*> physics_device_groups;
		physics_device_groups.resize(inst->enumPhysicalDeviceGroups(nullptr));
		inst->enumPhysicalDeviceGroups(&physics_device_groups[0]);
		mDevice=inst->createDevice(physics_device_groups[0]);
		m3DQueue=mDevice->getQueue(NSDevilX::NSCore::NSGraphicsDriver::IEnum::EQueue_3D,0);
		DXGI_SWAP_CHAIN_DESC1 desc={};
		desc.BufferCount=2;
		desc.BufferUsage=DXGI_USAGE_BACK_BUFFER|DXGI_USAGE_RENDER_TARGET_OUTPUT|DXGI_USAGE_DISCARD_ON_PRESENT;
		desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		desc.SampleDesc.Count=1;
		desc.SwapEffect=DXGI_SWAP_EFFECT_FLIP_DISCARD;
		mSwapChain=m3DQueue->createSwapChain(wnd,desc);
	}

	NSDevilX::Void update()
	{
		mSwapChain->swapBuffers();
	}
};