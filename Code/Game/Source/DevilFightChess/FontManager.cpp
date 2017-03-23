#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;
const UInt8 NSDevilX::NSFightChess::CFontManager::sFontSize=32;
NSDevilX::NSFightChess::CFontManager::CFontManager()
	:mImg(nullptr)
	,mRenderTexture(nullptr)
{
	String font_file;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	font_file=CDirectory::getSystemFontsDirectory()+"/Fonts/simsun.ttc";
#endif
	CFileStream font_file_stream(font_file);
	mImg=DEVILX_NEW CFontImage(&font_file_stream,CUInt2(2048),CUInt2(sFontSize));
	mPixels.resize(mImg->getSize().x,mImg->getSize().y);
	mRenderTexture=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createTexture("Font",NSRenderSystem::IEnum::ETextureType_2D);
	mRenderTexture->queryInterface_ITexture2DWritable()->setArraySize(1);
	mRenderTexture->queryInterface_ITexture2DWritable()->setFormat(NSRenderSystem::IEnum::ETexture2DFormat_A8);
	mRenderTexture->queryInterface_ITexture2DWritable()->setMipmapCount();
	mRenderTexture->queryInterface_ITexture2DWritable()->setSize(mImg->getSize().x,mImg->getSize().y);
	mRenderTexture->queryInterface_ITexture2DWritable()->setPixels(&mPixels[0],0,0);
}

NSDevilX::NSFightChess::CFontManager::~CFontManager()
{
	DEVILX_DELETE(mImg);
}

Void NSDevilX::NSFightChess::CFontManager::getPixelRange(WChar ch,CUInt2 * pixelStart,CUInt2 * pixelEnd)
{
	CUInt2 start,end;
	mImg->getPixelRange(ch,&start,&end);
	if(mImg->isDirty())
	{
		for(Int32 u=start.x;u<=end.x;++u)
		{
			for(Int32 v=start.y;v<=end.y;++v)
			{
				const Int32 index=v*mImg->getSize().x+u;
				const UInt8 font_img_pixel=mImg->getPixels()[index];
				mPixels[v*mImg->getSize().x+u]=CFloatRGBA(font_img_pixel,font_img_pixel,font_img_pixel,font_img_pixel).rgba8();
			}
		}
		mRenderTexture->queryInterface_ITexture2DWritable()->updatePixels(0,0);
		mImg->setDirty(False);
	}
}
