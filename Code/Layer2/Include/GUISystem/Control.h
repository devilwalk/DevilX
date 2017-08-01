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
			CControl * mCoordParent;
			CControl * mOrderParent;
			NSUISystem::IElement * mLayer;
			TVector<NSUISystem::IGraphicWindow*> mGraphicWindows;
			NSUISystem::IEventWindow * mEventWindow;
		public:
			CControl(const String & name,NSUISystem::IGraphicScene * graphicScene,NSUISystem::IEventScene * eventScene);
			CControl(const String & name,CControl * coordParent,CControl * orderParent);
			virtual ~CControl();
			NSUISystem::IGraphicScene * getGraphicScene()const
			{
				return mGraphicScene;
			}
			NSUISystem::IEventScene * getEventScene()const
			{
				return mEventScene;
			}
			Void setCoordParent(CControl * control);
			CControl * getCoordParent()const
			{
				return mCoordParent;
			}
			Void setOrderParent(CControl * control);
			CControl * getOrderParent()const
			{
				return mOrderParent;
			}
			NSUISystem::IElement * getLayer()const
			{
				return mLayer;
			}
			NSUISystem::IEventWindow * getEventWindow()const
			{
				return mEventWindow;
			}
			virtual Void setPrepareFocus(Bool focus){}
			virtual Void setFocus(Bool focus){}
		protected:
			Void _attachWindow(NSUISystem::IGraphicWindow * window);
			Void _attachWindow(NSUISystem::IEventWindow * window);
			Void _destroyGraphicWindows();
			Void _destroyEventWindow();
		};
		class CContainer
			:public CControl
			,public TBaseObject<CContainer>
		{
		public:
			using CControl::CControl;
		};
	}
}