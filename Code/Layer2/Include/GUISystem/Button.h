#pragma once
#include "Control.h"
#include "StaticText.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CButton
			:public CControl
			,public TBaseObject<CButton>
		{
		protected:
			CStaticText * mTextControl;
			NSResourceSystem::IResource * mBackgroundResource;
		public:
			CButton(const String & name,CControl * parent);
			~CButton();
			CStaticText * getTextControl()const
			{
				return mTextControl;
			}
			Void setBackground(NSResourceSystem::IResource * resource);
			NSResourceSystem::IResource * getBackground()const;
		};
	}
}