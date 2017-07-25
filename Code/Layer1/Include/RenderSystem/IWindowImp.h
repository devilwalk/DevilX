#pragma once
#include "IRenderTargetImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IWindowImp
			:public IWindow
			,public IRenderTargetImp
			,public TBaseObject<IWindowImp>
		{
		protected:
			CWindow * const mWindow;
		public:
			IWindowImp(CWindow * window);
			// Inherited via IWindow
			virtual IRenderTarget * queryInterface_IRenderTarget() const override;
			virtual CWindow * getWindow() const override;
		protected:
			~IWindowImp();
		};
	}
}