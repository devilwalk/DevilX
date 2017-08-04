#pragma once
#include "Control.h"
#include "GraphicWindowTextureUtility.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CImageBox
			:public CControl
			,public TBaseObject<CImageBox>
		{
		protected:
			CGraphicWindowTextureUtility * mBackground;
		public:
			CImageBox(const String & name,CControl * coordParent,CControl * orderParent);
			~CImageBox();
			Void setBackground(NSResourceSystem::IResource * resource);
			NSResourceSystem::IResource * getBackground()const;
			Void setBackgroundColour(const CColour & colour);
			const CColour & getBackgroundColour()const;
		};
	}
}