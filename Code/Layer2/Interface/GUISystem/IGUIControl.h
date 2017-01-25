#pragma once
#include "IGUIElement.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IControl
		{
		protected:
			virtual ~IControl(){}
		public:
			virtual IElement * queryInterface_IElement()const=0;
		};
	}
}