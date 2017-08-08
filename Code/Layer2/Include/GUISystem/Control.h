#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CContainer;
		class CControl
			:public NSUISystem::IEventListener
		{
		protected:
			NSUISystem::IGraphicScene * const mGraphicScene;
			NSUISystem::IEventScene * const mEventScene;
			CContainer * const mContainer;
			CControl * mCoordParent;
			CControl * mOrderParent;
			NSUISystem::IElement * mLayer;
			TVector<NSUISystem::IGraphicWindow*> mGraphicWindows;
			NSUISystem::IEventWindow * mEventWindow;
			Bool mVisible;
		public:
			CControl(const String & name,NSUISystem::IGraphicScene * graphicScene,NSUISystem::IEventScene * eventScene);
			CControl(const String & name,CControl * coordParent,CControl * orderParent,Bool createEventWindow=True);
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
			Bool getVisible()const
			{
				return mVisible;
			}
			virtual Void setVisible(Bool visible);
			virtual Void setPrepareFocus(Bool focus){}
			virtual Void setFocus(Bool focus){}
		protected:
			Void _attachWindow(NSUISystem::IGraphicWindow * window);
			Void _attachWindow(NSUISystem::IEventWindow * window);
			Void _destroyGraphicWindows();
			Void _destroyEventWindow();

			// Í¨¹ý IEventListener ¼Ì³Ð
			virtual Void onEvent(NSUISystem::IEvent * e) override;
		};
		class CContainer
			:public CControl
			,public TBaseObject<CContainer>
		{
		protected:
			TSet<CControl*> mPrepareFocusControls;
			TSet<CControl*> mFocusControls;
		public:
			using CControl::CControl;
			~CContainer();
			Void update();
			Void setPrepareFocusControl(CControl * control);
			Void addPrepareFocusControl(CControl * control);
			Void removePrepareFocusControl(CControl * control);
			Void setFocusControl(CControl * control);
			Void addFocusControl(CControl * control);
			Void removeFocusControl(CControl * control);
		};
	}
}