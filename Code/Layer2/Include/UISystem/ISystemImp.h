#pragma once
#include "IEventSceneImp.h"
#include "IGraphicSceneImp.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class ISystemImp
			:public ISystem
			,public TBaseObject<ISystemImp>
			,public TSingletonEx<ISystemImp>
		{
		protected:
			TNamedResourcePtrMap<IEventSceneImp> mEventScenes;
			TResourcePtrMap<NSRenderSystem::IViewport*,IGraphicSceneImp> mGraphicScenes;
		public:
			ISystemImp();
			~ISystemImp();

			// Í¨¹ý ISystem ¼Ì³Ð
			virtual IEventScene * createEventScene(const String & name) override;
			virtual IEventScene * getEventScene(const String & name) const override;
			virtual Void destroyEventScene(IEventScene * scene) override;
			virtual IGraphicScene * createGraphicScene(NSRenderSystem::IViewport * viewport) override;
			virtual IGraphicScene * getGraphicScene(NSRenderSystem::IViewport * viewport) const override;
			virtual Void destroyGraphicScene(IGraphicScene * scene) override;
		};
	}
}