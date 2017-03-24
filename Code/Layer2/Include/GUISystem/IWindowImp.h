#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISceneImp;
		class IWindowImp
			:public IWindow
			,public TBaseObject<IWindowImp>
			,public NSUISystem::IEventListener
			,public CDefaultWindowEventListener
		{
		protected:
			NSUISystem::IEventWindow * mEventWindow;
			NSUISystem::IEventScene * mEventScene;
			IControlImp * mControl;
			ISceneImp * const mScene;
			TNamedResourcePtrMap<IControlImp> mControls;
		public:
			IWindowImp(const String & name,ISceneImp * scene);
			~IWindowImp();
			Void setActive(Bool active);
			// ͨ�� IWindow �̳�
			virtual IControl * queryInterface_IControl() const override;
			virtual IScene * getScene() const override;
			virtual IStaticText * createStaticText(const String & name) override;
			virtual IButton * createButton(const String & name) override;
			virtual Void destroyControl(IControl * control) override;

			// ͨ�� IEventListener �̳�
			virtual Void onEvent(NSUISystem::IEvent * e) override;
		};
	}
}