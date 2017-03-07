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
			FT_Library mFTLibrary;
			FT_Face mFTFace;
			NSRenderSystem::ITexture * mRenderTexture;
			TVector<RGBA> mPixels;
			TMap<WChar,std::pair<CSInt2,CSInt2> > mCharPixelRanges;
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