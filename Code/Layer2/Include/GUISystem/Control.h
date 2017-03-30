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
			CControl * mParent;
			NSUISystem::IElement * mLayer;
			TVector<NSUISystem::IGraphicWindow*> mGraphicWindows;
			NSUISystem::IEventWindow * mEventWindow;
		public:
			CControl(const String & name,NSUISystem::IGraphicScene * graphicScene,NSUISystem::IEventScene * eventScene);
			CControl(const String & name,CControl * parent);
			virtual ~CControl();
			NSUISystem::IGraphicScene * getGraphicScene()const
			{
				return mGraphicScene;
			}
			NSUISystem::IEventScene * getEventScene()const
			{
				return mEventScene;
			}
			Void setParent(CControl * control);
			CControl * getParent()const
			{
				return mParent;
			}
			NSUISystem::IElement * getLayer()const
			{
				return mLayer;
			}
			NSUISystem::IEventWindow * getEventWindow()const
			{
				return mEventWindow;
			}
			virtual Void setFocus(Bool focus){}
		protected:
			Void _attachWindow(NSUISystem::IGraphicWindow * window);
			Void _attachWindow(NSUISystem::IEventWindow * window);
			Void _destroyGraphicWindows();
			Void _destroyEventWindow();
		};
	}
}