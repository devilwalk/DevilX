#pragma once
#include "IGUIControl.h"
#include "IGUITextProperty.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IStaticText
		{
		protected:
			virtual ~IStaticText(){}
		public:
			virtual IControl * queryInterface_IControl()const=0;
			virtual ITextProperty * getTextProperty()const=0;
			virtual Void setText(const CUTF8String & string)=0;
			virtual const CUTF8String & getText()const=0;
		};
	}
}