#pragma once
#include "IUIElement.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class ITextWindow
		{
		protected:
			virtual ~ITextWindow(){}
		public:
			virtual IElement * queryInterface_IElement()const=0;
			virtual Void setText(const String & text)=0;
			virtual const String & getText()const=0;
		};
	}
}