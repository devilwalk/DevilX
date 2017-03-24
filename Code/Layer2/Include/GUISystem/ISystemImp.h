#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISystemImp
			:public ISystem
			,public TBaseObject<ISystemImp>
			,public TSingletonEx<ISystemImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_Update
			};
		protected:
			CWindow * mWindow;
			TResourcePtrMap<NSRenderSystem::IViewport*,ISceneImp> mScenes;
		public:
			ISystemImp();
			~ISystemImp();
			CWindow * getWindow()const
			{
				return mWindow;
			}
			// Í¨¹ý ISystem ¼Ì³Ð
			virtual Void initialize(CWindow * window) override;
			virtual IScene * createScene(NSRenderSystem::IViewport * viewport) override;
			virtual IScene * getScene(NSRenderSystem::IViewport * viewport) const override;
			virtual Void destroyScene(IScene * scene) override;
			virtual Void update() override;
			virtual Void shutdown() override;
		};
	}
}