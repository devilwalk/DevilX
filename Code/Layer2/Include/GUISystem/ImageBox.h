#pragma once
#include "Control.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CImageBox
			:public CControl
			,public TBaseObject<CImageBox>
		{
		protected:
			NSResourceSystem::IResource * mBackgroundResource;
		public:
			CImageBox(const String & name,CControl * parent);
			~CImageBox();
			Void setBackground(NSResourceSystem::IResource * resource);
			NSResourceSystem::IResource * getBackground()const;
		};
	}
}