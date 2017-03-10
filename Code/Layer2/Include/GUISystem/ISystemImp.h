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
				EMessage_BeginFontManagerChange,
				EMessage_EndFontManagerChange,
				EMessage_BeginFontNameChange,
				EMessage_EndFontNameChange
			};
		protected:
			CFontManager * mFontManager;
			String mFontName;
			TResourcePtrMap<NSRenderSystem::IViewport*,ISceneImp> mScenes;
		public:
			ISystemImp();
			~ISystemImp();

			// Í¨¹ý ISystem ¼Ì³Ð
			virtual Void setFontManager(CFontManager * manager) override;
			virtual CFontManager * getFontManager() const override;
			virtual Void setFontName(const String & fontName) override;
			virtual const String & getFontName() const override;
			virtual IScene * createScene(NSRenderSystem::IViewport * viewport) override;
			virtual IScene * getScene(NSRenderSystem::IViewport * viewport) const override;
			virtual Void destroyScene(IScene * scene) override;
			virtual Void shutdown() override;
		};
	}
}