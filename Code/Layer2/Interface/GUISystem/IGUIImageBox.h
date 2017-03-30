#pragma once
#include "IGUIControl.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IImageBox
		{
		protected:
			virtual ~IImageBox(){}
		public:
			virtual IControl * queryInterface_IControl()const=0;
			virtual Void setBackground(NSResourceSystem::IResource * resource)=0;
			virtual NSResourceSystem::IResource * getBackground()const=0;
		};
	}
}