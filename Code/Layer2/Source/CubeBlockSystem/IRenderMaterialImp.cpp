#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockSystem;

NSDevilX::NSCubeBlockSystem::IRenderMaterialImp::IRenderMaterialImp(const String & name)
	:mName(name)
{}

NSDevilX::NSCubeBlockSystem::IRenderMaterialImp::~IRenderMaterialImp()
{}

const String & NSDevilX::NSCubeBlockSystem::IRenderMaterialImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

Void NSDevilX::NSCubeBlockSystem::IRenderMaterialImp::setColour(const CColour & colour)
{
	if(colour!=getColour())
	{
		notify(EMessage_BeginColourChange);
		mColour=colour;
		notify(EMessage_EndColourChange);
	}
}

const CColour & NSDevilX::NSCubeBlockSystem::IRenderMaterialImp::getColour() const
{
	// TODO: insert return statement here
	return mColour;
}
