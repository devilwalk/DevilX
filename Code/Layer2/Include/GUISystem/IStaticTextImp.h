#pragma once
#include "IControlImp.h"
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
		public:
			IStaticTextImp(const String & name,IWindowImp * window);
			~IStaticTextImp();

			// ͨ�� IStaticText �̳�
			virtual IControl * queryInterface_IControl() const override;
			virtual Void setFontResource(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getFontResource() const override;
			virtual Void setText(const CUTF8String & text) override;
			virtual const CUTF8String & getText() const override;
			virtual Void setTextColour(const CColour & colour) override;
			virtual const CColour & getTextColour() const override;

			// ͨ�� TMessageReceiver �̳�
			virtual Void onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}