#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::ITexture2DImp::SSubTexture::SSubTexture(ITexture2DImp * texture,UInt32 width,UInt32 height,UInt32 mipmapLevel,UInt32 arrayIndex)
	:mTexture(texture)
	,mWidth(width)
	,mHeight(height)
	,mMipmapLevel(mipmapLevel)
	,mArrayIndex(arrayIndex)
	,mMemoryPixels(nullptr)
	,mRenderTargetPixels(nullptr)
{}

Void NSDevilX::NSRenderSystem::ITexture2DImp::SSubTexture::setMemoryPixels(ConstVoidPtr pixels)
{
	mMemoryPixels=pixels;
	setRenderTargetPixels(nullptr);
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::SSubTexture::setRenderTargetPixels(IRenderTargetImp * target)
{
	Boolean old_enable=mRenderTargetPixels!=nullptr;
	Boolean new_enable=target!=nullptr;
	mRenderTargetPixels=target;
	mMemoryPixels=nullptr;
	if(old_enable!=new_enable)
	{
		if(new_enable)
		{
			ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_BeginRenderableSurfaceDestroy);
			ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_BeginWindowDestroy);
		}
		else
		{
			ISystemImp::getSingleton().removeListener(this,ISystemImp::EMessage_BeginRenderableSurfaceDestroy);
			ISystemImp::getSingleton().removeListener(this,ISystemImp::EMessage_BeginWindowDestroy);
		}
	}
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::SSubTexture::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_BeginRenderableSurfaceDestroy:
		if(static_cast<IRenderableSurfaceImp*>(data)==mRenderTargetPixels)
			mTexture->setPixels(static_cast<ConstVoidPtr>(nullptr),mMipmapLevel,mArrayIndex);
		break;
	case ISystemImp::EMessage_BeginWindowDestroy:
		if(static_cast<IWindowImp*>(data)==mRenderTargetPixels)
			mTexture->setPixels(static_cast<ConstVoidPtr>(nullptr),mMipmapLevel,mArrayIndex);
		break;
	}
}

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
	,mFormat(IEnum::ETexture2DFormat_R8G8B8A8)
	,mMipmapCount(-1)
	,mRealMipmapCount(-1)
	,mArraySize(1)
{
}

NSDevilX::NSRenderSystem::ITexture2DImp::~ITexture2DImp()
{
}

ITexture2DReadable * NSDevilX::NSRenderSystem::ITexture2DImp::queryInterface_ITexture2DReadable() const
{
	return const_cast<ITexture2DImp*>(this);
}

ITexture2DWritable * NSDevilX::NSRenderSystem::ITexture2DImp::queryInterface_ITexture2DWritable() const
{
	return const_cast<ITexture2DImp*>(this);
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
		mSubTextures.destroyAll();
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
		mRealMipmapCount=mMipmapCount;
		mSubTextures.destroyAll();
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
		mSubTextures.destroyAll();
		notify(EMessage_EndArraySizeChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::ITexture2DImp::getArraySize() const
{
	return mArraySize;
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::setFormat(IEnum::ETexture2DFormat format)
{
	if(getFormat()!=format)
	{
		notify(EMessage_BeginFormatChange);
		mFormat=format;
		notify(EMessage_EndFormatChange);
	}
}

IEnum::ETexture2DFormat NSDevilX::NSRenderSystem::ITexture2DImp::getFormat() const
{
	return mFormat;
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::setPixels(ConstVoidPtr pixels,UInt32 mipmapLevel,UInt32 arrayIndex)
{
	_createSubTextures();
	if(static_cast<UInt32>(-1)==mipmapLevel)
	{
		for(UInt32 mipmap_level=0;mipmap_level<=mRealMipmapCount;++mipmapLevel)
		{
			auto key=encodeSubTextureKey(mipmap_level,arrayIndex);
			const auto sub_tex=mSubTextures.get(key);
			const auto sub_pixels=reinterpret_cast<ConstVoidPtr>(reinterpret_cast<SizeT>(pixels)+getMipmapPixelByteOffset(getFormat(),mipmap_level,getWidth(),getHeight()));
			if(sub_pixels!=sub_tex->mMemoryPixels)
			{
				notify(EMessage_BeginPixelsChange,&key);
				sub_tex->setMemoryPixels(sub_pixels);
				notify(EMessage_EndPixelsChange,&key);
			}
		}
	}
	else
	{
		auto key=encodeSubTextureKey(mipmapLevel,arrayIndex);
		const auto sub_tex=mSubTextures.get(key);
		if(pixels!=sub_tex->mMemoryPixels)
		{
			notify(EMessage_BeginPixelsChange,&key);
			sub_tex->setMemoryPixels(pixels);
			notify(EMessage_EndPixelsChange,&key);
		}
	}
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::setPixels(IRenderTarget * target,UInt32 mipmapLevel,UInt32 arrayIndex)
{
	_createSubTextures();
	auto key=encodeSubTextureKey(mipmapLevel,arrayIndex);
	const auto sub_tex=mSubTextures.get(key);
	if(target!=sub_tex->mRenderTargetPixels)
	{
		notify(EMessage_BeginPixelsChange,&key);
		sub_tex->setRenderTargetPixels(static_cast<IRenderTargetImp*>(target));
		notify(EMessage_EndPixelsChange,&key);
	}
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::updatePixels(UInt32 mipmapLevel,UInt32 arrayIndex)
{
	_createSubTextures();
	if(static_cast<UInt32>(-1)==arrayIndex)
	{
		if(static_cast<UInt32>(-1)==mipmapLevel)
		{
			for(UInt32 array_index=0;array_index<getArraySize();++array_index)
			{
				for(UInt32 mipmap_level=0;mipmap_level<=mRealMipmapCount;++mipmap_level)
				{
					auto key=encodeSubTextureKey(mipmap_level,array_index);
					notify(EMessage_BeginPixelsChange,&key);
					notify(EMessage_EndPixelsChange,&key);
				}
			}
		}
		else
		{
			for(UInt32 array_index=0;array_index<getArraySize();++array_index)
			{
				auto key=encodeSubTextureKey(mipmapLevel,array_index);
				notify(EMessage_BeginPixelsChange,&key);
				notify(EMessage_EndPixelsChange,&key);
			}
		}
	}
	else
	{
		auto key=encodeSubTextureKey(mipmapLevel,arrayIndex);
		notify(EMessage_BeginPixelsChange,&key);
		notify(EMessage_EndPixelsChange,&key);
	}
}

ConstVoidPtr NSDevilX::NSRenderSystem::ITexture2DImp::getPixels(UInt32 mipmapLevel,UInt32 arrayIndex) const
{
	const auto key=encodeSubTextureKey(mipmapLevel,arrayIndex);
	const SSubTexture * const sub_tex=mSubTextures.get(key);
	return sub_tex?sub_tex->mMemoryPixels:nullptr;
}

Void NSDevilX::NSRenderSystem::ITexture2DImp::_createSubTextures()
{
	mRealMipmapCount=-1;
	if((getWidth()==0)
		||(getHeight()==0)
		||(getArraySize()==0)
		||(!mSubTextures.empty())
		)
		return;
	for(UInt32 array_index=0;array_index<getArraySize();++array_index)
	{
		auto looper=std::max<>(getWidth(),getHeight());
		auto next_width=getWidth();
		auto next_height=getHeight();
		UInt32 mipmap_level=0;
		while(looper)
		{
			mSubTextures.add(encodeSubTextureKey(mipmap_level,array_index),DEVILX_NEW SSubTexture(this,next_width,next_height,mipmap_level,array_index));
			next_width>>=1;
			next_width=std::max<UInt32>(next_width,1);
			next_height>>=1;
			next_height=std::max<UInt32>(next_height,1);
			++mipmap_level;
			looper>>=1;
		}
		mRealMipmapCount=mipmap_level-1;
	}
}
