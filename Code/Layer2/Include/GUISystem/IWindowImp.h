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
			ISceneImp * const mScene;
			IControlImp * mControl;
		public:
			IWindowImp(const String & name,ISceneImp * scene);
			~IWindowImp();

			// Í¨¹ý IWindow ¼Ì³Ð
			virtual IControl * queryInterface_IControl() const override;
			virtual IScene * getScene() const override;
			virtual IStaticText * createStaticText(const String & name) override;
			virtual IButton * createButton(const String & name) override;
		};
	}
}