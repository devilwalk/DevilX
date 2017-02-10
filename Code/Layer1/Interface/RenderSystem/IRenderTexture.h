#pragma once
#include "IRenderTarget.h"
#include "IRenderEnum.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITexture2DReadable
		{
		protected:
			virtual ~ITexture2DReadable(){}
		public:
			virtual IEnum::ETexture2DFormat getFormat()const=0;
			virtual UInt32 getMipmapCount()const=0;
			virtual UInt32 getWidth()const=0;
			virtual UInt32 getHeight()const=0;
			virtual UInt32 getArraySize()const=0;
			virtual ConstVoidPtr getPixels(UInt32 mipmapLevel=0,UInt32 arrayIndex=0)const=0;
		};
		class ITexture2DWritable
		{
		protected:
			virtual ~ITexture2DWritable(){}
		public:
			virtual Void setFormat(IEnum::ETexture2DFormat format)=0;
			virtual Void setMipmapCount(UInt32 count=-1)=0;
			virtual Void setSize(UInt32 width,UInt32 height)=0;
			virtual Void setArraySize(UInt32 size)=0;
			virtual Void setPixels(ConstVoidPtr pixels,UInt32 mipmapLevel=-1,UInt32 arrayIndex=0)=0;
			virtual Void setPixels(IRenderTarget * target,UInt32 mipmapLevel=0,UInt32 arrayIndex=0)=0;
			virtual Void updatePixels(UInt32 mipmapLevel=-1,UInt32 arrayIndex=-1)=0;
		};
		class ITexture
		{
		protected:
			virtual ~ITexture(){}
		public:
			virtual ITexture2DReadable * queryInterface_ITexture2DReadable()const=0;
			virtual ITexture2DWritable * queryInterface_ITexture2DWritable()const=0;
			virtual IEnum::ETextureType getType()const=0;
			virtual const String & getName()const=0;
		};
	}
}