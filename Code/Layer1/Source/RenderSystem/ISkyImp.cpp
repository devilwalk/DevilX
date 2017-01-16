#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::ISkyImp::ISkyImp(IRenderableImp * renderable)
	:mRenderable(renderable)
	,mOrder(0)
{}

NSDevilX::NSRenderSystem::ISkyImp::~ISkyImp()
{}

Void NSDevilX::NSRenderSystem::ISkyImp::setOrder(UInt32 order)
{
	mOrder=order;
}

UInt32 NSDevilX::NSRenderSystem::ISkyImp::getOrder() const
{
	return mOrder;
}
