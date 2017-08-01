#pragma once
#include "Control.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindowImp;
		class IControlImp
			:public IControl
			,public TBaseObject<IControlImp>
		{
		public:
			enum EType
			{
				EType_Container,
				EType_StaticText,
				EType_Button,
				EType_ImageBox,
				EType_EditBox,
				EType_PageBar,
				EType_ComboBox
			};
		protected:
			EType const mType;
			IWindowImp * const mParentWindow;
			CControl * const mControl;
			IControlImp * mParentControl;
		public:
			IControlImp(EType type,CControl * control,IWindowImp * parentWindow);
			~IControlImp();
			EType getType()const
			{
				return mType;
			}
			CControl * getControl()const
			{
				return mControl;
			}
			Void setPrepareFocus(Bool focus)
			{
				mControl->setPrepareFocus(focus);
			}
			Void setFocus(Bool focus)
			{
				mControl->setFocus(focus);
			}
			// Í¨¹ý IControl ¼Ì³Ð
			virtual const String & getName() const override;
			virtual Void setPosition(const CFloat2 & position) override;
			virtual const CFloat2 & getPosition() const override;
			virtual Void setSize(const CFloat2 & size) override;
			virtual const CFloat2 & getSize() const override;
			virtual Void setParent(IControl * control) override;
			virtual IControl * getParent() const override;
			virtual IWindow * getParentWindow() const override;
		};
	}
}