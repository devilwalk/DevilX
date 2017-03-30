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
		public:
			struct SEvent
				:public NSUISystem::IEvent
				,public TBaseObject<SEvent>
			{
				enum EType
				{
					EType_ControlFocus
				};
				const EType mType;
				NSUISystem::IElement * mLayer;
				SEvent(EType type);
				~SEvent();
				// 通过 IEvent 继承
				virtual NSUISystem::IElement * queryInterface_IElement() const override;
				virtual UInt32 getType() const override;
			};
		protected:
			NSUISystem::IEventWindow * mEventWindow;
			NSUISystem::IEventScene * mEventScene;
			IControlImp * mControl;
			IControlImp * mFocusControl;
			ISceneImp * const mScene;
			TNamedResourcePtrMap<IControlImp> mControls;
		public:
			IWindowImp(const String & name,ISceneImp * scene);
			~IWindowImp();
			Void update();
			Void setFocusControl(IControlImp * control);
			// 通过 IWindow 继承
			virtual IControl * queryInterface_IControl() const override;
			virtual IScene * getScene() const override;
			virtual IImageBox * createImageBox(const String & name) override;
			virtual IStaticText * createStaticText(const String & name) override;
			virtual IButton * createButton(const String & name) override;
			virtual IEditBox * createEditBox(const String & name) override;
			virtual Void destroyControl(IControl * control) override;

			// 通过 IEventListener 继承
			virtual Void onEvent(NSUISystem::IEvent * e) override;
		};
	}
}