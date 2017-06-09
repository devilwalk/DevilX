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
		{
		protected:
			NSUISystem::IEventWindow * mEventWindow;
			NSUISystem::IEventScene * mEventScene;
			Bool mIsModule;
			IControlImp * mControl;
			IControlImp * mPrepareFocusControl;
			IControlImp * mFocusControl;
			ISceneImp * const mScene;
			TNamedResourcePtrMap<IControlImp> mControls;
		public:
			IWindowImp(const String & name,ISceneImp * scene,Bool isModule);
			~IWindowImp();
			Bool isModule()const
			{
				return mIsModule;
			}
			Void update();
			Void setPrepareFocusControl(IControlImp * control);
			Void setFocusControl(IControlImp * control);
			// ͨ�� IWindow �̳�
			virtual IControl * queryInterface_IControl() const override;
			virtual IScene * getScene() const override;
			virtual IImageBox * createImageBox(const String & name) override;
			virtual IStaticText * createStaticText(const String & name) override;
			virtual IButton * createButton(const String & name) override;
			virtual IEditBox * createEditBox(const String & name) override;
			virtual Void destroyControl(IControl * control) override;

			// ͨ�� IEventListener �̳�
			virtual Void onEvent(NSUISystem::IEvent * e) override;

			// ͨ�� IWindow �̳�
			virtual IImageBox * getImageBox(const String & name) const override;
			virtual IStaticText * getStaticText(const String & name) const override;
			virtual IButton * getButton(const String & name) const override;
			virtual IEditBox * getEditBox(const String & name) const override;

			// ͨ�� IWindow �̳�
			virtual IPageBar * createPageBar(const String & name) override;
			virtual IPageBar * getPageBar(const String & name) const override;
		};
	}
}