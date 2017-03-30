#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindowImp;
		class IEditBoxImp
			:public IEditBox
			,public TBaseObject<IEditBoxImp>
			,public TMessageReceiver<IControlImp>
			,public NSUISystem::IEventListener
			,public TMessageReceiver<CEditBox>
		{
		protected:
			IControlImp * mControl;
			IEditBoxEventCallback * mEventCallback;
		public:
			IEditBoxImp(const String & name,IWindowImp * window);
			~IEditBoxImp();

			// 通过 IEdit 继承
			virtual IControl * queryInterface_IControl() const override;
			virtual Void setFontResource(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getFontResource() const override;
			virtual Void setText(const CUTF8String & text) override;
			virtual const CUTF8String & getText() const override;
			virtual Void setTextColour(const CColour & colour) override;
			virtual const CColour & getTextColour() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;
			virtual Void setEventCallback(IEditBoxEventCallback * callback) override;
			virtual IEditBoxEventCallback * getEventCallback() const override;

			// 通过 TMessageReceiver 继承
			virtual Void onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Void onMessage(CEditBox * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

			// 通过 IEventListener 继承
			virtual Void onEvent(NSUISystem::IEvent * e) override;
		};
	}
}