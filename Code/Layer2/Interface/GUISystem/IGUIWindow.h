#pragma once
#include "IGUIImageBox.h"
#include "IGUIStaticText.h"
#include "IGUIButton.h"
#include "IGUIEditBox.h"
#include "IGUIPageBar.h"
#include "IGUIComboBox.h"
#include "IGUIListBox.h"
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
			virtual IImageBox * createImageBox(const String & name)=0;
			virtual IImageBox * getImageBox(const String & name)const=0;
			virtual IStaticText * createStaticText(const String & name)=0;
			virtual IStaticText * getStaticText(const String & name)const=0;
			virtual IButton * createButton(const String & name)=0;
			virtual IButton * getButton(const String & name)const=0;
			virtual UInt32 getButtonCount()const=0;
			virtual IButton * getButton(UInt32 index)const=0;
			virtual IEditBox * createEditBox(const String & name)=0;
			virtual IEditBox * getEditBox(const String & name)const=0;
			virtual UInt32 getEditBoxCount()const=0;
			virtual IEditBox * getEditBox(UInt32 index)const=0;
			virtual IPageBar * createPageBar(const String & name)=0;
			virtual IPageBar * getPageBar(const String & name)const=0;
			virtual IComboBox * createComboBox(const String & name)=0;
			virtual IComboBox * getComboBox(const String & name)const=0;
			virtual IListBox * createListBox(const String & name)=0;
			virtual IListBox * getListBox(const String & name)const=0;
			virtual Void destroyControl(IControl * control)=0;
		};
	}
}