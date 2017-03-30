#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CFontManager::CFontManager()
{}

NSDevilX::CFontManager::~CFontManager()
{
	mFonts.clear();
}

Void NSDevilX::CFontManager::reigsterFont(const String & fontName,const CMemoryStream * dataStream)
{
	mFonts.add(fontName,dataStream);
}

CFontImage * NSDevilX::CFontManager::getImage(const String & fontName,const CUTF8Char & ch,OUT CUInt2 * pixelStart,OUT CUInt2 * pixelEnd,const CUInt2 & fontSize)
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
