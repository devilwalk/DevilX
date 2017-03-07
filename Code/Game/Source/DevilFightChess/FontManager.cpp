#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;
const UInt8 NSDevilX::NSFightChess::CFontManager::sFontSize=32;
NSDevilX::NSFightChess::CFontManager::CFontManager()
	:mFTLibrary(nullptr)
	,mFTFace(nullptr)
	,mRenderTexture(nullptr)
{
	mRenderTexture=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createTexture("Font",NSRenderSystem::IEnum::ETextureType_2D);
	mRenderTexture->queryInterface_ITexture2DWritable()->setArraySize(1);
	mRenderTexture->queryInterface_ITexture2DWritable()->setFormat(NSRenderSystem::IEnum::ETexture2DFormat_R8G8B8A8);
	mRenderTexture->queryInterface_ITexture2DWritable()->setMipmapCount();
	mRenderTexture->queryInterface_ITexture2DWritable()->setSize(2048,2048);
	mPixels.resize(mRenderTexture->queryInterface_ITexture2DReadable()->getWidth()*mRenderTexture->queryInterface_ITexture2DReadable()->getHeight());
	mRenderTexture->queryInterface_ITexture2DWritable()->setPixels(&mPixels[0],0,0);
	FT_Init_FreeType(&mFTLibrary);
	String font_file;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	font_file=CDirectory::getSystemFontsDirectory()+"/Fonts/simsun.ttc";
#endif
	FT_New_Face(mFTLibrary,font_file.c_str(),0,&mFTFace);
	FT_Set_Pixel_Sizes(mFTFace,sFontSize,sFontSize);
}

NSDevilX::NSFightChess::CFontManager::~CFontManager()
{
	if(mFTFace)
	{
		FT_Done_Face(mFTFace);
	}
	if(mFTLibrary)
	{
		FT_Done_FreeType(mFTLibrary);
	}
}

Void NSDevilX::NSFightChess::CFontManager::getPixelRange(WChar ch,CSInt2 * pixelStart,CSInt2 * pixelEnd)
{
	if(mCharPixelRanges.has(ch))
	{
		auto const & ret=mCharPixelRanges.get(ch);
		if(pixelStart)
			*pixelStart=ret.first;
		if(pixelEnd)
			*pixelEnd=ret.second;
	}
	else
	{
		FT_Load_Glyph(mFTFace,FT_Get_Char_Index(mFTFace,ch),FT_LOAD_DEFAULT);
		FT_Render_Glyph(mFTFace->glyph,FT_RENDER_MODE_NORMAL);
		UInt32 pixel_start_u=(static_cast<UInt32>(mCharPixelRanges.size())%(mRenderTexture->queryInterface_ITexture2DReadable()->getWidth()/sFontSize))*sFontSize;
		UInt32 pixel_start_v=(static_cast<UInt32>(mCharPixelRanges.size())/(mRenderTexture->queryInterface_ITexture2DReadable()->getWidth()/sFontSize))*sFontSize;
		const UInt32 ret_pixel_start_u=pixel_start_u;
		const UInt32 ret_pixel_start_v=pixel_start_v;
		for(auto v=0;v<sFontSize;++v)
		{
			memset(&mPixels[(pixel_start_v+v)*mRenderTexture->queryInterface_ITexture2DReadable()->getWidth()],0,sFontSize*sizeof(RGBA));
		}
		pixel_start_u+=mFTFace->glyph->bitmap_left;
		auto under_base_line_distance=sFontSize-mFTFace->size->metrics.ascender/64;
		pixel_start_v+=sFontSize-1-(under_base_line_distance+mFTFace->glyph->bitmap_top);
		for(UInt32 v=0;v<mFTFace->glyph->bitmap.rows;++v)
		{
			for(UInt32 u=0;u<mFTFace->glyph->bitmap.width;++u)
			{
				auto font_img_pixel=mFTFace->glyph->bitmap.buffer[v*mFTFace->glyph->bitmap.width+u];
				auto & pixel_ref=mPixels[(pixel_start_v+v)*mRenderTexture->queryInterface_ITexture2DReadable()->getWidth()+pixel_start_u+u];
				pixel_ref=CFloatRGBA(font_img_pixel,font_img_pixel,font_img_pixel,font_img_pixel).rgba8();
			}
		}
		mRenderTexture->queryInterface_ITexture2DWritable()->updatePixels(0,0);
		mCharPixelRanges[ch]=std::pair<CSInt2,CSInt2>(CSInt2(ret_pixel_start_u,ret_pixel_start_v),CSInt2(ret_pixel_start_u,ret_pixel_start_v)+CSInt2(sFontSize-1));
		if(pixelStart)
			*pixelStart=CSInt2(ret_pixel_start_u,ret_pixel_start_v);
		if(pixelEnd)
			*pixelEnd=CSInt2(ret_pixel_start_u,ret_pixel_start_v)+CSInt2(sFontSize-1);
	}
}
