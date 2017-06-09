#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISceneImp
			:public IScene
			,public TBaseObject<ISceneImp>
			,public CDefaultWindowEventListener
		{
		public:
			struct SEvent
				:public NSUISystem::IEvent
				,public TBaseObject<SEvent>
			{
				enum EType
				{
					EType_WindowActive
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
			NSUISystem::IGraphicScene * mGraphicScene;
			NSUISystem::IEventScene * mEventScene;
			IWindowImp * mActiveWindow;
			TNamedResourcePtrMap<IWindowImp> mWindows;
			TList<IWindowImp*> mOrderedWindows;
			TList<IWindowImp*> mOrderedModuleWindows;
		public:
			ISceneImp(NSRenderSystem::IViewport * viewport);
			~ISceneImp();
			NSUISystem::IGraphicScene * getGraphicScene()const
			{
				return mGraphicScene;
			}
			NSUISystem::IEventScene * getEventScene()const
			{
				return mEventScene;
			}
			Void update();
			Void setActiveWindow(IWindowImp * window);
			// 通过 IScene 继承
			virtual NSRenderSystem::IViewport * getRenderViewport() const override;
			virtual IWindow * createWindow(const String & name,Bool isModule) override;
			virtual IWindow * getWindow(const String & name) const override;
			virtual Void destroyWindow(IWindow * window) override;
		protected:
			Void _updateWindowsOrder();
			virtual Void onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position) override;
		};
	}
}