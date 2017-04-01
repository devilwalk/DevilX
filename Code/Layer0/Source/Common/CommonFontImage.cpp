#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CFontImage::CFontImage(CFontFace * face,const CUInt2 & size)
	:mSize(size)
	,mFontFace(face)
	,mDirty(False)
{
	mPixels.resize(getSize().x*getSize().y);
	for(char i='0';i<='9';++i)
		getPixelRange(i,nullptr,nullptr,False);
	for(char i='a';i<='z';++i)
		getPixelRange(i,nullptr,nullptr,False);
	for(char i='A';i<='Z';++i)
		getPixelRange(i,nullptr,nullptr,False);
}

NSDevilX::CFontImage::~CFontImage()
{
}

Void NSDevilX::CFontImage::getPixelRange(const CUTF8Char & ch,CUInt2 * pixelStart,CUInt2 * pixelEnd,Bool dirtyIfCreate)
{
	if(mCharPixelRanges.has(ch))
	{
		auto const & ret=mCharPixelRanges.get(ch);
		if(pixelStart)
			*pixelStart=ret.first;
		if(pixelEnd)
			*pixelEnd=ret.second;
	}
	else
	{
		auto bitmap=mFontFace->render(ch);
		const UInt32 pixel_start_u=(static_cast<UInt32>(mCharPixelRanges.size())%(getSize().x/mFontFace->getFontPixelSize().x))*mFontFace->getFontPixelSize().x;
		const UInt32 pixel_start_v=(static_cast<UInt32>(mCharPixelRanges.size())/(getSize().x/mFontFace->getFontPixelSize().x))*mFontFace->getFontPixelSize().y;
		for(UInt32 v=0;v<mFontFace->getFontPixelSize().y;++v)
		{
			memset(&mPixels[(pixel_start_v+v)*getSize().x+pixel_start_u],0,mFontFace->getFontPixelSize().x*sizeof(mPixels[0]));
		}
		//align to left bottom
		const UInt32 fill_pixel_start_v=pixel_start_v+(mFontFace->getFontPixelSize().y-bitmap.rows);
		for(UInt32 v=0;v<bitmap.rows;++v)
		{
			for(UInt32 u=0;u<bitmap.width;++u)
			{
				auto font_img_pixel=bitmap.buffer[v*bitmap.width+u];
				auto & pixel_ref=mPixels[(fill_pixel_start_v+v)*getSize().x+pixel_start_u+u];
				pixel_ref=font_img_pixel;
			}
		}
		mCharPixelRanges[ch]=std::pair<CUInt2,CUInt2>(CUInt2(pixel_start_u,pixel_start_v),CUInt2(pixel_start_u,pixel_start_v)+mFontFace->getFontPixelSize()-CUInt2::sOne);
		if(pixelStart)
			*pixelStart=CUInt2(pixel_start_u,pixel_start_v);
		if(pixelEnd)
			*pixelEnd=CUInt2(pixel_start_u,pixel_start_v)+mFontFace->getFontPixelSize()-CUInt2::sOne;
		mDirty=dirtyIfCreate;
	}
}
