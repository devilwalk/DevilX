#pragma once
#include "IGUIEnum.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ITextProperty
		{
		protected:
			virtual ~ITextProperty(){}
		public:
			virtual Void setFontResource(NSResourceSystem::IResource * resource)=0;
			virtual NSResourceSystem::IResource * getFontResource()const=0;
			virtual Void setFontSize(const CFloat2 & size)=0;
			virtual const CFloat2 & getFontSize()const=0;
			virtual Void setColour(const CColour & colour)=0;
			virtual const CColour & getColour()const=0;
			virtual Void setRowAlignMode(IEnum::ETextRowAlignMode mode)=0;
			virtual IEnum::ETextRowAlignMode getRowAlignMode()const=0;
			virtual Void setColumeAlignMode(IEnum::ETextColumeAlignMode mode)=0;
			virtual IEnum::ETextColumeAlignMode getColumeAlignMode()const=0;
		};
	}
}