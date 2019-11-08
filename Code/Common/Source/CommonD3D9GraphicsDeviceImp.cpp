#include "Precompiler.h"
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
using namespace NSDevilX;

NSDevilX::CD3D9GraphicsDeviceImp::CD3D9GraphicsDeviceImp(IDirect3DDevice9* internalDevice)
	:mInternal(internalDevice)
{
}

NSDevilX::CD3D9GraphicsDeviceImp::~CD3D9GraphicsDeviceImp()
{
}
#endif