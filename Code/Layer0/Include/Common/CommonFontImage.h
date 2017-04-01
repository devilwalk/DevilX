#pragma once
#include "CommonFontFace.h"
namespace NSDevilX
{
	class CFontImage
		:public TBaseObject<CFontImage>
	{
	protected:
		CFontFace * mFontFace;
		const CUInt2 mSize;
		TVector<UInt8> mPixels;
		TMap<CUTF8Char,std::pair<CUInt2,CUInt2> > mCharPixelRanges;
		Bool mDirty;
	public:
		CFontImage(CFontFace * face,const CUInt2 & size=CUInt2(2048));
		~CFontImage();
		const CFontFace * getFontFace()const
		{
			return mFontFace;
		}
		const CUInt2 & getSize()const
		{
			return mSize;
		}
		const UInt8 * getPixels()const
		{
			return mPixels.empty()?nullptr:&mPixels[0];
		}
		Void setDirty(Bool dirty)
		{
			mDirty=dirty;
		}
		Boolean isDirty()const
		{
			return False!=mDirty;
		}
		Void getPixelRange(const CUTF8Char & ch,CUInt2 * pixelStart,CUInt2 * pixelEnd,Bool dirtyIfCreate=True);
	};
}