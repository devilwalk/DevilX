#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;

NSDevilX::NSCore::NSDirectX::IGASwapChainImp::IGASwapChainImp(ID3D11Device * dev,DXGI_SWAP_CHAIN_DESC && desc)
{
	CGAManager::getSingleton().getFactory()->CreateSwapChain(dev,&desc,&mInternal);
	CComPtr<IDXGISwapChain2> swap_chain;
	mInternal->QueryInterface<IDXGISwapChain2>(&swap_chain);
	swap_chain->SetMaximumFrameLatency(1);
	mInternal->GetBuffer(0,__uuidof(mBackBuffer11),reinterpret_cast<VoidPtr*>(&mBackBuffer11));
	dev->CreateRenderTargetView(mBackBuffer11,nullptr,&mRenderTargetView11);
	D3D11_TEXTURE2D_DESC rt_desc={0};
	mBackBuffer11->GetDesc(&rt_desc);
	D3D11_TEXTURE2D_DESC ds_desc={0};
	ds_desc.ArraySize=1;
	ds_desc.BindFlags=D3D11_BIND_DEPTH_STENCIL|D3D11_BIND_SHADER_RESOURCE;
	ds_desc.Format=DXGI_FORMAT_D24_UNORM_S8_UINT;
	ds_desc.Height=rt_desc.Height;
	ds_desc.MipLevels=1;
	ds_desc.SampleDesc.Count=1;
	ds_desc.Width=rt_desc.Width;
	dev->CreateTexture2D(&ds_desc,nullptr,&mDepthStencil11);
	dev->CreateDepthStencilView(mDepthStencil11,nullptr,&mDepthStencilView11);
}

NSDevilX::NSCore::NSDirectX::IGASwapChainImp::~IGASwapChainImp()
{
}

IGARenderTargetView * NSDevilX::NSCore::NSDirectX::IGASwapChainImp::getRenderTargetView() const
{
	return const_cast<IGASwapChainImp*>(this);
}

IGADepthStencilView * NSDevilX::NSCore::NSDirectX::IGASwapChainImp::getDepthStencilView() const
{
	return const_cast<IGASwapChainImp*>(this);
}

Void NSDevilX::NSCore::NSDirectX::IGASwapChainImp::present()
{
	mInternal->Present(0,0);
}
