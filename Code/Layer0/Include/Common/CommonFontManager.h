#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonFileStream.h"
#include "CommonFontImage.h"
#include "CommonResourceContainer.h"
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
		CFontImage * getImage(const String & fontName,WChar ch,OUT CSInt2 * pixelStart,OUT CSInt2 * pixelEnd,const CSInt2 & fontSize=CSInt2(32));
	};
}