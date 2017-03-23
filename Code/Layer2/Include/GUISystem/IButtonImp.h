#pragma once
#include "IControlImp.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindowImp;
		class IButtonImp
			:public IButton
			,public TBaseObject<IButtonImp>
			,public TMessageReceiver<IControlImp>
		{
		protected:
			IControlImp * mControl;
		public:
			IButtonImp(const String & name,IWindowImp * window);
			~IButtonImp();

			// 通过 IButton 继承
			virtual IControl * queryInterface_IControl() const override;
			virtual Void setFontResource(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getFontResource() const override;
			virtual Void setText(const CUTF8String & text) override;
			virtual const CUTF8String & getText() const override;
			virtual Void setTextColour(const CColour & colour) override;
			virtual const CColour & getTextColour() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;
			virtual Void setEventCallback(IButtonEventCallback * callback) override;
			virtual IButtonEventCallback * getEventCallback() const override;

			// 通过 TMessageReceiver 继承
			virtual Void onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}