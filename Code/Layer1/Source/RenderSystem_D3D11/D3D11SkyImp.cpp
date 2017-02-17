#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CSkyImp::CSkyImp(ISkyImp * interfaceImp)
	:TInterfaceObject<ISkyImp>(interfaceImp)
{}

NSDevilX::NSRenderSystem::NSD3D11::CSkyImp::~CSkyImp()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CSkyImp::onMessage(ISkyImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}
