#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CUIControl::CUIControl(const String & name,const CFloat2 & position,const CFloat2 & size,CUIControl * parent)
	:mName(name)
	,mLayer(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer(name);
	mLayer->setPosition(position);
	mLayer->setSize(size);
	if(parent)
		mLayer->setParent(parent->getLayer());
}

NSDevilX::NSFightChess::CUIControl::~CUIControl()
{
	for(auto window:mUIGraphicWindows)
		CApp::getSingleton().getGame()->getUIManager()->getGraphicScene()->destroyWindow(window);
	NSUISystem::getSystem()->destroyLayer(mLayer);
}

Void NSDevilX::NSFightChess::CUIControl::addGraphicWindow(NSUISystem::IGraphicWindow * window)
{
	window->queryInterface_IElement()->setParent(getLayer());
	mUIGraphicWindows.push_back(window);
}

NSDevilX::NSFightChess::CUIManager::CUIManager()
	:mGraphicScene(nullptr)
{
	mGraphicScene=NSUISystem::getSystem()->createGraphicScene(CApp::getSingleton().getGame()->getViewport());
}

NSDevilX::NSFightChess::CUIManager::~CUIManager()
{
	NSUISystem::getSystem()->destroyGraphicScene(mGraphicScene);
}

CUIControl * NSDevilX::NSFightChess::CUIManager::createControl(const String & name,const CFloat2 & position,const CFloat2 & size,CUIControl * parent)
{
	assert(!mControls.has(name));
	auto control=DEVILX_NEW CUIControl(name,position,size,parent);
	mControls.add(name,control);
	return control;
}

Void NSDevilX::NSFightChess::CUIManager::destroyControl(CUIControl * control)
{
	mControls.destroy(control->getName());
}

CUIControl * NSDevilX::NSFightChess::CUIManager::createStaticText(const String & name,const WString & text,const CFloat2 & position,const CFloat2 & size,const CColour & colour,CUIControl * parent)
{
	assert(!mControls.has(name));
	const auto word_width=1.0f/text.length();
	auto static_text=DEVILX_NEW CUIControl(name,position,size,parent);
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
		window->queryInterface_IElement()->setPosition(CFloat2(word_width,0.0f)*static_cast<Float>(i));
		window->queryInterface_IElement()->setSize(CFloat2(word_width,1.0f));
		static_text->addGraphicWindow(window);
	}
	mControls.add(name,static_text);
	return static_text;
}
