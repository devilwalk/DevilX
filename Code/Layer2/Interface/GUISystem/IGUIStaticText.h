#pragma once
#include "IGUIControl.h"
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
			virtual Void setText(const WString & string,const CColour & colour=CFloatRGBA::sBlack)=0;
			virtual const WString & getText()const=0;
			virtual const CColour & getTextColour()const=0;
		};
	}
}