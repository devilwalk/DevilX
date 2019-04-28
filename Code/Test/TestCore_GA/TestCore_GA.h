#pragma once

#include "resource.h"

class CGATester
	:public NSDevilX::TSingletonEx<CGATester>
{
protected:
	NSDevilX::NSCore::IGADevice* mGADevice;
	NSDevilX::NSCore::IGASwapChain* mGASwapChain;
public:
	CGATester()
	{
	}
	~CGATester()
	{
		NSDevilX::NSCore::getSystem()->shutdown();
	}

	NSDevilX::Void initialize(HWND wnd)
	{
		mGADevice=NSDevilX::NSCore::getSystem()->getGAManager()->createDevice(NSDevilX::NSCore::IGAEnum::EDeviceVersion_OpenGL);
		NSDevilX::NSCore::IGAStruct::SGISwapChainDesc swap_chain_desc={0};
		swap_chain_desc.BufferDesc.Format=NSDevilX::NSCore::IGAEnum::EGIFormat_R8G8B8A8_UNORM_SRGB;
		swap_chain_desc.BufferUsage=NSDevilX::NSCore::IGAEnum::EGIUsage_BackBuffer|NSDevilX::NSCore::IGAEnum::EGIUsage_RenderTargetOutput;
		swap_chain_desc.OutputWindow=wnd;
		swap_chain_desc.SampleDesc.Count=1;
		swap_chain_desc.SampleDesc.Quality=0;
		mGASwapChain=NSDevilX::NSCore::getSystem()->getGAManager()->createSwapChain(mGADevice,swap_chain_desc);
	}

	NSDevilX::Void update()
	{
		NSDevilX::Float clear_rgba[]={1.0f,0,0,1.0f};
		mGADevice->getImmediateContext()->clear(mGASwapChain->getRenderTargetView(),clear_rgba);
		mGADevice->getImmediateContext()->clear(mGASwapChain->getDepthStencilView(),NSDevilX::NSCore::IGAEnum::EClearFlag_DEPTH|NSDevilX::NSCore::IGAEnum::EClearFlag_STENCIL,1.0f,0);
		mGASwapChain->present();
	}
};