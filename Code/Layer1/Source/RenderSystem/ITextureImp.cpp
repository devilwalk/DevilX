#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::ITextureImp::ITextureImp(const String & name)
	:mName(name)
{}

NSDevilX::NSRenderSystem::ITextureImp::~ITextureImp()
{}

const String & NSDevilX::NSRenderSystem::ITextureImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

NSDevilX::NSRenderSystem::ITexture2DImp::ITexture2DImp(const String & name)
	:ITextureImp(name)
	,mWidth(0)
	,mHeight(0)
	,mFormat(IEnum::ETextureFormat_R8G8B8A8)
	,mMipmapCount(-1)
	,mArraySize(1)
	,mPixels(nullptr)
{
}

NSDevilX::NSRenderSystem::ITexture2DImp::~ITexture2DImp()
{
}

IRenderTarget * NSDevilX::NSRenderSystem::ITexture2DImp::queryInterface_IRenderTarget(UInt32 mipmapLevel,UInt32 arrayIndex) const
{
	assert(0);
	return nullptr;
}

ITexture2D * NSDevilX::NSRenderSystem::ITexture2DImp::queryInterface_ITexture2D() const
{
	return const_cast<ITexture2DImp*>(this);
}

ITextureCube * NSDevilX::NSRenderSystem::ITexture2DImp::queryInterface_ITextureCube() const
{
	return nullptr;
}

IEnum::ETextureType NSDevilX::NSRenderSystem::ITexture2DImp::getType() const
{
	return IEnum::ETextureType_2D;
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::setSize(UInt32 width,UInt32 height)
{
	if(getWidth()!=width||getHeight()!=height)
	{
		notify(EMessage_BeginSizeChange);
		mWidth=width;
		mHeight=height;
		addDirtyFlag(EDirtyFlag_Size);
		notify(EMessage_EndSizeChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::ITexture2DImp::getWidth() const
{
	return mWidth;
}

UInt32 NSDevilX::NSRenderSystem::ITexture2DImp::getHeight() const
{
	return mHeight;
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::setMipmapCount(UInt32 count)
{
	if(getMipmapCount()!=count)
	{
		notify(EMessage_BeginMipmapChange);
		mMipmapCount=count;
		addDirtyFlag(EDirtyFlag_Mipmap);
		notify(EMessage_EndMipmapChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::ITexture2DImp::getMipmapCount() const
{
	return mMipmapCount;
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::setArraySize(UInt32 size)
{
	size=std::min<UInt32>(size,1);
	if(size!=getArraySize())
	{
		notify(EMessage_BeginArraySizeChange);
		mArraySize=size;
		addDirtyFlag(EDirtyFlag_ArraySize);
		notify(EMessage_EndArraySizeChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::ITexture2DImp::getArraySize() const
{
	return mArraySize;
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::setFormat(IEnum::ETextureFormat format)
{
	if(getFormat()!=format)
	{
		notify(EMessage_BeginFormatChange);
		mFormat=format;
		addDirtyFlag(EDirtyFlag_Format);
		notify(EMessage_EndFormatChange);
	}
}

IEnum::ETextureFormat NSDevilX::NSRenderSystem::ITexture2DImp::getFormat() const
{
	return mFormat;
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::setPixels(ConstVoidPtr pixels,UInt32 arrayIndex)
{
	if(getPixels()!=pixels)
	{
		notify(EMessage_BeginPixelsChange);
		mPixels=pixels;
		addDirtyFlag(EDirtyFlag_Pixels);
		notify(EMessage_EndPixelsChange);
	}
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::updatePixels()
{
	addDirtyFlag(EDirtyFlag_Pixels);
}

ConstVoidPtr NSDevilX::NSRenderSystem::ITexture2DImp::getPixels(UInt32 arrayIndex) const
{
	return mPixels;
}