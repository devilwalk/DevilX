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

CFontImage * NSDevilX::CFontManager::getImage(const String & fontName,WChar ch,OUT CSInt2 * pixelStart,OUT CSInt2 * pixelEnd,const CSInt2 & fontSize)
{
	auto src=mFonts.get(fontName);
	if(!src)
		return nullptr;
	CFontImage * ret=nullptr;
	auto & imgs=mImages[src];
	for(auto img:imgs)
	{
		if(img->getFontSize()==fontSize)
		{
			ret=img;
			break;
		}
	}
	if(!ret)
	{
		ret=DEVILX_NEW CFontImage(src,2048,fontSize);
		imgs.push_back(ret);
	}
	ret->getPixelRange(ch,pixelStart,pixelEnd);
	return ret;
}
