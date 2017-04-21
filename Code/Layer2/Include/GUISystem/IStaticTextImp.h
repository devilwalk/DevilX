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
			,public TMessageReceiver<IControlImp>
		{
		protected:
			IControlImp * mControl;
			ITextPropertyImp * mTextProperty;
		public:
			IStaticTextImp(const String & name,IWindowImp * window);
			~IStaticTextImp();

			// ͨ�� IStaticText �̳�
			virtual IControl * queryInterface_IControl() const override;
			virtual ITextProperty * getTextProperty() const override;
			virtual Void setText(const CUTF8String & text) override;
			virtual const CUTF8String & getText() const override;

			// ͨ�� TMessageReceiver �̳�
			virtual Void onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}