#pragma once
#include "IControlImp.h"
#include "ITextPropertyImp.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindowImp;
		class IStaticTextImp
			:public IStaticText
			,public TBaseObject<IStaticTextImp>
		{
		protected:
			IControlImp * mControl;
			ITextPropertyImp * mTextProperty;
		public:
			IStaticTextImp(const String & name,IWindowImp * window);
			~IStaticTextImp();

			// Í¨¹ý IStaticText ¼Ì³Ð
			virtual IControl * queryInterface_IControl() const override;
			virtual ITextProperty * getTextProperty() const override;
			virtual Void setText(const CUTF8String & text) override;
			virtual const CUTF8String & getText() const override;
		};
	}
}