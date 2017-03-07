#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CUIManager::CUIManager()
	:mGraphicScene(nullptr)
{
	mGraphicScene=NSUISystem::getSystem()->createGraphicScene(CApp::getSingleton().getGame()->getViewport());
}

NSDevilX::NSFightChess::CUIManager::~CUIManager()
{
	NSUISystem::getSystem()->destroyGraphicScene(mGraphicScene);
}

Void NSDevilX::NSFightChess::CUIManager::createStaticText(const String & name,const WString & text,const CFloat2 & position,const CFloat2 & size,const CColour & colour)
{
	assert(!mStaticTexts.has(name));
	const auto word_width=size.x/text.length();
	auto static_text=DEVILX_NEW SStaticText;
	TVector<CSInt2> pixel_starts;
	pixel_starts.resize(text.length());
	TVector<CSInt2> pixel_ends;
	pixel_ends.resize(text.length());
	for(size_t i=0;i<text.length();++i)
	{
		CApp::getSingleton().getGame()->getFontManager()->getPixelRange(text[i],&pixel_starts[i],&pixel_ends[i]);
		auto window=getGraphicScene()->createWindow(name+"/"+CStringConverter::toString(i));
		window->setColour(colour);
		window->setTexture(CApp::getSingleton().getGame()->getFontManager()->getRenderTexture(),pixel_starts[i],pixel_ends[i]);
		window->queryInterface_IElement()->setPosition(position+CFloat2(word_width,0.0f)*static_cast<Float>(i));
		window->queryInterface_IElement()->setSize(CFloat2(word_width,size.y));
		static_text->mUIGraphicWindows.push_back(window);
	}
}
