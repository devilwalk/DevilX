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

NSDevilX::NSGraphicsAPI::CGLGlobal::EProfile NSDevilX::NSGraphicsAPI::CGLGlobal::msProfile=EProfile_Count;
NSDevilX::NSGraphicsAPI::CGLGlobal::EESProfile NSDevilX::NSGraphicsAPI::CGLGlobal::msESProfile=EESProfile_Count;