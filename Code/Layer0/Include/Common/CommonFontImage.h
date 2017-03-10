#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonType.h"
#include "CommonSTL.h"
#include "CommonDataStream.h"
namespace NSDevilX
{
	class CFontImage
		:public TBaseObject<CFontImage>
	{
	protected:
		const CSInt2 mSize;
		const CSInt2 mFontSize;
		FT_Library mFTLibrary;
		FT_Face mFTFace;
		TVector<UInt8> mPixels;
		TMap<WChar,std::pair<CSInt2,CSInt2> > mCharPixelRanges;
		Bool mDirty;
	public:
		CFontImage(CDataStream * source,const CSInt2 & size=CSInt2(2048),const CSInt2 & fontSize=CSInt2(32));
		~CFontImage();
		const CSInt2 & getSize()const
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
		Void getPixelRange(WChar ch,CSInt2 * pixelStart,CSInt2 * pixelEnd,Bool dirtyIfCreate=True);
	};
}