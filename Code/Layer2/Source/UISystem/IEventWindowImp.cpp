#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::IEventWindowImp::IEventWindowImp(const String & name)
	:mElement(nullptr)
{
	mElement=DEVILX_NEW IElementImp(name);
	mElement->setUserPointer(0,this);
}

NSDevilX::NSUISystem::IEventWindowImp::~IEventWindowImp()
{
	DEVILX_DELETE(mElement);
}

Void NSDevilX::NSUISystem::IEventWindowImp::notify(IEvent * e)
{
	mEventNotifier.notify(e->getType(),e);
}

IElement * NSDevilX::NSUISystem::IEventWindowImp::queryInterface_IElement() const
{
	return mElement;
}

Void NSDevilX::NSUISystem::IEventWindowImp::registerListener(IEventListener * listener,UInt32 eventType)
{
	auto el=mEventListeners.get(listener);
	if(!el)
	{
		el=DEVILX_NEW SEventListener();
		mEventListeners.add(listener,el);
	}
	el->mListener=listener;
	mEventNotifier.addListener(mEventListeners.get(listener),eventType);
}

Void NSDevilX::NSUISystem::IEventWindowImp::unregisterListener(IEventListener * listener,UInt32 eventType)
{
	mEventNotifier.removeListener(mEventListeners.get(listener),eventType);
}
