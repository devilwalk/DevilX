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
			CCommonControl(const String & name,CControl * coordParent);
			virtual ~CCommonControl();
			CStaticText * getTextControl()const
			{
				return mTextControl;
			}
			CImageBox * getImageControl()const
			{
				return mImageControl;
			}
			virtual Void setVisible(Bool visible) override;
		protected:
			virtual Void _setOrderChild(CControl * control) override;
		};
	}
}