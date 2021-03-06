#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CEditBox::CEditBox(const String & name,CControl * coordParent)
	:CControl(name,coordParent)
	,mCommonControl(nullptr)
	,mCaret(nullptr)
	,mCaretPosition(0)
	,mPrepareFocus(False)
{
	mCommonControl=DEVILX_NEW CCommonControl(name+"/CommonControl",this);
	mCommonControl->setOrderParent(this);
	mCommonControl->getImageControl()->setBackgroundColour(CFloatRGB(0.8f));
	mCaret=DEVILX_NEW CCaret(name+"/Caret",this);
	mCaret->setOrderParent(getCommonControl());
	mCaret->getLayer()->setSize(CFloat2(0.01f,1.0f));
}

NSDevilX::NSGUISystem::CEditBox::~CEditBox()
{
	DEVILX_DELETE(mCommonControl);
	DEVILX_DELETE(mCaret);
}

Void NSDevilX::NSGUISystem::CEditBox::setText(const CUTF8String & text)
{
	_setText(text);
	mCaretPosition=text.size();
}

Void NSDevilX::NSGUISystem::CEditBox::setPrepareFocus(Bool focus)
{
	auto pre_value=mPrepareFocus||mCaret->isEnable();
	mPrepareFocus=focus;
	_updateListener(pre_value);
}

Void NSDevilX::NSGUISystem::CEditBox::setFocus(Bool focus)
{
	auto pre_value=mPrepareFocus||mCaret->isEnable();
	mCaret->setEnable(focus);
	_updateListener(pre_value);
}

Void NSDevilX::NSGUISystem::CEditBox::onMouseButtonEvent(CWindow * window,EMouseButtonType buttonType,EMouseButtonEventType eventType,const CUInt2 & position)
{
	if(False==mPrepareFocus)
		return;
	if((EMouseButtonType_Left==buttonType)&&(EMouseButtonEventType_Up==eventType))
	{
		if(!mCaret->isEnable())
			mContainer->setFocusControl(this);
		TVector<CFloat2> char_positions;
		Float last_char_right;
		if(mCommonControl->getTextControl()->getPositions(&char_positions,&last_char_right))
		{
			CFloat2 position_f=position/ISystemImp::getSingleton().getWindow()->getSize();
			TList<NSUISystem::IElement*> parents;
			auto * first_parent=getLayer()->getCoordParent();
			while(first_parent)
			{
				parents.push_front(first_parent);
				first_parent=first_parent->getCoordParent();
			}
			for(auto control:parents)
			{
				position_f=control->convertPosition(position_f,NSUISystem::IElement::ECoord_Parent,NSUISystem::IElement::ECoord_Local);
			}
			position_f=getLayer()->convertPosition(position_f,NSUISystem::IElement::ECoord_Parent,NSUISystem::IElement::ECoord_Local);
			position_f=getCommonControl()->getTextControl()->getLayer()->convertPosition(position_f,NSUISystem::IElement::ECoord_Parent,NSUISystem::IElement::ECoord_Local);
			TVector<Float> distances;
			for(auto const & char_pos:char_positions)
			{
				distances.push_back(fabs(char_pos.x-position_f.x));
			}
			distances.push_back(fabs(last_char_right-position_f.x));
			auto index=std::min_element(distances.begin(),distances.end())-distances.begin();
			mCaretPosition=static_cast<UInt32>(index);
		}
	}
}

Void NSDevilX::NSGUISystem::CEditBox::onCharEvent(CWindow * window,const CUTF16Char & ch)
{
	if(False==mCaret->isEnable())
		return;
	if(ch=='\b')
	{
		auto erase_pos=mCaretPosition;
		if(erase_pos>0)
		{
			erase_pos=erase_pos-1;
			auto text=getCommonControl()->getTextControl()->getText();
			text.erase(text.begin()+erase_pos);
			_setText(text);
			--mCaretPosition;
		}
	}
	else
	{
		auto text=getCommonControl()->getTextControl()->getText();
		text.insert(text.begin()+mCaretPosition,CUTF8Char(ch));
		_setText(text);
		++mCaretPosition;
	}
}

Void NSDevilX::NSGUISystem::CEditBox::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
	{
		CFloat2 pos(CFloat2::sZero);
		if(getCommonControl()->getTextControl()->getPosition(mCaretPosition,&pos))
		{
			pos=getCommonControl()->getTextControl()->getLayer()->convertPosition(pos,NSUISystem::IElement::ECoord_Local,NSUISystem::IElement::ECoord_Parent);
			mCaret->getLayer()->setPosition(CFloat2(pos.x,0.0f));
		}
	}
	break;
	}
}

Void NSDevilX::NSGUISystem::CEditBox::_setText(const CUTF8String & text)
{
	notify(EMessage_BeginTextChange);
	mCommonControl->getTextControl()->setText(text);
	notify(EMessage_EndTextChange);
}

Void NSDevilX::NSGUISystem::CEditBox::_updateListener(Bool preValue)
{
	Bool focus=mPrepareFocus||mCaret->isEnable();
	if(preValue!=focus)
	{
		if(focus)
		{
			ISystemImp::getSingleton().getWindow()->registerEventListener(this);
			ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
		}
		else
		{
			ISystemImp::getSingleton().getWindow()->unregisterEventListener(this);
			ISystemImp::getSingleton().removeListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
		}
	}
}

Void NSDevilX::NSGUISystem::CEditBox::_setOrderChild(CControl * control)
{
	if(control==mCommonControl)
	{
		CControl::_setOrderChild(control);
	}
	else
		assert(0);
}
