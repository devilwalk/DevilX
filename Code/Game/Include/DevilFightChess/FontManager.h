#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CFontManager
			:public TBaseObject<CFontManager>
		{
		public:
			static const UInt8 sFontSize;
		protected:
			CFontImage * mImg;
			NSRenderSystem::ITexture * mRenderTexture;
			TVector<RGBA> mPixels;
		public:
			CFontManager();
			~CFontManager();
			NSRenderSystem::ITexture * getRenderTexture()const
			{
				return mRenderTexture;
			}
			Void getPixelRange(WChar ch,CSInt2 * pixelStart,CSInt2 * pixelEnd);
		};
	}
}