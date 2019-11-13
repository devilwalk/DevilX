#include "Precompiler.h"
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
using namespace NSDevilX;

NSDevilX::NSGraphicsAPI::CD3D11DeviceImp::CD3D11DeviceImp(ID3D11Device* internalDevice)
	:mInternal(internalDevice)
{
}

NSDevilX::NSGraphicsAPI::CD3D11DeviceImp::~CD3D11DeviceImp()
{
}

Bool NSDevilX::NSGraphicsAPI::CD3D11DeviceImp::createVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,OUT IBuffer* Buffer)
{
	D3D11_BUFFER_DESC desc={0};
	desc.BindFlags=D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth=Length;
	desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE|((Usage&D3DUSAGE_WRITEONLY)?0:D3D11_CPU_ACCESS_READ);
	desc.MiscFlags=0;
	desc.StructureByteStride=0;
	desc.Usage=mappingD3D11(Pool,Usage);
	mInternal->CreateBuffer(&desc,nullptr,&static_cast<CD3D11BufferImp*>(Buffer)->mInternal);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CD3D11DeviceImp::createIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,OUT IBuffer* Buffer)
{
	D3D11_BUFFER_DESC desc={0};
	desc.BindFlags=D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth=Length;
	desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE|((Usage&D3DUSAGE_WRITEONLY)?0:D3D11_CPU_ACCESS_READ);
	desc.MiscFlags=0;
	desc.StructureByteStride=0;
	desc.Usage=mappingD3D11(Pool,Usage);
	mInternal->CreateBuffer(&desc,nullptr,&static_cast<CD3D11BufferImp*>(Buffer)->mInternal);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CD3D11DeviceImp::createBuffer(const D3D10_BUFFER_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IBuffer* buffer)
{
	D3D11_BUFFER_DESC real_desc=mapping(desc);
	mInternal->CreateBuffer(&real_desc,reinterpret_cast<const D3D11_SUBRESOURCE_DATA*>(initializeData),&static_cast<CD3D11BufferImp*>(buffer)->mInternal);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CD3D11DeviceImp::createBuffer(const D3D11_BUFFER_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IBuffer* buffer)
{
	mInternal->CreateBuffer(&desc,initializeData,&static_cast<CD3D11BufferImp*>(buffer)->mInternal);
	return True;
}

#endif