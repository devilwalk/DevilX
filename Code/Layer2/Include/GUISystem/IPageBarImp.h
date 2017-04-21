#pragma once
#include "IControlImp.h"
#include "ITextPropertyImp.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IPageBarImp
			:public IPageBar
			,public TBaseObject<IPageBarImp>
			,public TMessageReceiver<IControlImp>
			,public NSUISystem::IEventListener
		{
		protected:
			IControlImp * mControl;
			ITextPropertyImp * mTextProperty;
			IPageBarEventCallback * mEventCallback;
		public:
			IPageBarImp(const String & name,IWindowImp * window);
			~IPageBarImp();

			// 通过 IPageBar 继承
			virtual IControl * queryInterface_IControl() const override;
			virtual ITextProperty * getTextProperty() const override;
			virtual Void addPage(const CUTF8String & text) override;
			virtual const CUTF8String & getPage(UInt32 index) const override;
			virtual Void removePage(UInt32 index) override;
			virtual UInt32 getActivePageIndex() const override;
			virtual Void setEventCallback(IPageBarEventCallback * callback) override;
			virtual IPageBarEventCallback * getEventCallback() const override;

			// 通过 TMessageReceiver 继承
			virtual Void onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

			// 通过 IEventListener 继承
			virtual Void onEvent(NSUISystem::IEvent * e) override;
		};
	}
}