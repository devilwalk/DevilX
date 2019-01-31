#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IRenderTaskImp::IRenderTaskImp()
	:mInternal(nullptr)
{
}

NSDevilX::NSRenderSystem::IRenderTaskImp::~IRenderTaskImp()
{
}

Void NSDevilX::NSRenderSystem::IRenderTaskImp::addChild(IRenderTask * task)
{
	mInternal->addChild(static_cast<IRenderTaskImp*>(task)->getInternal());
}

Void NSDevilX::NSRenderSystem::IRenderTaskImp::setSchemeName(const String & name)
{
	return Void();
}
