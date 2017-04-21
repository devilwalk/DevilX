#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::ITextPropertyImp::ITextPropertyImp(CTextProperty * prop)
	:mProperty(prop)
{}

NSDevilX::NSGUISystem::ITextPropertyImp::~ITextPropertyImp()
{}

Void NSDevilX::NSGUISystem::ITextPropertyImp::setFontResource(NSResourceSystem::IResource * resource)
{
	mProperty->setFontResource(resource);
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::ITextPropertyImp::getFontResource() const
{
	return mProperty->getFontResource();
}

Void NSDevilX::NSGUISystem::ITextPropertyImp::setFontSize(const CFloat2 & size)
{
	mProperty->setFontSize(size);
}

const CFloat2 & NSDevilX::NSGUISystem::ITextPropertyImp::getFontSize() const
{
	// TODO: 在此处插入 return 语句
	return mProperty->getFontSize();
}

Void NSDevilX::NSGUISystem::ITextPropertyImp::setColour(const CColour & colour)
{
	mProperty->setColour(colour);
}

const CColour & NSDevilX::NSGUISystem::ITextPropertyImp::getColour() const
{
	// TODO: 在此处插入 return 语句
	return mProperty->getColour();
}

Void NSDevilX::NSGUISystem::ITextPropertyImp::setRowAlignMode(IEnum::ETextRowAlignMode mode)
{
	mProperty->setRowAlignMode(mode);
}

IEnum::ETextRowAlignMode NSDevilX::NSGUISystem::ITextPropertyImp::getRowAlignMode() const
{
	return mProperty->getRowAlignMode();
}

Void NSDevilX::NSGUISystem::ITextPropertyImp::setColumeAlignMode(IEnum::ETextColumeAlignMode mode)
{
	mProperty->setColumeAlignMode(mode);
}

IEnum::ETextColumeAlignMode NSDevilX::NSGUISystem::ITextPropertyImp::getColumeAlignMode() const
{
	return mProperty->getColumeAlignMode();
}
