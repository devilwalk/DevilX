#pragma once
#include "IGUIControl.h"
#include "IGUITextProperty.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IButton;
		class IButtonEventCallback
		{
		public:
			enum EEvent
			{
				EEvent_Press,
				EEvent_Release,
				EEvent_Click
			};
		protected:
			virtual ~IButtonEventCallback(){}
		public:
			virtual Void onEvent(IButton * control,EEvent events)=0;
		};
		class IButton
		{
		protected:
			virtual ~IButton(){}
		public:
			virtual IControl * queryInterface_IControl()const=0;
			virtual ITextProperty * getTextProperty()const=0;
			virtual Void setText(const CUTF8String & text)=0;
			virtual const CUTF8String & getText()const=0;
			virtual Void setBackground(NSResourceSystem::IResource * resource)=0;
			virtual NSResourceSystem::IResource * getBackground()const=0;
			virtual Void setEventCallback(IButtonEventCallback * callback)=0;
			virtual IButtonEventCallback * getEventCallback()const=0;
		};
	}
}