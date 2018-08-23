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
			TNamedResourcePtrMap(IEventSceneImp) mEventScenes;
			TResourcePtrMap(NSRenderSystem::IViewport*,IGraphicSceneImp) mGraphicScenes;
			TNamedResourcePtrMap(IElementImp) mLayers;
		public:
			ISystemImp();
			~ISystemImp();

			// Í¨¹ý ISystem ¼Ì³Ð
			virtual Void shutdown() override;
			virtual IEventScene * createEventScene(const String & name) override;
			virtual IEventScene * getEventScene(const String & name) const override;
			virtual Void destroyEventScene(IEventScene * scene) override;
			virtual IGraphicScene * createGraphicScene(NSRenderSystem::IViewport * viewport) override;
			virtual IGraphicScene * getGraphicScene(NSRenderSystem::IViewport * viewport) const override;
			virtual Void destroyGraphicScene(IGraphicScene * scene) override;
			virtual IElement * createLayer(const String & name) override;
			virtual IElement * getLayer(const String & name) const override;
			virtual Void destroyLayer(IElement * element) override;
		};
	}
}