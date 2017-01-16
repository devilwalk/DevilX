#pragma once
#include "MipmapRenderTarget.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITextureImp
			:public ITexture
		{
		protected:
			const String mName;
		public:
			ITextureImp(const String & name);
			virtual ~ITextureImp();
			virtual const String & getName() const override;
		};
		class ITexture2DImp
			:public ITexture2D
			,public ITextureImp
			,public TBaseObject<ITexture2DImp>
			,public CMessageNotifier
			,public CDirtyFlagContainer
		{
		public:
			enum EMessage
			{
				EMessage_BeginSizeChange,
				EMessage_EndSizeChange,
				EMessage_BeginMipmapChange,
				EMessage_EndMipmapChange,
				EMessage_BeginArraySizeChange,
				EMessage_EndArraySizeChange,
				EMessage_BeginFormatChange,
				EMessage_EndFormatChange,
				EMessage_BeginPixelsChange,
				EMessage_EndPixelsChange
			};
			enum EDirtyFlag
			{
				EDirtyFlag_Size,
				EDirtyFlag_Mipmap,
				EDirtyFlag_ArraySize,
				EDirtyFlag_Format,
				EDirtyFlag_Pixels
			};
		protected:
			UInt32 mWidth,mHeight;
			IEnum::ETextureFormat mFormat;
			UInt32 mMipmapCount;
			UInt32 mArraySize;
			ConstVoidPtr mPixels;
		public:
			ITexture2DImp(const String & name);
			~ITexture2DImp();

			// Í¨¹ý ITexture ¼Ì³Ð
			virtual IRenderTarget * queryInterface_IRenderTarget(UInt32 mipmapLevel=0,UInt32 arrayIndex=0) const override;
			virtual ITexture2D * queryInterface_ITexture2D() const override;
			virtual ITextureCube * queryInterface_ITextureCube() const override;
			virtual IEnum::ETextureType getType() const override;
			virtual Void setSize(UInt32 width,UInt32 height) override;
			virtual UInt32 getWidth() const override;
			virtual UInt32 getHeight() const override;
			virtual Void setMipmapCount(UInt32 count=-1) override;
			virtual UInt32 getMipmapCount() const override;
			virtual Void setArraySize(UInt32 size) override;
			virtual UInt32 getArraySize() const override;
			virtual Void setFormat(IEnum::ETextureFormat format) override;
			virtual IEnum::ETextureFormat getFormat() const override;
			virtual Void setPixels(ConstVoidPtr pixels,UInt32 arrayIndex=0) override;
			virtual Void updatePixels() override;
			virtual ConstVoidPtr getPixels(UInt32 arrayIndex=0) const;
		};
	}
}