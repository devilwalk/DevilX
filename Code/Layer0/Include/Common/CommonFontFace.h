#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonMemoryStream.h"
#include "CommonUTFChar.h"
#include "CommonVectorI.h"
namespace NSDevilX
{
	class CFontFace
		:public TBaseObject<CFontFace>
	{
	protected:
		FT_Library mLibrary;
		FT_Face mFace;
		const CUInt2 mFontPixelSize;
	public:
		CFontFace(const CMemoryStream * source,const CUInt2 & fontPixelSize=CUInt2(32));
		~CFontFace();
		const CUInt2 & getFontPixelSize()const
		{
			return mFontPixelSize;
		}
		FT_Glyph_Metrics getGlyphMetrics(const CUTF8Char & ch);
		FT_Bitmap render(const CUTF8Char & ch);
	};
}