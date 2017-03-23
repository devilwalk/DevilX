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
			virtual Void setFontResource(NSResourceSystem::IResource * resource)=0;
			virtual NSResourceSystem::IResource * getFontResource()const=0;
			virtual Void setText(const CUTF8String & string)=0;
			virtual const CUTF8String & getText()const=0;
			virtual Void setTextColour(const CColour & colour)=0;
			virtual const CColour & getTextColour()const=0;
		};
	}
}