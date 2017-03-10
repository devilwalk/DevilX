#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindowImp;
		class IControlImp
			:public IControl
			,public TBaseObject<IControlImp>
		{
		protected:
			const String mName;
			IWindowImp * const mParentWindow;
			NSUISystem::IElement * mLayer;
			TVector<NSUISystem::IGraphicWindow*> mGraphicWindows;
		public:
			IControlImp(const String & name,IWindowImp * parentWindow);
			~IControlImp();
			Void attachGraphicWindow(NSUISystem::IGraphicWindow * window);
			// Í¨¹ý IControl ¼Ì³Ð
			virtual NSUISystem::IElement * queryInterface_IElement() const override;
			virtual IWindow * getParentWindow() const override;
		};
	}
}