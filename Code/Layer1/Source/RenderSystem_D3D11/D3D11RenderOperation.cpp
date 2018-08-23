#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CRenderOperation::CRenderOperation(ID3D11DeviceContext1 * context)
	:mContext(context)
	,mPass(nullptr)
	,mPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	,mIndexCount(0)
	,mIndexBufferOffset(0)
	,mVertexCount(0)
	,mVertexBufferOffset(0)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderOperation::~CRenderOperation()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderOperation::process()
{
	const UINT vertex_offsets[16]={0};
	if(mPass->getVertexShader()->getInputElementDescs().empty())
		mContext->IASetVertexBuffers(0,0,nullptr,nullptr,nullptr);
	else
		mContext->IASetVertexBuffers(0,static_cast<UINT>(mPass->getVertexShader()->getInputElementDescs().size()),&mVertexBuffers[0],&mVertexStrides[0],vertex_offsets);
	mContext->IASetIndexBuffer(mIndexBuffer,DXGI_FORMAT_R32_UINT,0);
	mContext->IASetPrimitiveTopology(mPrimitiveTopology);
	mContext->IASetInputLayout(mPass->getVertexShader()->getInputLayout());
	mContext->VSSetShader(mPass->getVertexShader()->getInternal(),nullptr,0);
	for(auto constant_buffer:mConstantBuffers)
	{
		auto slot=mPass->getVertexShader()->getSlot(constant_buffer->getDescription()->getNameInShader());
		if(static_cast<UInt32>(-1)!=slot)
		{
			auto const temp=constant_buffer->getInternal();
			mContext->VSSetConstantBuffers(slot,1,&temp);
		}
	}
	TVector(ID3D11ShaderResourceView*) srvs;
	if(!mPass->getVSTextures().empty())
	{
		for(auto texture:mPass->getVSTextures())
		{
			srvs.push_back(texture->getInternal());
		}
		mContext->VSSetShaderResources(0,static_cast<UInt32>(srvs.size()),&srvs[0]);
	}
	if(!mPass->getVSSamplerStates().empty())
		mContext->VSSetSamplers(0,static_cast<UInt32>(mPass->getVSSamplerStates().size()),&mPass->getVSSamplerStates()[0]);
	mContext->PSSetShader(mPass->getPixelShader()->getInternal(),nullptr,0);
	for(auto constant_buffer:mConstantBuffers)
	{
		auto slot=mPass->getPixelShader()->getSlot(constant_buffer->getDescription()->getNameInShader());
		if(static_cast<UInt32>(-1)!=slot)
		{
			auto const temp=constant_buffer->getInternal();
			mContext->PSSetConstantBuffers(slot,1,&temp);
		}
	}
	if(!mPass->getPSTextures().empty())
	{
		for(auto texture:mPass->getPSTextures())
		{
			srvs.push_back(texture->getInternal());
		}
		mContext->PSSetShaderResources(0,static_cast<UInt32>(srvs.size()),&srvs[0]);
	}
	if(!mPass->getPSSamplerStates().empty())
		mContext->PSSetSamplers(0,static_cast<UInt32>(mPass->getPSSamplerStates().size()),&mPass->getPSSamplerStates()[0]);
	mContext->RSSetState(mPass->getRasterizerState());
	if(!mScissorRects.empty())
		mContext->RSSetScissorRects(static_cast<UInt32>(mScissorRects.size()),&mScissorRects[0]);
	mContext->OMSetBlendState(mPass->getBlendState(),reinterpret_cast<const Float*>(&CFloat4::sOne),0xffffffff);
	mContext->OMSetDepthStencilState(mPass->getDepthStencilState(),0);
	if(mIndexCount)
		mContext->DrawIndexed(mIndexCount,mIndexBufferOffset,mVertexBufferOffset);
	else
		mContext->Draw(mVertexCount,mVertexBufferOffset);
}
