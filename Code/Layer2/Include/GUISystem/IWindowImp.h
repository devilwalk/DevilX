#pragma once
#include "IButtonImp.h"
#include "IImageBoxImp.h"
#include "IEditBoxImp.h"
#include "IPageBarImp.h"
#include "IComboBoxImp.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISceneImp;
		class IWindowImp
			:public IWindow
			,public TBaseObject<IWindowImp>
			,public NSUISystem::IEventListener
		{
		protected:
			NSUISystem::IEventWindow * mEventWindow;
			NSUISystem::IEventScene * mEventScene;
			Bool mIsModule;
			IControlImp * mControl;
			ISceneImp * const mScene;
			TNamedIndexResourcePtrContainer<IButtonImp> mButtons;
			TNamedIndexResourcePtrContainer<IImageBoxImp> mImageBoxes;
			TNamedIndexResourcePtrContainer<IEditBoxImp> mEditBoxes;
			TNamedIndexResourcePtrContainer<IStaticTextImp> mStaticTexts;
			TNamedIndexResourcePtrContainer<IPageBarImp> mPageBars;
			TNamedIndexResourcePtrContainer<IComboBoxImp> mComboBoxs;
		public:
			IWindowImp(const String & name,ISceneImp * scene,Bool isModule);
			~IWindowImp();
			Bool isModule()const
			{
				return mIsModule;
			}
			Void update();
			// 通过 IWindow 继承
			virtual IControl * queryInterface_IControl() const override;
			virtual IScene * getScene() const override;
			virtual IImageBox * createImageBox(const String & name) override;
			virtual IStaticText * createStaticText(const String & name) override;
			virtual IButton * createButton(const String & name) override;
			virtual IEditBox * createEditBox(const String & name) override;
			virtual Void destroyControl(IControl * control) override;

			// 通过 IEventListener 继承
			virtual Void onEvent(NSUISystem::IEvent * e) override;

			// 通过 IWindow 继承
			virtual IImageBox * getImageBox(const String & name) const override;
			virtual IStaticText * getStaticText(const String & name) const override;
			virtual IButton * getButton(const String & name) const override;
			virtual IEditBox * getEditBox(const String & name) const override;

			// 通过 IWindow 继承
			virtual IPageBar * createPageBar(const String & name) override;
			virtual IPageBar * getPageBar(const String & name) const override;

			// 通过 IWindow 继承
			virtual UInt32 getButtonCount() const override;
			virtual IButton * getButton(UInt32 index) const override;
			virtual UInt32 getEditBoxCount() const override;
			virtual IEditBox * getEditBox(UInt32 index) const override;

			// 通过 IWindow 继承
			virtual IComboBox * createComboBox(const String & name) override;
			virtual IComboBox * getComboBox(const String & name) const override;

			// 通过 IWindow 继承
			virtual IListBox * createListBox(const String & name) override;
			virtual IListBox * getListBox(const String & name) const override;
		};
	}
}