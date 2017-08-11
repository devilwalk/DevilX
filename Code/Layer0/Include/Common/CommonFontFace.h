#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonMemoryStream.h"
#include "CommonUTFString.h"
#include "CommonVectorI.h"
namespace NSDevilX
{
	class CFontFace
		:public TBaseObject<CFontFace>
	{
	protected:
		FT_Library mLibrary;
		FT_Face mFace;
		FT_BBox mBBox;
		const CUInt2 mFontPixelSize;
	public:
		CFontFace(const CMemoryStream * source,const CUInt2 & fontPixelSize=CUInt2(32));
		~CFontFace();
		const CUInt2 & getFontPixelSize()const
		{
			return mFontPixelSize;
		}
		const FT_Glyph_Metrics & getGlyphMetrics(const CUTF8Char & ch)const;
		FT_Bitmap render(const CUTF8Char & ch);
		const FT_BBox & getBBox();
		UInt32 getTotalAdvanceWidth(const CUTF8String & text)const;
		Void getStartPositions(const CUTF8String & text,TVector<CUInt2> & startPositions);
	};
}