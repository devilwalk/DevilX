#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGraphicsAPI;

NSDevilX::NSGraphicsAPI::CGLObject::CGLObject()
	:mInternal(0)
{
}

NSDevilX::NSGraphicsAPI::CGLObject::~CGLObject()
{
}

NSDevilX::NSGraphicsAPI::CGLGlobal::EProfileCore NSDevilX::NSGraphicsAPI::CGLGlobal::msProfileCore=EProfileCore_Count;
NSDevilX::NSGraphicsAPI::CGLGlobal::EProfileESCore NSDevilX::NSGraphicsAPI::CGLGlobal::msProfileESCore=EProfileESCore_Count;