#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IEditBox;
		class IEditBoxEventCallback
		{
		public:
			enum EEvent
			{
				EEvent_TextChange
			};
		protected:
			virtual ~IEditBoxEventCallback()
			{}
		public:
			virtual Void onEvent(IEditBox * control,EEvent events)=0;
		};
		class IEditBox
		{
		protected:
			virtual ~IEditBox(){}
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
			virtual Void setEventCallback(IEditBoxEventCallback * callback)=0;
			virtual IEditBoxEventCallback * getEventCallback()const=0;
		};
	}
}