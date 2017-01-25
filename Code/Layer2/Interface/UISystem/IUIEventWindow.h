#pragma once
#include "IUIElement.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IEventListener
		{
		protected:
			virtual ~IEventListener(){}
		public:
			virtual Void onEvent(IEvent * e)=0;
		};
		class IEventWindow
		{
		protected:
			virtual ~IEventWindow(){}
		public:
			virtual IElement * queryInterface_IElement()const=0;
			virtual Void registerListener(IEventListener * listener,UInt32 eventType)=0;
			virtual Void unregisterListener(IEventListener * listener,UInt32 eventType)=0;
		};
	}
}