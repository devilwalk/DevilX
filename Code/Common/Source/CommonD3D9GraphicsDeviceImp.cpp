#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CD3D9GraphicsDeviceImp::CD3D9GraphicsDeviceImp(IDirect3DDevice9* internalDevice)
	:mInternal(internalDevice)
{
}

NSDevilX::CD3D9GraphicsDeviceImp::~CD3D9GraphicsDeviceImp()
{
}

IGraphicsVertexBuffer* NSDevilX::CD3D9GraphicsDeviceImp::CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool)
{
	return nullptr;
}

IGraphicsIndexBuffer* NSDevilX::CD3D9GraphicsDeviceImp::CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool)
{
	return nullptr;
}

IGraphicsBuffer* NSDevilX::CD3D9GraphicsDeviceImp::createBuffer(const D3D10_BUFFER_DESC* desc)
{
	return nullptr;
}

IGraphicsBuffer* NSDevilX::CD3D9GraphicsDeviceImp::createBuffer(const D3D11_BUFFER_DESC* desc)
{
	return nullptr;
}
