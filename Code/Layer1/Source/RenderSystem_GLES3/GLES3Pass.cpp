#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CPass::CPass()
	:mTechnique(nullptr)
	,mForwardType(CEnum::EForwardPassType_Count)
	,mProgram(nullptr)
{
}

NSDevilX::NSRenderSystem::NSGLES3::CPass::~CPass()
{}