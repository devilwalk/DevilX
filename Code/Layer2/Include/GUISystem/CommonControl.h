#pragma once
#include "ImageBox.h"
#include "StaticText.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CCommonControl
			:public CControl
			,public TBaseObject<CCommonControl>
		{
		protected:
			CStaticText * mTextControl;
			CImageBox * mImageControl;
		public:
			CCommonControl(const String & name,CControl * coordParent,CControl * orderParent);
			virtual ~CCommonControl();
			CStaticText * getTextControl()const
			{
				return mTextControl;
			}
			CImageBox * getImageControl()const
			{
				return mImageControl;
			}
		};
	}
}