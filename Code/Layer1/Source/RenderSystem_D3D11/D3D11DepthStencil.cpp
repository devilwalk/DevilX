#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CDepthStencil::CDepthStencil(UInt32 width,UInt32 height)
	:mTextureResource(nullptr)
	,mLocked(0)
{
	D3D11_TEXTURE2D_DESC desc;
	desc.ArraySize=1;
	desc.BindFlags=D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags=0;
	desc.Format=DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.Height=height;
	desc.MipLevels=1;
	desc.MiscFlags=0;
	desc.SampleDesc.Count=1;
	desc.SampleDesc.Quality=0;
	desc.Usage=D3D11_USAGE_DEFAULT;
	desc.Width=width;
	CSystemImp::getSingleton().getDevice()->CreateTexture2D(&desc,nullptr,&mTextureResource);
	decltype(getInternal()) temp_internal=nullptr;
	CSystemImp::getSingleton().getDevice()->CreateDepthStencilView(mTextureResource,nullptr,&temp_internal);
	setInternal(temp_internal);
}

NSDevilX::NSRenderSystem::NSD3D11::CDepthStencil::~CDepthStencil()
{
	if(mTextureResource)
		mTextureResource->Release();
}