#pragma once
#include "IGraphicWindowImp.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IGraphicSceneImp
			:public TBaseObject<IGraphicSceneImp>
			,public IGraphicScene
		{
		protected:
			NSRenderSystem::IViewport * const mViewport;
			TNamedResourcePtrMap(IGraphicWindowImp) mWindows;
		public:
			IGraphicSceneImp(NSRenderSystem::IViewport * viewport);
			~IGraphicSceneImp();

			// Í¨¹ý IGraphicScene ¼Ì³Ð
			virtual NSRenderSystem::IViewport * getRenderViewport() const override;
			virtual IGraphicWindow * createWindow(const String & name) override;
			virtual IGraphicWindow * getWindow(const String & name) const override;
			virtual Void destroyWindow(IGraphicWindow * window) override;
		};
	}
}