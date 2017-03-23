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
			TResourcePtrMap<NSRenderSystem::IViewport*,ISceneImp> mScenes;
		public:
			ISystemImp();
			~ISystemImp();

			// ͨ�� ISystem �̳�
			virtual IScene * createScene(NSRenderSystem::IViewport * viewport) override;
			virtual IScene * getScene(NSRenderSystem::IViewport * viewport) const override;
			virtual Void destroyScene(IScene * scene) override;
			virtual Void update() override;
			virtual Void shutdown() override;
		};
	}
}