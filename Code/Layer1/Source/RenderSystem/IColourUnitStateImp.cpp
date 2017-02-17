#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IColourUnitStateImp::IColourUnitStateImp(CColour::EType colourType)
	:mEnable(True)
	,mValue(nullptr)
{
	switch(colourType)
	{
	case CColour::EType_Alpha:
		mValue=DEVILX_NEW CFloatAlpha(1.0f);
		break;
	case CColour::EType_RGB:
		mValue=DEVILX_NEW CFloatRGB(CFloatRGB::sWhite);
		break;
	case CColour::EType_RGBA:
		mValue=DEVILX_NEW CFloatRGBA(CFloatRGBA::sWhite);
		break;
	}
}

NSDevilX::NSRenderSystem::IColourUnitStateImp::~IColourUnitStateImp()
{
	DEVILX_DELETE(mValue);
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
		*mValue=colour;
		notify(EMessage_EndValueChange);
	}
}

const CColour & NSDevilX::NSRenderSystem::IColourUnitStateImp::getValue() const
{
	// TODO: insert return statement here
	return *mValue;
}
