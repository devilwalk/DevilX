#pragma once
#include "IUIElement.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IEvent
		{
		protected:
			virtual ~IEvent(){}
		public:
			virtual IElement * queryInterface_IElement()const=0;
			virtual UInt32 getType()const=0;
		};
	}
}