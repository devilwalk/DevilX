#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonFileStream.h"
#include "CommonFontImage.h"
#include "CommonResourceContainer.h"
#include "CommonVectorI.h"
namespace NSDevilX
{
	class CFontManager
		:public TBaseObject<CFontManager>
	{
	protected:
		TNamedResourcePtrMap<const CMemoryStream> mFonts;
		TMap<const CMemoryStream*,TResourcePtrVector<CFontImage> > mImages;
	public:
		CFontManager();
		~CFontManager();
		Void reigsterFont(const String & fontName,const CMemoryStream * dataStream);
		CFontImage * getImage(const String & fontName,const CUTF8Char & ch,OUT CUInt2 * pixelStart,OUT CUInt2 * pixelEnd,const CUInt2 & fontSize=CUInt2(32));
	};
}