#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IComboBoxImp::IComboBoxImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
	,mTextProperty(nullptr)
	,mEventCallback(nullptr)
{
	mControl=DEVILX_NEW IControlImp(IControlImp::EType_ComboBox,DEVILX_NEW CComboBox(name,static_cast<IControlImp*>(window->queryInterface_IControl())->getControl(),static_cast<IControlImp*>(window->queryInterface_IControl())->getControl()),window);
	mControl->getControl()->getEventWindow()->registerListener(this,CEvent::EType_MouseMove);
	mTextProperty=DEVILX_NEW ITextPropertyImp(static_cast<CComboBox*>(mControl->getControl())->getTextControl()->getTextProperty());
	static_cast<CEditBox*>(mControl->getControl())->addListener(static_cast<TMessageReceiver<CComboBox>*>(this),CComboBox::EMessage_SetFocus);
	static_cast<CEditBox*>(mControl->getControl())->addListener(static_cast<TMessageReceiver<CComboBox>*>(this),CComboBox::EMessage_EndTextChange);
}

NSDevilX::NSGUISystem::IComboBoxImp::~IComboBoxImp()
{
	DEVILX_DELETE(mControl);
	DEVILX_DELETE(mTextProperty);
}
