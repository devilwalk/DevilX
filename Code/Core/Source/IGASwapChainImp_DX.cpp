#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;

NSDevilX::NSCore::NSDirectX::IGASwapChainImp::IGASwapChainImp(ID3D11Device * dev,DXGI_SWAP_CHAIN_DESC && desc)
	:mRenderTargetView11(nullptr)
	,mDepthStencilView11(nullptr)
{
	CGAManager::getSingleton().getFactory()->CreateSwapChain(dev,&desc,&mInternal);
	mInternal->GetBuffer(0,__uuidof(mBackBuffer11),reinterpret_cast<VoidPtr*>(&mBackBuffer11));
	mRenderTargetView11.reset(DEVILX_NEW NSVersion11::IGARenderTargetViewImp(dev,mBackBuffer11,nullptr));
	D3D11_TEXTURE2D_DESC rt_desc={0};
	mBackBuffer11->GetDesc(&rt_desc);
	D3D11_TEXTURE2D_DESC ds_desc={0};
	ds_desc.ArraySize=1;
	ds_desc.BindFlags=D3D11_BIND_DEPTH_STENCIL|D3D11_BIND_SHADER_RESOURCE;
	ds_desc.Format=DXGI_FORMAT_R24G8_TYPELESS;
	ds_desc.Height=rt_desc.Height;
	ds_desc.MipLevels=1;
	ds_desc.SampleDesc.Count=1;
	ds_desc.Width=rt_desc.Width;
	dev->CreateTexture2D(&ds_desc,nullptr,&mDepthStencil11);
	D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;
	dsv_desc.Flags=0;
	dsv_desc.Format=DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsv_desc.ViewDimension=D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv_desc.Texture2D.MipSlice=0;
	mDepthStencilView11.reset(DEVILX_NEW NSVersion11::IGADepthStencilViewImp(dev,mDepthStencil11,&dsv_desc));
}

NSDevilX::NSCore::NSDirectX::IGASwapChainImp::~IGASwapChainImp()
{
}

IGARenderTargetView * NSDevilX::NSCore::NSDirectX::IGASwapChainImp::getRenderTargetView() const
{
	return mRenderTargetView11.get();
}

IGADepthStencilView * NSDevilX::NSCore::NSDirectX::IGASwapChainImp::getDepthStencilView() const
{
	return mDepthStencilView11.get();
}

Void NSDevilX::NSCore::NSDirectX::IGASwapChainImp::present()
{
	mInternal->Present(0,0);
}
