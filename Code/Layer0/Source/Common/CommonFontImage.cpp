#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CFontImage::CFontImage(CDataStream * source,const CUInt2 & size,const CUInt2 & fontSize)
	:mSize(size)
	,mFontSize(fontSize)
	,mFTLibrary(nullptr)
	,mFTFace(nullptr)
	,mDirty(False)
{
	FT_Init_FreeType(&mFTLibrary);
	TVector<Byte> mem_src;
	mem_src.resize(source->getSize());
	auto reader=source->createReader();
	reader->process(source->getSize(),&mem_src[0]);
	source->destroyReader(reader);
	FT_New_Memory_Face(mFTLibrary,&mem_src[0],static_cast<FT_Long>(mem_src.size()),0,&mFTFace);
	FT_Set_Pixel_Sizes(mFTFace,getFontSize().x,getFontSize().y);
	mPixels.resize(getSize().x*getSize().y);
}

NSDevilX::CFontImage::~CFontImage()
{
	if(mFTFace)
	{
		FT_Done_Face(mFTFace);
	}
	if(mFTLibrary)
	{
		FT_Done_FreeType(mFTLibrary);
	}
}

Void NSDevilX::CFontImage::getPixelRange(WChar ch,CUInt2 * pixelStart,CUInt2 * pixelEnd,Bool dirtyIfCreate)
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
		FT_Load_Glyph(mFTFace,FT_Get_Char_Index(mFTFace,ch),FT_LOAD_DEFAULT);
		FT_Render_Glyph(mFTFace->glyph,FT_RENDER_MODE_NORMAL);
		UInt32 pixel_start_u=(static_cast<UInt32>(mCharPixelRanges.size())%(getSize().x/getFontSize().x))*getFontSize().x;
		UInt32 pixel_start_v=(static_cast<UInt32>(mCharPixelRanges.size())/(getSize().x/getFontSize().x))*getFontSize().y;
		const UInt32 ret_pixel_start_u=pixel_start_u;
		const UInt32 ret_pixel_start_v=pixel_start_v;
		for(UInt32 v=0;v<getFontSize().y;++v)
		{
			memset(&mPixels[(pixel_start_v+v)*getSize().x+pixel_start_u],0,getFontSize().x*sizeof(mPixels[0]));
		}
		pixel_start_u+=mFTFace->glyph->bitmap_left;
		auto under_base_line_distance=getFontSize().y-mFTFace->size->metrics.ascender/64;
		pixel_start_v+=getFontSize().y-1-(under_base_line_distance+mFTFace->glyph->bitmap_top);
		for(UInt32 v=0;v<mFTFace->glyph->bitmap.rows;++v)
		{
			for(UInt32 u=0;u<mFTFace->glyph->bitmap.width;++u)
			{
				auto font_img_pixel=mFTFace->glyph->bitmap.buffer[v*mFTFace->glyph->bitmap.width+u];
				auto & pixel_ref=mPixels[(pixel_start_v+v)*getSize().x+pixel_start_u+u];
				pixel_ref=font_img_pixel;
			}
		}
		mCharPixelRanges[ch]=std::pair<CUInt2,CUInt2>(CUInt2(ret_pixel_start_u,ret_pixel_start_v),CUInt2(ret_pixel_start_u,ret_pixel_start_v)+getFontSize()-CUInt2::sOne);
		if(pixelStart)
			*pixelStart=CUInt2(ret_pixel_start_u,ret_pixel_start_v);
		if(pixelEnd)
			*pixelEnd=CUInt2(ret_pixel_start_u,ret_pixel_start_v)+getFontSize()-CUInt2::sOne;
		mDirty=dirtyIfCreate;
	}
}
