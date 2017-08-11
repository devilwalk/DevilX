#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::ITextPropertyImp::ITextPropertyImp()
	:mProperty(nullptr)
{
	mProperty=DEVILX_NEW CTextProperty();
}

NSDevilX::NSGUISystem::ITextPropertyImp::~ITextPropertyImp()
{
	DEVILX_DELETE(mProperty);
}

Void NSDevilX::NSGUISystem::ITextPropertyImp::add(CTextProperty * prop)
{
	mPropertys.insert(prop);
	prop->copyFrom(mProperty);
}

Void NSDevilX::NSGUISystem::ITextPropertyImp::remove(CTextProperty * prop)
{
	mPropertys.remove(prop);
}

Void NSDevilX::NSGUISystem::ITextPropertyImp::setFontResource(NSResourceSystem::IResource * resource)
{
	mProperty->setFontResource(resource);
	for(auto prop:mPropertys)
		prop->setFontResource(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::ITextPropertyImp::getFontResource() const
{
	return mProperty->getFontResource();
}

Void NSDevilX::NSGUISystem::ITextPropertyImp::setColour(const CColour & colour)
{
	mProperty->setColour(colour);
	for(auto prop:mPropertys)
		prop->setColour(colour);
}

const CColour & NSDevilX::NSGUISystem::ITextPropertyImp::getColour() const
{
	// TODO: 在此处插入 return 语句
	return mProperty->getColour();
}

Void NSDevilX::NSGUISystem::ITextPropertyImp::setRowAlignMode(IEnum::ETextRowAlignMode mode)
{
	mProperty->setRowAlignMode(mode);
	for(auto prop:mPropertys)
		prop->setRowAlignMode(mode);
}

IEnum::ETextRowAlignMode NSDevilX::NSGUISystem::ITextPropertyImp::getRowAlignMode() const
{
	return mProperty->getRowAlignMode();
}

Void NSDevilX::NSGUISystem::ITextPropertyImp::setColumeAlignMode(IEnum::ETextColumeAlignMode mode)
{
	mProperty->setColumeAlignMode(mode);
	for(auto prop:mPropertys)
		prop->setColumeAlignMode(mode);
}

IEnum::ETextColumeAlignMode NSDevilX::NSGUISystem::ITextPropertyImp::getColumeAlignMode() const
{
	return mProperty->getColumeAlignMode();
}
