#pragma once
#include "IRenderTarget.h"
#include "IRenderEnum.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITexture2D
		{
		protected:
			virtual ~ITexture2D(){}
		public:
			virtual IRenderTarget * queryInterface_IRenderTarget(UInt32 mipmapLevel=0,UInt32 arrayIndex=0)const=0;
			virtual Void setSize(UInt32 width,UInt32 height)=0;
			virtual UInt32 getWidth()const=0;
			virtual UInt32 getHeight()const=0;
			virtual Void setArraySize(UInt32 size)=0;
			virtual UInt32 getArraySize()const=0;
			virtual Void setPixels(ConstVoidPtr pixels,UInt32 arrayIndex=0)=0;
			virtual Void updatePixels()=0;
			virtual ConstVoidPtr getPixels(UInt32 arrayIndex=0)const=0;
		};
		class ITextureCube
		{
		protected:
			virtual ~ITextureCube(){}
		public:
			virtual IRenderTarget * queryInterface_IRenderTarget(IEnum::ECubeTextureFace face,UInt32 mipmapLevel=0,UInt32 arrayIndex=0)const=0;
			virtual Void setSize(UInt32 width,UInt32 height)=0;
			virtual UInt32 getWidth()const=0;
			virtual UInt32 getHeight()const=0;
			virtual Void setPixels(ConstVoidPtr pixels,UInt32 arrayIndex=0)=0;
			virtual Void updatePixels()=0;
			virtual ConstVoidPtr getPixels(UInt32 arrayIndex=0)const=0;
		};
		class ITexture
		{
		protected:
			virtual ~ITexture(){}
		public:
			virtual ITexture2D * queryInterface_ITexture2D()const=0;
			virtual ITextureCube * queryInterface_ITextureCube()const=0;
			virtual IEnum::ETextureType getType()const=0;
			virtual const String & getName()const=0;
			virtual Void setFormat(IEnum::ETextureFormat format)=0;
			virtual IEnum::ETextureFormat getFormat()const=0;
			virtual Void setMipmapCount(UInt32 count=-1)=0;
			virtual UInt32 getMipmapCount()const=0;
		};
	}
}