#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IPassImp::IPassImp(ITechniqueImp * technique)
	:mTechnique(technique)
{
}

NSDevilX::NSRenderSystem::IPassImp::~IPassImp()
{
}

ITechnique * NSDevilX::NSRenderSystem::IPassImp::getTechnique() const
{
	return mTechnique;
}

Void NSDevilX::NSRenderSystem::IPassImp::setProgram(IProgram * program)
{
	return Void();
}

IProgram * NSDevilX::NSRenderSystem::IPassImp::getProgram() const
{
	return nullptr;
}

Void NSDevilX::NSRenderSystem::IPassImp::setProgramResource(UInt32 resourceLocation,IBuffer * buffer)
{
	return Void();
}

Void NSDevilX::NSRenderSystem::IPassImp::setProgramResource(UInt32 resourceLocation,ITexture * texture)
{
	return Void();
}

Void NSDevilX::NSRenderSystem::IPassImp::setProgramResource(UInt32 resourceLocation,ISamplerState * state)
{
	return Void();
}
