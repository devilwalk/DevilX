#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CPass::CPass()
	:mTechnique(nullptr)
	,mForwardType(CEnum::EForwardPassType_Count)
	,mProgram(nullptr)
{
}

NSDevilX::NSRenderSystem::NSGL4::CPass::~CPass()
{}