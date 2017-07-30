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
		{
		protected:
			IControlImp * mControl;
		public:
			IImageBoxImp(const String & name,IWindowImp * window);
			~IImageBoxImp();

			// Í¨¹ý IImageBox ¼Ì³Ð
			virtual IControl * queryInterface_IControl() const override;
			virtual Void setBackground(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getBackground() const override;
		};
	}
}