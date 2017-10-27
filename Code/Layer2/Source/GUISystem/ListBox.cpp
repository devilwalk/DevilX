#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CListBox::CListBox(const String & name,CControl * coordParent)
	:CControl(name,coordParent,False)
	,mList(nullptr)
{
	mList=DEVILX_NEW CList(name+"/List",this);
}

NSDevilX::NSGUISystem::CListBox::~CListBox()
{
	DEVILX_DELETE(mList);
}