#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IListBoxImp::IListBoxImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
{
}

NSDevilX::NSGUISystem::IListBoxImp::~IListBoxImp()
{}

IControl * NSDevilX::NSGUISystem::IListBoxImp::queryInterface_IControl() const
{
	return mControl;
}

ITextProperty * NSDevilX::NSGUISystem::IListBoxImp::getTextProperty() const
{
	return nullptr;
}

Void NSDevilX::NSGUISystem::IListBoxImp::setBackground(NSResourceSystem::IResource * resource)
{
	return Void();
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::IListBoxImp::getBackground() const
{
	return nullptr;
}

IListBoxItem * NSDevilX::NSGUISystem::IListBoxImp::getItem(UInt32 rowIndex,UInt32 columeIndex) const
{
	return nullptr;
}

Void NSDevilX::NSGUISystem::IListBoxImp::destroyItem(IListBoxItem * item)
{
	return Void();
}

Void NSDevilX::NSGUISystem::IListBoxImp::setRowCount(UInt32 count)
{
	return Void();
}

UInt32 NSDevilX::NSGUISystem::IListBoxImp::getRowCount() const
{
	return UInt32();
}

Void NSDevilX::NSGUISystem::IListBoxImp::setColumeCount(UInt32 count)
{
	return Void();
}

UInt32 NSDevilX::NSGUISystem::IListBoxImp::getColumeCount() const
{
	return UInt32();
}
