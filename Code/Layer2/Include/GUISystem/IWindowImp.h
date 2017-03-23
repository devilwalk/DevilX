#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISceneImp;
		class IWindowImp
			:public IWindow
			,public TBaseObject<IWindowImp>
		{
		protected:
			IControlImp * mControl;
			ISceneImp * const mScene;
			TNamedResourcePtrMap<IControlImp> mControls;
		public:
			IWindowImp(const String & name,ISceneImp * scene);
			~IWindowImp();

			// Í¨¹ý IWindow ¼Ì³Ð
			virtual IControl * queryInterface_IControl() const override;
			virtual IScene * getScene() const override;
			virtual IStaticText * createStaticText(const String & name) override;
			virtual IButton * createButton(const String & name) override;
			virtual Void destroyControl(IControl * control) override;
		};
	}
}