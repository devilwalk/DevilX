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
			,public TMessageReceiver<CButton>
			,public TMessageReceiver<ISystemImp>
		{
		protected:
			IControlImp * mControl;
			ITextPropertyImp * mTextProperty;
			IButtonEventCallback * mEventCallback;
			TVector<IButtonEventCallback::EEvent> mLastEvents;
		public:
			IButtonImp(const String & name,IWindowImp * window);
			~IButtonImp();

			// 通过 IButton 继承
			virtual IControl * queryInterface_IControl() const override;
			virtual ITextProperty * getTextProperty() const override;
			virtual Void setText(const CUTF8String & text) override;
			virtual const CUTF8String & getText() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;
			virtual Void setEventCallback(IButtonEventCallback * callback) override;
			virtual IButtonEventCallback * getEventCallback() const override;

			// 通过 TMessageReceiver 继承
			virtual Void onMessage(CButton * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}