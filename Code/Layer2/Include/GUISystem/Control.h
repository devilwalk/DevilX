#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CControl
		{
		protected:
			NSUISystem::IGraphicScene * const mGraphicScene;
			NSUISystem::IEventScene * const mEventScene;
			CControl * const mParent;
			NSUISystem::IElement * mLayer;
			TVector<NSUISystem::IGraphicWindow*> mGraphicWindows;
		public:
			CControl(const String & name,NSUISystem::IGraphicScene * graphicScene,NSUISystem::IEventScene * eventScene);
			CControl(const String & name,CControl * parent=nullptr);
			virtual ~CControl();
			NSUISystem::IGraphicScene * getGraphicScene()const
			{
				return mGraphicScene;
			}
			NSUISystem::IEventScene * getEventScene()const
			{
				return mEventScene;
			}
			CControl * getParent()const
			{
				return mParent;
			}
			NSUISystem::IElement * getLayer()const
			{
				return mLayer;
			}
		protected:
			Void _attachGraphicWindow(NSUISystem::IGraphicWindow * window);
			Void _destroyGraphicWindows();
		};
	}
}