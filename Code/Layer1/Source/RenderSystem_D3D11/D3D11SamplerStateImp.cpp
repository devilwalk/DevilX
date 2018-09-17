#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::CSamplerStateImp()
	:mInternal(nullptr)
{
	mDescription=CSystemImp::getSingleton().getDefaultSamplerStateDescription();
}

NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::~CSamplerStateImp()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::setFilter(IEnum::ESamplerFilter filter)
{
	if(getFilter()!=filter)
	{
		mDescription.Filter=CUtility::map(filter);
		mInternal=nullptr;
	}
}

IEnum::ESamplerFilter NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::getFilter() const
{
	return CUtility::map(mDescription.Filter);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::setTextureAddressModeU(IEnum::ETextureAddressMode mode)
{
	if(getTextureAddressModeU()!=mode)
	{
		mDescription.AddressU=CUtility::map(mode);
		mInternal=nullptr;
	}
}

IEnum::ETextureAddressMode NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::getTextureAddressModeU() const
{
	return CUtility::map(mDescription.AddressU);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::setTextureAddressModeV(IEnum::ETextureAddressMode mode)
{
	if(getTextureAddressModeV()!=mode)
	{
		mDescription.AddressV=CUtility::map(mode);
		mInternal=nullptr;
	}
}

IEnum::ETextureAddressMode NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::getTextureAddressModeV() const
{
	return CUtility::map(mDescription.AddressV);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::setTextureAddressModeW(IEnum::ETextureAddressMode mode)
{
	if(getTextureAddressModeW()!=mode)
	{
		mDescription.AddressW=CUtility::map(mode);
		mInternal=nullptr;
	}
}

IEnum::ETextureAddressMode NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::getTextureAddressModeW() const
{
	return CUtility::map(mDescription.AddressW);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::setMipLODBias(Float bias)
{
	if(mDescription.MipLODBias!=bias)
	{
		mDescription.MipLODBias=bias;
		mInternal=nullptr;
	}
}

Float NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::getMipLODBias() const
{
	return mDescription.MipLODBias;
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::setMaxAnisotropy(UInt32 value)
{
	if(mDescription.MaxAnisotropy!=value)
	{
		mDescription.MaxAnisotropy=value;
		mInternal=nullptr;
	}
}

UInt32 NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::getMaxAnisotropy() const
{
	return mDescription.MaxAnisotropy;
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::setComparisonFunction(IEnum::EComparisonFunction func)
{
	if(getComparisonFunction()!=func)
	{
		mDescription.ComparisonFunc=CUtility::map(func);
		mInternal=nullptr;
	}
}

IEnum::EComparisonFunction NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::getComparisonFunction() const
{
	return CUtility::map(mDescription.ComparisonFunc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::setBorderColour(const CColour & colour)
{
	mDescription.BorderColor[0]=colour.r();
	mDescription.BorderColor[1]=colour.g();
	mDescription.BorderColor[2]=colour.b();
	mDescription.BorderColor[3]=colour.a();
	mInternal=nullptr;
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::getBorderColour(OUT CColour & colour) const
{
	// TODO: 在此处插入 return 语句
	colour.setRed(mDescription.BorderColor[0]);
	colour.setGreen(mDescription.BorderColor[1]);
	colour.setBlue(mDescription.BorderColor[2]);
	colour.setAlpha(mDescription.BorderColor[3]);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::setMinLOD(Float value)
{
	if(mDescription.MinLOD!=value)
	{
		mDescription.MinLOD=value;
		mInternal=nullptr;
	}
}

Float NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::getMinLOD() const
{
	return mDescription.MinLOD;
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::setMaxLOD(Float value)
{
	if(mDescription.MaxLOD!=value)
	{
		mDescription.MaxLOD=value;
		mInternal=nullptr;
	}
}

Float NSDevilX::NSRenderSystem::NSD3D11::CSamplerStateImp::getMaxLOD() const
{
	return mDescription.MaxLOD;
}
