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

			// ͨ�� IImageBox �̳�
			virtual IControl * queryInterface_IControl() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;

			// ͨ�� TMessageReceiver �̳�
			virtual Void onMessage(IControlImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}