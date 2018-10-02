#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CBufferImp::CBufferImp()
{
}

NSDevilX::NSRenderSystem::NSD3D11::CBufferImp::~CBufferImp()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CBufferImp::initialize(IEnum::EBufferType type,UInt32 sizeInBytes,UInt32 flag,ConstVoidPtr data)
{
	ID3D11Buffer * buff=nullptr;
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(desc));
	switch(type)
	{
	case IEnum::EBufferType_VertexBuffer:desc.BindFlags|=D3D11_BIND_VERTEX_BUFFER;break;
	case IEnum::EBufferType_IndexBuffer:desc.BindFlags|=D3D11_BIND_INDEX_BUFFER;break;
	case IEnum::EBufferType_ConstantBuffer:desc.BindFlags|=D3D11_BIND_CONSTANT_BUFFER;break;
	case IEnum::EBufferType_ShaderResource:desc.BindFlags|=D3D11_BIND_SHADER_RESOURCE;break;
	}
	if(IEnum::EBufferFlag_StreamOutput&flag)
	{
		desc.BindFlags|=D3D11_BIND_STREAM_OUTPUT;
	}
	if(IEnum::EBufferFlag_CPUWrite&flag)
	{
		desc.CPUAccessFlags|=D3D11_CPU_ACCESS_WRITE;
		desc.Usage=D3D11_USAGE_DYNAMIC;
	}
	else
	{
		desc.Usage=D3D11_USAGE_DEFAULT;
	}
	desc.ByteWidth=sizeInBytes;
	D3D11_SUBRESOURCE_DATA sub_data;
	sub_data.pSysMem=data;
	sub_data.SysMemPitch=sizeInBytes;
	sub_data.SysMemSlicePitch=sizeInBytes;
	CSystemImp::getSingleton().getDevice()->CreateBuffer(&desc,data?&sub_data:nullptr,&buff);
	setInternal(buff);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CBufferImp::updateData(ConstVoidPtr data,UInt32 offsetInBytes,UInt32 sizeInBytes)
{
	D3D11_BOX dst_box={0};
	dst_box.left=offsetInBytes;
	dst_box.right=offsetInBytes+sizeInBytes;
	dst_box.bottom=1;
	dst_box.back=1;
	CSystemImp::getSingleton().getImmediateContext()->UpdateSubresource(getInternal(),0,&dst_box,data,dst_box.right-dst_box.left+1,dst_box.right-dst_box.left+1);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CBufferImp::bind(UInt32 offsetInBytes,IEnum::EAutoPropgramParameterDataSource source)
{
	return Void();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CBufferImp::unbind(UInt32 offsetInBytes)
{
	return Void();
}
