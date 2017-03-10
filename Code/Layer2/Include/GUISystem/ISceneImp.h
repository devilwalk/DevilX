#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISceneImp
			:public IScene
			,public TBaseObject<ISceneImp>
		{
		protected:
			NSUISystem::IGraphicScene * mGraphicScene;
			TNamedResourcePtrMap<IWindowImp> mWindows;
		public:
			ISceneImp(NSRenderSystem::IViewport * viewport);
			~ISceneImp();
			NSUISystem::IGraphicScene * getGraphicScene()const
			{
				return mGraphicScene;
			}
			// ͨ�� IScene �̳�
			virtual NSRenderSystem::IViewport * getRenderViewport() const override;
			virtual IWindow * createWindow(const String & name) override;
			virtual IWindow * getWindow(const String & name) const override;
			virtual Void destroyWindow(IWindow * window) override;
		};
	}
}