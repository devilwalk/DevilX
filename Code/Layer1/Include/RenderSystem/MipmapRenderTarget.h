#pragma once
#include "IRenderTargetImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITexture2DImp;
		class CMipmapRenderTarget2D
			:public IRenderTargetImp
			,public TBaseObject<CMipmapRenderTarget2D>
		{
		protected:
			const UInt32 mMipmapLevel;
			ITexture2DImp * const mTexture;
		public:
			CMipmapRenderTarget2D(UInt32 mipmapLevel,ITexture2DImp * texture);
			~CMipmapRenderTarget2D();
			UInt32 getMipmapLevel()const
			{
				return mMipmapLevel;
			}
			ITexture2DImp * getTexture()const
			{
				return mTexture;
			}
		};
	}
}