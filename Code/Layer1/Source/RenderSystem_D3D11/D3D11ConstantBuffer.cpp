#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CConstantBuffer::CConstantBuffer(CConstantBufferDescription * description)
	:mDescription(description)
{
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.ByteWidth=getDescription()->getDesc().Size;
	buffer_desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	buffer_desc.MiscFlags=0;
	buffer_desc.StructureByteStride=0;
	buffer_desc.Usage=D3D11_USAGE_DYNAMIC;
	decltype(getInternal()) temp_internal=nullptr;
	CSystemImp::getSingleton().getDevice()->CreateBuffer(&buffer_desc,nullptr,&temp_internal);
	setInternal(temp_internal);
	mCache.resize(buffer_desc.ByteWidth);
}

NSDevilX::NSRenderSystem::NSD3D11::CConstantBuffer::~CConstantBuffer()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CConstantBuffer::submit()
{
	if(!mNeedUpdate)
		return;
	auto & is_update_ref=mNeedUpdate.beginWrite();
	if(is_update_ref)
	{
		auto context=CSystemImp::getSingleton().getImmediateContext();
		D3D11_MAPPED_SUBRESOURCE mapped_subresource;
		context->Map(getInternal(),0,D3D11_MAP_WRITE_DISCARD,0,&mapped_subresource);
		CopyMemory(mapped_subresource.pData,getCache(),mCache.size());
		context->Unmap(getInternal(),0);
		is_update_ref=False;
	}
	mNeedUpdate.endWrite();
}
