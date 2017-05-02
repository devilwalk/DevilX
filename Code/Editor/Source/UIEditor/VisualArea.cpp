#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUIEditor;

NSDevilX::NSUIEditor::CVisualArea::CVisualArea()
	:mWindow(nullptr)
{
	mWindow=CApp::getSingleton().getMainFrame()->getScene()->createWindow("VisualArea");
}

NSDevilX::NSUIEditor::CVisualArea::~CVisualArea()
{
	CApp::getSingleton().getMainFrame()->getScene()->destroyWindow(mWindow);
}
