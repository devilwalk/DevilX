#pragma once
#include "IGUIControl.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IButton
		{
		protected:
			virtual ~IButton(){}
		public:
			virtual IControl * queryInterface_IControl()const=0;
			virtual Void setText(const WString & string)=0;
		};
	}
}