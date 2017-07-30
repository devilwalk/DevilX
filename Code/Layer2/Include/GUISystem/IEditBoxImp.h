#pragma once
#include "IControlImp.h"
#include "ITextPropertyImp.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindowImp;
		class IEditBoxImp
			:public IEditBox
			,public TBaseObject<IEditBoxImp>
			,public NSUISystem::IEventListener
			,public TMessageReceiver<CEditBox>
		{
		protected:
			IControlImp * mControl;
			ITextPropertyImp * mTextProperty;
			IEditBoxEventCallback * mEventCallback;
		public:
			IEditBoxImp(const String & name,IWindowImp * window);
			~IEditBoxImp();

			// ͨ�� IEdit �̳�
			virtual IControl * queryInterface_IControl() const override;
			virtual ITextProperty * getTextProperty() const override;
			virtual Void setText(const CUTF8String & text) override;
			virtual const CUTF8String & getText() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;
			virtual Void setEventCallback(IEditBoxEventCallback * callback) override;
			virtual IEditBoxEventCallback * getEventCallback() const override;

			// ͨ�� TMessageReceiver �̳�
			virtual Void onMessage(CEditBox * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

			// ͨ�� IEventListener �̳�
			virtual Void onEvent(NSUISystem::IEvent * e) override;
		};
	}
}