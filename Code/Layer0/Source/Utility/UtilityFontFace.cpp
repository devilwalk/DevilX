#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CFontFace::CFontFace(const CMemoryStream * source,const CUInt2 & fontPixelSize)
	:mFontPixelSize(fontPixelSize)
{
	memset(&mBBox,0,sizeof(mBBox));
	FT_Init_FreeType(&mLibrary);
	FT_New_Memory_Face(mLibrary,&source->getData()[0],source->getSize(),0,&mFace);
	FT_Set_Pixel_Sizes(mFace,getFontPixelSize().x,getFontPixelSize().y);
}

NSDevilX::CFontFace::~CFontFace()
{
	if(mFace)
	{
		FT_Done_Face(mFace);
	}
	if(mLibrary)
	{
		FT_Done_FreeType(mLibrary);
	}
}

const FT_Glyph_Metrics & NSDevilX::CFontFace::getGlyphMetrics(const CUTF8Char & ch)const
{
	FT_Load_Glyph(mFace,FT_Get_Char_Index(mFace,ch),FT_LOAD_DEFAULT);
	return mFace->glyph->metrics;
}

FT_Bitmap NSDevilX::CFontFace::render(const CUTF8Char & ch)
{
	FT_Load_Glyph(mFace,FT_Get_Char_Index(mFace,ch),FT_LOAD_DEFAULT|FT_LOAD_RENDER);
	return mFace->glyph->bitmap;
}

const FT_BBox & NSDevilX::CFontFace::getBBox()
{
	// TODO: 在此处插入 return 语句
	FT_BBox init_bbox={0};
	if(memcmp(&mBBox,&init_bbox,sizeof(mBBox))==0)
	{
		for(FT_Long glyphs_index=0;glyphs_index<mFace->num_glyphs;++glyphs_index)
		{
			FT_Load_Glyph(mFace,glyphs_index,FT_LOAD_DEFAULT);
			if(mFace->glyph->metrics.horiAdvance>0&&mFace->glyph->metrics.horiBearingY>0)
			{
				mBBox.xMax=std::max<>(mBBox.xMax,mFace->glyph->metrics.horiAdvance);
				mBBox.yMax=std::max<>(mBBox.yMax,mFace->glyph->metrics.horiBearingY);
				mBBox.yMin=std::min<>(mBBox.yMin,mFace->glyph->metrics.horiBearingY-mFace->glyph->metrics.height);
			}
		}
	}
	return mBBox;
}

FT_BBox NSDevilX::CFontFace::getBBox(const CUTF8Char & ch) const
{
	FT_Load_Glyph(mFace,FT_Get_Char_Index(mFace,ch),FT_LOAD_DEFAULT);
	FT_Glyph glyph=nullptr;
	FT_Get_Glyph(mFace->glyph,&glyph);
	FT_BBox ret={0};
	FT_Glyph_Get_CBox(glyph,0,&ret);
	FT_Done_Glyph(glyph);
	return ret;
}

UInt32 NSDevilX::CFontFace::getTotalAdvanceWidth(const CUTF8String & text) const
{
	UInt32 ret=0;
	for(auto const & c:text)
	{
		ret+=getGlyphMetrics(c).horiAdvance;
	}
	return ret;
}

Void NSDevilX::CFontFace::getStartPositions(const CUTF8String & text,TVector<CUInt2>& startPositions)
{
	startPositions.clear();
	UInt32 start_pos=0;
	for(auto const & c:text)
	{
		startPositions.push_back(CUInt2(start_pos));
		start_pos+=getGlyphMetrics(c).horiAdvance;
	}
}
