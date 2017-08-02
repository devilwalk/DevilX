#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CDropList::CDropList(const String & name,CControl * coordParent,CControl * orderParent)
	:CControl(name,coordParent,orderParent)
{}

NSDevilX::NSGUISystem::CDropList::~CDropList()
{}

Void NSDevilX::NSGUISystem::CDropList::setSize(UInt32 size)
{
	if(size>getSize())
	{
		for(UInt32 i=getSize();i<size;++i)
		{
			auto control=DEVILX_NEW CCommonControl(getLayer()->getName()+"/"+CStringConverter::toString(i),this,this);
		}
	}
}
