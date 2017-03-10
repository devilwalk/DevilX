#pragma once
#include "IGUIControl.h"
#include "IGUIStaticText.h"
#include "IGUIButton.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IScene;
		class IWindow
		{
		protected:
			virtual ~IWindow(){}
		public:
			virtual IControl * queryInterface_IControl()const=0;
			virtual IScene * getScene()const=0;
			virtual IStaticText * createStaticText(const String & name)=0;
			virtual IButton * createButton(const String & name)=0;
			virtual Void destroyControl(IControl * control);
		};
	}
}