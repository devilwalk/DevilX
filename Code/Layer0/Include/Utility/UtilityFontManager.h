#pragma once
#include "UtilityFontFace.h"
#include "UtilityFontImage.h"
#include "UtilityResourceContainer.h"
namespace NSDevilX
{
	class CFontManager
		:public TBaseObject<CFontManager>
	{
	public:
		struct SChar
			:public TBaseObject<SChar>
		{
			CFontImage * mImage;
			CUInt2 mPixelStart;
			CUInt2 mPixelEnd;
			FT_Glyph_Metrics mGlyphMetrics;
			SChar()
				:mImage(nullptr)
			{}
		};
	protected:
		TNamedResourcePtrMap(const CMemoryStream) mFonts;
		TMap(const CMemoryStream*,TResourcePtrVector(CFontFace) ) mFaces;
		TMap(const CMemoryStream*,TResourcePtrVector(CFontImage) ) mImages;
	public:
		CFontManager();
		~CFontManager();
		Void reigsterFont(const String & fontName,const CMemoryStream * dataStream);
		SChar get(const String & fontName,const CUTF8Char & ch,const CUInt2 & fontPixelSize=CUInt2(32));
		CFontFace * getFace(const String & fontName,const CUInt2 & fontPixelSize=CUInt2(32));
	};
}