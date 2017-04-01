#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CFontFace::CFontFace(const CMemoryStream * source,const CUInt2 & fontPixelSize)
	:mFontPixelSize(fontPixelSize)
{
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

FT_Glyph_Metrics NSDevilX::CFontFace::getGlyphMetrics(const CUTF8Char & ch)
{
	FT_Load_Glyph(mFace,FT_Get_Char_Index(mFace,ch),FT_LOAD_DEFAULT);
	return mFace->glyph->metrics;
}

FT_Bitmap NSDevilX::CFontFace::render(const CUTF8Char & ch)
{
	FT_Load_Glyph(mFace,FT_Get_Char_Index(mFace,ch),FT_LOAD_DEFAULT|FT_LOAD_RENDER);
	return mFace->glyph->bitmap;
}
