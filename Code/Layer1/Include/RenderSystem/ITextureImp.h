#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISystemImp;
		class IRenderTargetImp;
		class ITextureImp
			:public ITexture
			,public CReferenceObject
		{
		protected:
			const String mName;
		public:
			ITextureImp(const String & name);
			virtual const String & getName() const override;
		protected:
			virtual ~ITextureImp();
		};
		class ITexture2DImp
			:public ITexture2DReadable
			,public ITexture2DWritable
			,public ITextureImp
			,public TBaseObject<ITexture2DImp>
			,public CMessageNotifier
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
			struct SSubTexture
				:public TBaseObject<SSubTexture>
				,public TMessageReceiver<ISystemImp>
			{
				ITexture2DImp * const mTexture;
				const UInt32 mWidth,mHeight;
				const UInt32 mMipmapLevel;
				const UInt32 mArrayIndex;
				ConstVoidPtr mMemoryPixels;
				IRenderTargetImp * mRenderTargetPixels;
				explicit SSubTexture(ITexture2DImp * texture,UInt32 width,UInt32 height,UInt32 mipmapLevel,UInt32 arrayIndex);
				Void setMemoryPixels(ConstVoidPtr pixels);
				Void setRenderTargetPixels(IRenderTargetImp * target);

				// 通过 TMessageReceiver 继承
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		protected:
			UInt32 mWidth,mHeight;
			IEnum::ETexture2DFormat mFormat;
			UInt32 mMipmapCount;
			UInt32 mRealMipmapCount;
			UInt32 mArraySize;
			TResourcePtrMap(UInt32,SSubTexture) mSubTextures;
		public:
			ITexture2DImp(const String & name);
			static UInt32 encodeSubTextureKey(UInt32 mipmapLevel,UInt32 arrayIndex)
			{
				return (arrayIndex<<16)+mipmapLevel;
			}
			static Void decodeSubTextureKey(UInt32 key,UInt32 * mipmapLevel,UInt32 * arrayIndex)
			{
				if(arrayIndex)
					*arrayIndex=key>>16;
				if(mipmapLevel)
					*mipmapLevel=key&0xffff;
			}
			static UInt32 getMipmapPixelByteOffset(IEnum::ETexture2DFormat format,UInt32 mipmapLevel,UInt32 width,UInt32 height)
			{
				UInt32 bpp=0;
				switch(format)
				{
				case IEnum::ETexture2DFormat_R8G8B8A8:
					bpp=4;
					break;
				case IEnum::ETexture2DFormat_A8:
					bpp=1;
					break;
				}
				auto next_width=width;
				auto next_height=height;
				UInt32 pitch=0;
				do
				{
					pitch+=next_width*next_height;
					next_width>>=1;
					next_width=std::max<UInt32>(next_width,1);
					next_height>>=1;
					next_height=std::max<UInt32>(next_height,1);
				}
				while(mipmapLevel--);
				return bpp*pitch;
			}
			const decltype(mSubTextures) & getSubTextures()
			{
				_createSubTextures();
				return mSubTextures;
			}
			UInt32 getRealMipmapCount()
			{
				_createSubTextures();
				return mRealMipmapCount;
			}
			Boolean isAutoMipmap()const
			{
				return getMipmapCount()==static_cast<UInt32>(-1);
			}
			// 通过 ITexture 继承
			virtual ITexture2DReadable * queryInterface_ITexture2DReadable() const override;
			virtual ITexture2DWritable * queryInterface_ITexture2DWritable() const override;
			virtual IEnum::ETextureType getType() const override;
			virtual Void setSize(UInt32 width,UInt32 height) override;
			virtual UInt32 getWidth() const override;
			virtual UInt32 getHeight() const override;
			virtual Void setMipmapCount(UInt32 count=-1) override;
			virtual UInt32 getMipmapCount() const override;
			virtual Void setArraySize(UInt32 size) override;
			virtual UInt32 getArraySize() const override;
			virtual Void setFormat(IEnum::ETexture2DFormat format) override;
			virtual IEnum::ETexture2DFormat getFormat() const override;
			virtual Void setPixels(ConstVoidPtr pixels,UInt32 mipmapLevel=-1,UInt32 arrayIndex=0) override;
			virtual Void setPixels(IRenderTarget * target,UInt32 mipmapLevel=0,UInt32 arrayIndex=0) override;
			virtual Void updatePixels(UInt32 mipmapLevel=0,UInt32 arrayIndex=0) override;
			virtual ConstVoidPtr getPixels(UInt32 mipmapLevel=-1,UInt32 arrayIndex=-1) const override;
		protected:
			~ITexture2DImp();
			Void _createSubTextures();
		};
	}
}