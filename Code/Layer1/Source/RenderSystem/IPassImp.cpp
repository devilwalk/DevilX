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
