#pragma once
#include "IGUIControl.h"
#include "IGUITextProperty.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IPageBar;
		class IPageBarEventCallback
		{
		public:
			enum EEvent
			{
				EEvent_ActivePageChange
			};
		protected:
			virtual ~IPageBarEventCallback(){}
		public:
			virtual Void onEvent(IPageBar * control,EEvent e)=0;
		};
		class IPageBar
		{
		protected:
			virtual ~IPageBar(){}
		public:
			virtual IControl * queryInterface_IControl()const=0;
			virtual ITextProperty * getTextProperty()const=0;
			virtual Void addPage(const CUTF8String & text)=0;
			virtual const CUTF8String & getPage(UInt32 index)const=0;
			virtual Void removePage(UInt32 index)=0;
			virtual UInt32 getActivePageIndex()const=0;
			virtual Void setEventCallback(IPageBarEventCallback * callback)=0;
			virtual IPageBarEventCallback * getEventCallback()const=0;
		};
	}
}