#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;
NSDevilX::NSFightChess::CFontManager::CFontManager()
	:mFontResource(nullptr)
{
	String font_file;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	font_file=CDirectory::getSystemFontsDirectory()+"/msyh.ttc";
#endif
	mFontResource=NSResourceSystem::getSystem()->createResource("Font/Default",font_file);
}

NSDevilX::NSFightChess::CFontManager::~CFontManager()
{
	NSResourceSystem::getSystem()->destroyResource(getFontResource());
}