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
		TResourcePtrMap<const String,CFileStream> mFonts;
		TMap<CFileStream*,TResourcePtrVector<CFontImage> > mImages;
	public:
		CFontManager();
		~CFontManager();
		Void reigsterFont(const String & fontName,const String & fontFileName);
		CFontImage * getImage(const String & fontName,WChar ch,OUT CUInt2 * pixelStart,OUT CUInt2 * pixelEnd,const CUInt2 & fontSize=CUInt2(32));
	};
}