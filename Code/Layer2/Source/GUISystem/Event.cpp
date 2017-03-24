#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CEvent::CEvent(UInt32 type)
	:mType(type)
	,mLayer(nullptr)
{
	mLayer=NSUISystem::getSystem()->createLayer("Event/"+CStringConverter::toString(type));
}

NSDevilX::NSGUISystem::CEvent::~CEvent()
{
	NSUISystem::getSystem()->destroyLayer(mLayer);
}

NSUISystem::IElement * NSDevilX::NSGUISystem::CEvent::queryInterface_IElement() const
{
	return mLayer;
}

UInt32 NSDevilX::NSGUISystem::CEvent::getType() const
{
	return mType;
}
