#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CFontManager::CFontManager()
{}

NSDevilX::CFontManager::~CFontManager()
{}

Void NSDevilX::CFontManager::reigsterFont(const String & fontName,const String & fontFileName)
{
	mFonts.add(fontName,DEVILX_NEW CFileStream(fontFileName));
}

CFontImage * NSDevilX::CFontManager::getImage(const String & fontName,WChar ch,OUT CSInt2 * pixelStart,OUT CSInt2 * pixelEnd)
{
	auto src=mFonts.get(fontName);
	if(!src)
		return nullptr;
	auto & img=mImages[src];
	if(!img)
	{
		img=DEVILX_NEW CFontImage(src);
	}
	img->getPixelRange(ch,pixelStart,pixelEnd);
	return img;
}
