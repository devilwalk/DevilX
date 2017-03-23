#pragma once
#include "IGUIControl.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IButtonEventCallback
		{
		public:
			enum EEvent
			{
				EEvent_MouseEnter,
				EEvent_MouseLeave,
				EEvent_MouseClick
			};
		protected:
			virtual ~IButtonEventCallback(){}
		public:
			virtual Void onEvent(EEvent events)=0;
		};
		class IButton
		{
		protected:
			virtual ~IButton(){}
		public:
			virtual IControl * queryInterface_IControl()const=0;
			virtual Void setFontResource(NSResourceSystem::IResource * resource)=0;
			virtual NSResourceSystem::IResource * getFontResource()const=0;
			virtual Void setText(const CUTF8String & text)=0;
			virtual const CUTF8String & getText()const=0;
			virtual Void setTextColour(const CColour & colour)=0;
			virtual const CColour & getTextColour()const=0;
			virtual Void setBackground(NSResourceSystem::IResource * resource)=0;
			virtual NSResourceSystem::IResource * getBackground()const=0;
			virtual Void setEventCallback(IButtonEventCallback * callback)=0;
			virtual IButtonEventCallback * getEventCallback()const=0;
		};
	}
}