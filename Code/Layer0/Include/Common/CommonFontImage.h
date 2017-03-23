#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonType.h"
#include "CommonSTL.h"
#include "CommonDataStream.h"
#include "CommonVectorI.h"
namespace NSDevilX
{
	class CFontImage
		:public TBaseObject<CFontImage>
	{
	protected:
		const CUInt2 mSize;
		const CUInt2 mFontSize;
		FT_Library mFTLibrary;
		FT_Face mFTFace;
		TVector<UInt8> mPixels;
		TMap<WChar,std::pair<CUInt2,CUInt2> > mCharPixelRanges;
		Bool mDirty;
	public:
		CFontImage(CDataStream * source,const CUInt2 & size=CUInt2(2048),const CUInt2 & fontSize=CUInt2(32));
		~CFontImage();
		const CUInt2 & getSize()const
		{
			return mSize;
		}
		const CUInt2 & getFontSize()const
		{
			return mFontSize;
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
		Void getPixelRange(WChar ch,CUInt2 * pixelStart,CUInt2 * pixelEnd,Bool dirtyIfCreate=True);
	};
}