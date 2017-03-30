#pragma once
#include "IControlImp.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindowImp;
		class IImageBoxImp
			:public IImageBox
			,public TBaseObject<IImageBoxImp>
			,public TMessageReceiver<IControlImp>
		{
		protected:
			IControlImp * mControl;
		public:
			IImageBoxImp(const String & name,IWindowImp * window);
			~IImageBoxImp();

			// 通过 IImageBox 继承
			virtual IControl * queryInterface_IControl() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;

			// 通过 TMessageReceiver 继承
			virtual Void onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}