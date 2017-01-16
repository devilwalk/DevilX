#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IColourUnitStateImp::IColourUnitStateImp(IEnum::EColourUnitStateType type,IMaterialImp * material)
	:mType(type)
	,mMaterial(material)
	,mEnable(True)
	,mValue(CColour::sWhite)
{}

NSDevilX::NSRenderSystem::IColourUnitStateImp::~IColourUnitStateImp()
{}

IEnum::EColourUnitStateType NSDevilX::NSRenderSystem::IColourUnitStateImp::getType() const
{
	return mType;
}

Void NSDevilX::NSRenderSystem::IColourUnitStateImp::setEnable(Bool enable)
{
	if(enable!=getEnable())
	{
		notify(EMessage_BeginEnableChange);
		mEnable=enable;
		notify(EMessage_EndEnableChange);
	}
}

Bool NSDevilX::NSRenderSystem::IColourUnitStateImp::getEnable() const
{
	return mEnable;
}

Void NSDevilX::NSRenderSystem::IColourUnitStateImp::setValue(const CColour & colour)
{
	if(colour!=getValue())
	{
		notify(EMessage_BeginValueChange);
		mValue=colour;
		notify(EMessage_EndValueChange);
	}
}

const CColour & NSDevilX::NSRenderSystem::IColourUnitStateImp::getValue() const
{
	// TODO: insert return statement here
	return mValue;
}
