#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CFontManager
			:public TBaseObject<CFontManager>
		{
		public:
		protected:
			FT_Library mFTLibrary;
			FT_Face mFTFace;
			NSRenderSystem::ITexture * mRenderTexture;
			TVector<RGBA> mPixels;
			TMap<WChar,std::pair<CFloat2,CFloat2> > mCharUVs;
		public:
			CFontManager();
			~CFontManager();
			NSRenderSystem::ITexture * getRenderTexture()const
			{
				return mRenderTexture;
			}
			Void getUV(WChar ch,CFloat2 * uvOffset,CFloat2 * uvScale);
		};
	}
}