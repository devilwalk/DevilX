#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CFontManager::CFontManager()
	:mFTLibrary(nullptr)
	,mFTFace(nullptr)
	,mRenderTexture(nullptr)
{
	mPixels.resize(2048*2048);
	mRenderTexture=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createTexture("Font",NSRenderSystem::IEnum::ETextureType_2D);
	mRenderTexture->queryInterface_ITexture2DWritable()->setArraySize(1);
	mRenderTexture->queryInterface_ITexture2DWritable()->setFormat(NSRenderSystem::IEnum::ETexture2DFormat_R8G8B8A8);
	mRenderTexture->queryInterface_ITexture2DWritable()->setMipmapCount();
	mRenderTexture->queryInterface_ITexture2DWritable()->setSize(2048,2048);
	mRenderTexture->queryInterface_ITexture2DWritable()->setPixels(&mPixels[0],0,0);
	FT_Init_FreeType(&mFTLibrary);
	String font_file;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	font_file=CDirectory::getSystemFontsDirectory()+"/Fonts/simsun.ttc";
#endif
	FT_New_Face(mFTLibrary,font_file.c_str(),0,&mFTFace);
	FT_Set_Pixel_Sizes(mFTFace,32,32);
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

Void NSDevilX::NSFightChess::CFontManager::getUV(WChar ch,CFloat2 * uvOffset,CFloat2 * uvScale)
{
	if(mCharUVs.has(ch))
	{
		auto const & ret=mCharUVs.get(ch);
		if(uvOffset)
			*uvOffset=ret.first;
		if(uvScale)
			*uvScale=ret.second;
	}
	else
	{
		FT_Load_Glyph(mFTFace,FT_Get_Char_Index(mFTFace,ch),FT_LOAD_DEFAULT);
		FT_Render_Glyph(mFTFace->glyph,FT_RENDER_MODE_NORMAL);
		auto pixel_start_u=(mCharUVs.size()%(mRenderTexture->queryInterface_ITexture2DReadable()->getWidth()/32))*32;
		auto pixel_start_v=(mCharUVs.size()/(mRenderTexture->queryInterface_ITexture2DReadable()->getWidth()/32))*32;
		auto uv_offset=CFloat2(static_cast<Float>(pixel_start_u)/mRenderTexture->queryInterface_ITexture2DReadable()->getWidth()
			,static_cast<Float>(pixel_start_v)/mRenderTexture->queryInterface_ITexture2DReadable()->getHeight());
		auto uv_scale=CFloat2(32.0f/mRenderTexture->queryInterface_ITexture2DReadable()->getWidth());
		for(auto v=0;v<32;++v)
		{
			memset(&mPixels[(pixel_start_v+v)*mRenderTexture->queryInterface_ITexture2DReadable()->getWidth()],0,32*sizeof(RGBA));
		}
		pixel_start_u+=mFTFace->glyph->bitmap_left;
		auto under_base_line_distance=32-mFTFace->size->metrics.ascender/64;
		pixel_start_v+=31-(under_base_line_distance+mFTFace->glyph->bitmap_top);
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
		mCharUVs[ch]=std::pair<CFloat2,CFloat2>(uv_offset,uv_scale);
		if(uvOffset)
			*uvOffset=uv_offset;
		if(uvScale)
			*uvScale=uv_scale;
	}
}
