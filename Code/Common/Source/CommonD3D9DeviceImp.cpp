#include "Precompiler.h"
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
using namespace NSDevilX;

NSDevilX::NSGraphicsAPI::CD3D9DeviceImp::CD3D9DeviceImp(IDirect3DDevice9* internalDevice)
	:mInternal(internalDevice)
{
}

NSDevilX::NSGraphicsAPI::CD3D9DeviceImp::~CD3D9DeviceImp()
{
}
#endif