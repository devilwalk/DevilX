#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CTexture1DImp::CTexture1DImp()
{
}

NSDevilX::NSRenderSystem::NSD3D11::CTexture1DImp::~CTexture1DImp()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CTexture1DImp::initialize(UInt32 width,UInt32 mipLevels,IEnum::ETexture1DFormat fmt,UInt32 flag,UInt32 arraySize)
{
	CTexture1D::initialize(width,mipLevels,fmt,flag,arraySize);
	D3D11_TEXTURE1D_DESC desc;
	ZeroMemory(&desc,sizeof(desc));
	desc.ArraySize=mArraySize;
	desc.Format=CUtility::getDXGIFormat(fmt);
	desc.MipLevels=mipLevels;
	desc.Width=mWidth;
	if(IEnum::EAccessFlag_GPURead&flag)
	{
		desc.BindFlags|=D3D11_BIND_SHADER_RESOURCE;
	}
	if(IEnum::EAccessFlag_CPUWrite&flag)
	{
		desc.CPUAccessFlags|=D3D11_CPU_ACCESS_WRITE;
		desc.Usage=D3D11_USAGE_DYNAMIC;
	}
	else
	{
		desc.Usage=D3D11_USAGE_DEFAULT;
	}
	ID3D11Texture1D * tex=nullptr;
	CSystemImp::getSingleton().getDevice()->CreateTexture1D(&desc,nullptr,&tex);
	setInternal(tex);
}

NSDevilX::NSRenderSystem::NSD3D11::CTexture2DImp::CTexture2DImp()
{
}

NSDevilX::NSRenderSystem::NSD3D11::CTexture2DImp::~CTexture2DImp()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CTexture2DImp::initialize(UInt32 width,UInt32 height,UInt32 mipLevels,IEnum::ETexture2DFormat fmt,UInt32 flag,UInt32 arraySize)
{
	CTexture2D::initialize(width,height,mipLevels,fmt,flag,arraySize);
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc,sizeof(desc));
	desc.ArraySize=mArraySize;
	desc.Format=CUtility::getDXGIFormat(fmt);
	desc.MipLevels=mipLevels;
	desc.Width=mWidth;
	desc.Height=mHeight;
	if(IEnum::EAccessFlag_GPURead&flag)
	{
		desc.BindFlags|=D3D11_BIND_SHADER_RESOURCE;
	}
	if(IEnum::EAccessFlag_CPUWrite&flag)

	{
		desc.CPUAccessFlags|=D3D11_CPU_ACCESS_WRITE;
		desc.Usage=D3D11_USAGE_DYNAMIC;
	}
	else
	{
		desc.Usage=D3D11_USAGE_DEFAULT;
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CTexture3DImp::CTexture3DImp()
{
}

NSDevilX::NSRenderSystem::NSD3D11::CTexture3DImp::~CTexture3DImp()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CTexture3DImp::initialize(UInt32 width,UInt32 height,UInt32 depth,UInt32 mipLevels,IEnum::ETexture3DFormat fmt,UInt32 flag)
{
	CTexture3D::initialize(width,height,depth,mipLevels,fmt,flag);
}
