#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CComboBox::CComboBox(const String & name,CControl * coordParent,CControl * orderParent)
	:CControl(name,coordParent,orderParent)
	,mEditBox(nullptr)
{
	mEditBox=DEVILX_NEW CEditBox(name+"/EditControl",this,this);
	for(UInt32 i=0;i<5;++i)
	{
		auto drop_list_control=DEVILX_NEW CCommonControl(name+"/DropListControl/"+CStringConverter::toString(i),this,this);
	}
}

NSDevilX::NSGUISystem::CComboBox::~CComboBox()
{
	DEVILX_DELETE(getEditControl());
}
