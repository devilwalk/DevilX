#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::CEntityPass(CEntityTechnique * technique)
	:mTechnique(technique)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CEntityPass::~CEntityPass()
{}