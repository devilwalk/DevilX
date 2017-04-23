#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSUIEditor::CCodeArea::CCodeArea()
	:mWindow(nullptr)
{
	mWindow=CApp::getSingleton().getMainFrame()->getScene()->createWindow("CodeArea");
}

NSDevilX::NSUIEditor::CCodeArea::~CCodeArea()
{
	CApp::getSingleton().getMainFrame()->getScene()->destroyWindow(mWindow);
}
