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

NSDevilX::CFontManager::SChar NSDevilX::CFontManager::get(const String & fontName,const CUTF8Char & ch,const CUInt2 & fontPixelSize)
{
	SChar ret;
	auto src=mFonts.get(fontName);
	if(!src)
		return ret;
	CFontFace * face=getFace(fontName,fontPixelSize);
	ret.mGlyphMetrics=face->getGlyphMetrics(ch);
	auto & imgs=mImages[src];
	for(auto img:imgs)
	{
		if(img->getFontFace()==face)
		{
			ret.mImage=img;
			break;
		}
	}
	if(!ret.mImage)
	{
		ret.mImage=DEVILX_NEW CFontImage(face,2048);
		imgs.push_back(ret.mImage);
	}
	ret.mImage->getPixelRange(ch,&ret.mPixelStart,&ret.mPixelEnd);
	return ret;
}

CFontFace * NSDevilX::CFontManager::getFace(const String & fontName,const CUInt2 & fontPixelSize)
{
	auto src=mFonts.get(fontName);
	if(!src)
		return nullptr;
	CFontFace * face=nullptr;
	auto & faces=mFaces[src];
	for(auto test:faces)
	{
		if(test->getFontPixelSize()==fontPixelSize)
		{
			face=test;
			break;
		}
	}
	if(!face)
	{
		face=DEVILX_NEW CFontFace(src,fontPixelSize);
		faces.push_back(face);
	}
	return face;
}