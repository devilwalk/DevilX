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
