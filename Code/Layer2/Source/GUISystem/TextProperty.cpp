#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CTextProperty::CTextProperty()
	:mFontResource(nullptr)
	,mRowAlignMode(IEnum::ETextRowAlignMode_Center)
	,mColumeAlignMode(IEnum::ETextColumeAlignMode_Center)
	,mFontSize(CFloat2::sOne)
{}

NSDevilX::NSGUISystem::CTextProperty::~CTextProperty()
{}

Void NSDevilX::NSGUISystem::CTextProperty::copyFrom(const CTextProperty * prop)
{
	setFontResource(prop->getFontResource());
	setFontSize(prop->getFontSize());
	setColour(prop->getColour());
	setRowAlignMode(prop->getRowAlignMode());
	setColumeAlignMode(prop->getColumeAlignMode());
}

Void NSDevilX::NSGUISystem::CTextProperty::setFontResource(NSResourceSystem::IResource * resource)
{
	if(getFontResource()!=resource)
	{
		mFontResource=resource;
		addDirtyFlag(EDirtyFlag_Font);
	}
}

Void NSDevilX::NSGUISystem::CTextProperty::setFontSize(const CFloat2 & size)
{
	assert(CFloat2(DirectX::XMVectorSaturate(size))==size);
	if(size!=getFontSize())
	{
		mFontSize=size;
		addDirtyFlag(EDirtyFlag_Font);
	}
}

Void NSDevilX::NSGUISystem::CTextProperty::setColour(const CColour & colour)
{
	if(getColour()!=colour)
	{
		mColour=colour;
		addDirtyFlag(EDirtyFlag_Colour);
	}
}

Void NSDevilX::NSGUISystem::CTextProperty::setRowAlignMode(IEnum::ETextRowAlignMode mode)
{
	if(getRowAlignMode()!=mode)
	{
		mRowAlignMode=mode;
		addDirtyFlag(EDirtyFlag_Font);
	}
}

Void NSDevilX::NSGUISystem::CTextProperty::setColumeAlignMode(IEnum::ETextColumeAlignMode mode)
{
	if(getColumeAlignMode()!=mode)
	{
		mColumeAlignMode=mode;
		addDirtyFlag(EDirtyFlag_Font);
	}
}

Void NSDevilX::NSGUISystem::CTextProperty::_postProcessDirtyFlagAdd(UInt32 flagIndex)
{
	notify(EMessage_AddDirtyFlag,&flagIndex);
}
