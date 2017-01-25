#pragma once
#include "IGUIElement.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IPanel
		{
		protected:
			virtual ~IPanel(){}
		public:
			virtual IElement * queryInterface_IElement()const=0;
		};
	}
}