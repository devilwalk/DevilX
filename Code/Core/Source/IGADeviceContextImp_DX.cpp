#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;
using namespace NSVersion11;

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::IGADeviceContextImp(ID3D11Device * device,Bool deferred)
{
	if(deferred)
	{
		device->CreateDeferredContext(0,&mInternal);
	}
	else
	{
		device->GetImmediateContext(&mInternal);
	}
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::~IGADeviceContextImp()
{
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::clear(IGADepthStencilView * view,UInt32 flags,Float depth,UInt8 stencil)
{
	mInternal->ClearDepthStencilView(static_cast<IGADepthStencilViewImp*>(view)->getInternal(),CUtility::mappingClearFlags(flags),depth,stencil);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::clear(IGARenderTargetView * view,const Float colourRGBA[4])
{
	mInternal->ClearRenderTargetView(static_cast<IGARenderTargetViewImp*>(view)->getInternal(),colourRGBA);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::clear(IGAUnorderedAccessView * view,const Float value[4])
{
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::clear(IGAUnorderedAccessView * view,const UInt32 value[4])
{
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setRenderTargets(UInt32 numRenderTarget,IGARenderTargetView * const * renderTargetViews,IGADepthStencilView * depthStencilView)
{
	for(UInt32 i=0;i<numRenderTarget;++i)
	{
		mPointerCache[i]=static_cast<IGARenderTargetViewImp*>(renderTargetViews[i])->getInternal();
	}
	mInternal->OMSetRenderTargets(numRenderTarget,reinterpret_cast<ID3D11RenderTargetView**>(&mPointerCache[0]),static_cast<IGADepthStencilViewImp*>(depthStencilView)->getInternal());
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setInputLayout(IGAInputLayout * layout)
{
	mInternal->IASetInputLayout(static_cast<IGAInputLayoutImp*>(layout)->getInternal());
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setVertexBuffer(UInt32 startSlot,UInt32 numBuffers,IGAVertexBuffer * const * buffers,const UInt32 * strides,const UInt32 * offsets)
{
	for(UInt32 i=0;i<numBuffers;++i)
		mPointerCache[i]=static_cast<IGABufferImp*>(buffers[i])->getInternal();
	mInternal->IASetVertexBuffers(startSlot,numBuffers,reinterpret_cast<ID3D11Buffer**>(&mPointerCache[0]),strides,offsets);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setIndexBuffer(IGAIndexBuffer * buffer,IGAEnum::EGIFormat format,UInt32 offset)
{
	mInternal->IASetIndexBuffer(static_cast<IGABufferImp*>(buffer)->getInternal(),CUtility::mapping(format),offset);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setProgram(IGAProgram * program,IGAProgramParameter * parameter)
{
	auto shaders=static_cast<IGAProgramImp*>(program)->getShaders();
	auto vertex_shader=static_cast<IGAVertexShaderImp*>(shaders[IGAEnum::EShaderType_Vertex]);
	if(vertex_shader)
	{
		mInternal->VSSetShader(vertex_shader->getInternal(),nullptr,0);
		if(static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Vertex])
		{
			auto& constant_buffers=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Vertex]->getConstantBuffers();
			if(!constant_buffers.empty())
				CopyMemory(&mPointerCache[0],&constant_buffers[0],constant_buffers.size()*sizeof(VoidPtr));
			mInternal->VSSetConstantBuffers(0,static_cast<UInt32>(constant_buffers.size()),reinterpret_cast<ID3D11Buffer*const*>(&mPointerCache[0]));
			auto& samplers=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Vertex]->getSamplers();
			if(!samplers.empty())
				CopyMemory(&mPointerCache[0],&samplers[0],samplers.size()*sizeof(VoidPtr));
			mInternal->VSSetSamplers(0,static_cast<UInt32>(samplers.size()),reinterpret_cast<ID3D11SamplerState*const*>(&mPointerCache[0]));
			auto& shader_resource=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Vertex]->getShaderResourceViews();
			if(!shader_resource.empty())
				CopyMemory(&mPointerCache[0],&shader_resource[0],shader_resource.size()*sizeof(VoidPtr));
			mInternal->VSSetShaderResources(0,static_cast<UInt32>(shader_resource.size()),reinterpret_cast<ID3D11ShaderResourceView*const*>(&mPointerCache[0]));
		}
	}
	auto pixel_shader=static_cast<IGAPixelShaderImp*>(shaders[IGAEnum::EShaderType_Pixel]);
	if(pixel_shader)
	{
		mInternal->PSSetShader(pixel_shader->getInternal(),nullptr,0);
		if(static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Pixel])
		{
			auto& constant_buffers=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Pixel]->getConstantBuffers();
			if(!constant_buffers.empty())
				CopyMemory(&mPointerCache[0],&constant_buffers[0],constant_buffers.size()*sizeof(VoidPtr));
			mInternal->PSSetConstantBuffers(0,static_cast<UInt32>(constant_buffers.size()),reinterpret_cast<ID3D11Buffer*const*>(&mPointerCache[0]));
			auto& samplers=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Pixel]->getSamplers();
			if(!samplers.empty())
				CopyMemory(&mPointerCache[0],&samplers[0],samplers.size()*sizeof(VoidPtr));
			mInternal->PSSetSamplers(0,static_cast<UInt32>(samplers.size()),reinterpret_cast<ID3D11SamplerState*const*>(&mPointerCache[0]));
			auto& shader_resource=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Pixel]->getShaderResourceViews();
			if(!shader_resource.empty())
				CopyMemory(&mPointerCache[0],&shader_resource[0],shader_resource.size()*sizeof(VoidPtr));
			mInternal->PSSetShaderResources(0,static_cast<UInt32>(shader_resource.size()),reinterpret_cast<ID3D11ShaderResourceView*const*>(&mPointerCache[0]));
		}
	}
	auto geometry_shader=static_cast<IGAGeometryShaderImp*>(shaders[IGAEnum::EShaderType_Geometry]);
	if(geometry_shader)
	{
		mInternal->GSSetShader(geometry_shader->getInternal(),nullptr,0);
		if(static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Geometry])
		{
			auto& constant_buffers=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Geometry]->getConstantBuffers();
			if(!constant_buffers.empty())
				CopyMemory(&mPointerCache[0],&constant_buffers[0],constant_buffers.size()*sizeof(VoidPtr));
			mInternal->GSSetConstantBuffers(0,static_cast<UInt32>(constant_buffers.size()),reinterpret_cast<ID3D11Buffer*const*>(&mPointerCache[0]));
			auto& samplers=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Geometry]->getSamplers();
			if(!samplers.empty())
				CopyMemory(&mPointerCache[0],&samplers[0],samplers.size()*sizeof(VoidPtr));
			mInternal->GSSetSamplers(0,static_cast<UInt32>(samplers.size()),reinterpret_cast<ID3D11SamplerState*const*>(&mPointerCache[0]));
			auto& shader_resource=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Geometry]->getShaderResourceViews();
			if(!shader_resource.empty())
				CopyMemory(&mPointerCache[0],&shader_resource[0],shader_resource.size()*sizeof(VoidPtr));
			mInternal->GSSetShaderResources(0,static_cast<UInt32>(shader_resource.size()),reinterpret_cast<ID3D11ShaderResourceView*const*>(&mPointerCache[0]));
		}
	}
	auto hull_shader=static_cast<IGAHullShaderImp*>(shaders[IGAEnum::EShaderType_Hull]);
	if(hull_shader)
	{
		mInternal->HSSetShader(hull_shader->getInternal(),nullptr,0);
		if(static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Hull])
		{
			auto& constant_buffers=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Hull]->getConstantBuffers();
			if(!constant_buffers.empty())
				CopyMemory(&mPointerCache[0],&constant_buffers[0],constant_buffers.size()*sizeof(VoidPtr));
			mInternal->HSSetConstantBuffers(0,static_cast<UInt32>(constant_buffers.size()),reinterpret_cast<ID3D11Buffer*const*>(&mPointerCache[0]));
			auto& samplers=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Hull]->getSamplers();
			if(!samplers.empty())
				CopyMemory(&mPointerCache[0],&samplers[0],samplers.size()*sizeof(VoidPtr));
			mInternal->HSSetSamplers(0,static_cast<UInt32>(samplers.size()),reinterpret_cast<ID3D11SamplerState*const*>(&mPointerCache[0]));
			auto& shader_resource=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Hull]->getShaderResourceViews();
			if(!shader_resource.empty())
				CopyMemory(&mPointerCache[0],&shader_resource[0],shader_resource.size()*sizeof(VoidPtr));
			mInternal->HSSetShaderResources(0,static_cast<UInt32>(shader_resource.size()),reinterpret_cast<ID3D11ShaderResourceView*const*>(&mPointerCache[0]));
		}
	}
	auto domain_shader=static_cast<IGADomainShaderImp*>(shaders[IGAEnum::EShaderType_Domain]);
	if(domain_shader)
	{
		mInternal->DSSetShader(domain_shader->getInternal(),nullptr,0);
		if(static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Domain])
		{
			auto& constant_buffers=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Domain]->getConstantBuffers();
			if(!constant_buffers.empty())
				CopyMemory(&mPointerCache[0],&constant_buffers[0],constant_buffers.size()*sizeof(VoidPtr));
			mInternal->DSSetConstantBuffers(0,static_cast<UInt32>(constant_buffers.size()),reinterpret_cast<ID3D11Buffer*const*>(&mPointerCache[0]));
			auto& samplers=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Domain]->getSamplers();
			if(!samplers.empty())
				CopyMemory(&mPointerCache[0],&samplers[0],samplers.size()*sizeof(VoidPtr));
			mInternal->DSSetSamplers(0,static_cast<UInt32>(samplers.size()),reinterpret_cast<ID3D11SamplerState*const*>(&mPointerCache[0]));
			auto& shader_resource=static_cast<IGAProgramParameterImp*>(parameter)->getShaderParameters()[IGAEnum::EShaderType_Domain]->getShaderResourceViews();
			if(!shader_resource.empty())
				CopyMemory(&mPointerCache[0],&shader_resource[0],shader_resource.size()*sizeof(VoidPtr));
			mInternal->DSSetShaderResources(0,static_cast<UInt32>(shader_resource.size()),reinterpret_cast<ID3D11ShaderResourceView*const*>(&mPointerCache[0]));
		}
	}
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setPrimitiveTopology(IGAEnum::EPrimitiveTopology primitiveTopology)
{
	mInternal->IASetPrimitiveTopology(CUtility::mapping(primitiveTopology));
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setRasterizerState(IGARasterizerState * state)
{
	mInternal->RSSetState(static_cast<IGARasterizerStateImp*>(state)->getInternal());
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setDepthStencilState(IGADepthStencilState * state,UInt32 stencilRef)
{
	mInternal->OMSetDepthStencilState(static_cast<IGADepthStencilStateImp*>(state)->getInternal(),stencilRef);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setBlendState(IGABlendState * state,const Float factor[4],UInt32 samplerMask)
{
	mInternal->OMSetBlendState(static_cast<IGABlendStateImp*>(state)->getInternal(),factor,samplerMask);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setScissorRects(UInt32 numRects,const CRect * rects)
{
	std::array<D3D11_RECT,8> d3d_rects;
	for(UInt32 i=0;i<numRects;++i)
	{
		d3d_rects[i].bottom=rects[i].mBottom;
		d3d_rects[i].top=rects[i].mTop;
		d3d_rects[i].left=rects[i].mLeft;
		d3d_rects[i].right=rects[i].mRight;
	}
	mInternal->RSSetScissorRects(numRects,&d3d_rects[0]);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setViewports(UInt32 numViewports,const IGAStruct::SViewport * viewports)
{
	std::array<D3D11_VIEWPORT,8> d3d_vps;
	for(UInt32 i=0;i<numViewports;++i)
	{
		d3d_vps[i].Height=viewports[i].Height;
		d3d_vps[i].MaxDepth=viewports[i].MaxDepth;
		d3d_vps[i].MinDepth=viewports[i].MinDepth;
		d3d_vps[i].TopLeftX=viewports[i].TopLeftX;
		d3d_vps[i].TopLeftY=viewports[i].TopLeftY;
		d3d_vps[i].Width=viewports[i].Width;
	}
	mInternal->RSSetViewports(numViewports,&d3d_vps[0]);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::draw(UInt32 vertexCountPerInstance,UInt32 startVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation)
{
	mInternal->DrawInstanced(vertexCountPerInstance,instanceCount,startVertexLocation,startInstanceLocation);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::drawIndexed(UInt32 indexCountPerInstance,UInt32 startIndexLocation,Int32 baseVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation)
{
	mInternal->DrawIndexedInstanced(indexCountPerInstance,instanceCount,startIndexLocation,baseVertexLocation,startInstanceLocation);
}

IGADeviceContext1* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::queryInterface_IGADeviceContext1() const
{
	return const_cast<IGADeviceContextImp*>(this);
}

IGADeviceContext* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::queryInterface_IGADeviceContext() const
{
	return const_cast<IGADeviceContextImp*>(this);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setVertexShader(IGAVertexShader* shader,IGAShaderParameter* parameter)
{
	mInternal->VSSetShader(static_cast<IGAVertexShaderImp*>(shader)->getInternal(),nullptr,0);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().empty())
		mInternal->VSSetConstantBuffers(0,static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().empty())
		mInternal->VSSetSamplers(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getSamplers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().empty())
		mInternal->VSSetShaderResources(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews()[0]);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setPixelShader(IGAPixelShader* shader,IGAShaderParameter* parameter)
{
	mInternal->PSSetShader(static_cast<IGAPixelShaderImp*>(shader)->getInternal(),nullptr,0);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().empty())
		mInternal->PSSetConstantBuffers(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().empty())
		mInternal->PSSetSamplers(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getSamplers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().empty())
		mInternal->PSSetShaderResources(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews()[0]);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setGeometryShader(IGAGeometryShader* shader,IGAShaderParameter* parameter)
{
	mInternal->GSSetShader(static_cast<IGAGeometryShaderImp*>(shader)->getInternal(),nullptr,0);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().empty())
		mInternal->GSSetConstantBuffers(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().empty())
		mInternal->GSSetSamplers(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getSamplers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().empty())
		mInternal->GSSetShaderResources(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews()[0]);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setHullShader(IGAHullShader* shader,IGAShaderParameter* parameter)
{
	mInternal->HSSetShader(static_cast<IGAHullShaderImp*>(shader)->getInternal(),nullptr,0);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().empty())
		mInternal->HSSetConstantBuffers(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().empty())
		mInternal->HSSetSamplers(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getSamplers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().empty())
		mInternal->HSSetShaderResources(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews()[0]);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::setDomainShader(IGADomainShader* shader,IGAShaderParameter* parameter)
{
	mInternal->DSSetShader(static_cast<IGADomainShaderImp*>(shader)->getInternal(),nullptr,0);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().empty())
		mInternal->DSSetConstantBuffers(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().empty())
		mInternal->DSSetSamplers(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getSamplers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().empty())
		mInternal->DSSetShaderResources(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews()[0]);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::dispatch(IGAComputeShader* shader,IGAShaderParameter* parameter,UInt32 threadGroupCountX,UInt32 threadGroupCountY,UInt32 threadGroupCountZ)
{
	mInternal->CSSetShader(static_cast<IGAComputeShaderImp*>(shader)->getInternal(),nullptr,0);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().empty())
		mInternal->CSSetConstantBuffers(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getConstantBuffers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().empty())
		mInternal->CSSetSamplers(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getSamplers().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getSamplers()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().empty())
		mInternal->CSSetShaderResources(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getShaderResourceViews()[0]);
	if(!static_cast<IGAShaderParameterImp*>(parameter)->getUnorderedAccessViews().empty())
		mInternal->CSSetUnorderedAccessViews(0, static_cast<UINT>(static_cast<IGAShaderParameterImp*>(parameter)->getUnorderedAccessViews().size()),&static_cast<IGAShaderParameterImp*>(parameter)->getUnorderedAccessViews()[0],nullptr);
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceContextImp::update(IGABuffer* buffer,ConstVoidPtr data,UInt32 updateOffsetInBytes,UInt32 updateSizeInBytes)
{
	D3D11_BUFFER_DESC desc;
	static_cast<IGABufferImp*>(buffer)->getInternal()->GetDesc(&desc);
	if(desc.Usage==D3D11_USAGE_DEFAULT)
	{
		D3D11_BOX dst_box;
		D3D11_BOX* dst_box_ptr=nullptr;
		if(updateOffsetInBytes||updateSizeInBytes)
		{
			dst_box.left=updateOffsetInBytes;
			dst_box.right=updateOffsetInBytes+updateSizeInBytes;
			dst_box.top=0;
			dst_box.bottom=1;
			dst_box.front=0;
			dst_box.back=1;
			dst_box_ptr=&dst_box;
		}
		mInternal->UpdateSubresource(static_cast<IGABufferImp*>(buffer)->getInternal(),0,dst_box_ptr,data,0,0);
	}
	else if(desc.Usage==D3D11_USAGE_DYNAMIC)
	{
		D3D11_MAPPED_SUBRESOURCE sub_resource;
		mInternal->Map(static_cast<IGABufferImp*>(buffer)->getInternal(),0,D3D11_MAP_WRITE_DISCARD,0,&sub_resource);
		updateSizeInBytes=updateSizeInBytes?updateSizeInBytes:desc.ByteWidth;
		CopyMemory(static_cast<UInt8*>(sub_resource.pData)+updateOffsetInBytes,data,updateSizeInBytes);
		mInternal->Unmap(static_cast<IGABufferImp*>(buffer)->getInternal(),0);
	}
	else
	{
		assert(0);
	}
}
