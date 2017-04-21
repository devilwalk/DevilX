#pragma once
#include "IControlImp.h"
#include "ITextPropertyImp.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindowImp;
		class IButtonImp
			:public IButton
			,public TBaseObject<IButtonImp>
			,public TMessageReceiver<IControlImp>
			,public NSUISystem::IEventListener
			,public TMessageReceiver<CButton>
		{
		protected:
			IControlImp * mControl;
			ITextPropertyImp * mTextProperty;
			IButtonEventCallback * mEventCallback;
		public:
			IButtonImp(const String & name,IWindowImp * window);
			~IButtonImp();

			// ͨ�� IButton �̳�
			virtual IControl * queryInterface_IControl() const override;
			virtual ITextProperty * getTextProperty() const override;
			virtual Void setText(const CUTF8String & text) override;
			virtual const CUTF8String & getText() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;
			virtual Void setEventCallback(IButtonEventCallback * callback) override;
			virtual IButtonEventCallback * getEventCallback() const override;

			// ͨ�� TMessageReceiver �̳�
			virtual Void onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Void onMessage(CButton * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

			// ͨ�� IEventListener �̳�
			virtual Void onEvent(NSUISystem::IEvent * e) override;
		};
	}
}