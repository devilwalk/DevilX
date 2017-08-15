#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CContainer;
		class CControl
			:public NSUISystem::IEventListener
			,public TMessageReceiver<CMessageNotifier>
		{
		public:
			enum EMessage
			{
				EMessage_NeedRefreshOrderParent
			};
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
			CMessageNotifier * mNotifier;
		public:
			CControl(const String & name,NSUISystem::IGraphicScene * graphicScene,NSUISystem::IEventScene * eventScene);
			CControl(const String & name,CControl * coordParent,Bool createEventWindow=True);
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
			Void setInternalOrderParent(CControl * control);
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
			CUInt2 getSizeInPixel()const;
			virtual Void setVisible(Bool visible);
			virtual Void setPrepareFocus(Bool focus){}
			virtual Void setFocus(Bool focus){}
		protected:
			Void _attachWindow(NSUISystem::IGraphicWindow * window);
			Void _attachWindow(NSUISystem::IEventWindow * window);
			Void _destroyGraphicWindows();
			Void _destroyEventWindow();
			virtual Void _setOrderChild(CControl * control);
			// 通过 IEventListener 继承
			virtual Void onEvent(NSUISystem::IEvent * e) override;

			// 通过 TMessageReceiver 继承
			virtual Void onMessage(CMessageNotifier * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
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