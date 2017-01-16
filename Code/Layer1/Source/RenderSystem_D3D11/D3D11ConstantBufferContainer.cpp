#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CConstantBufferContainer::CConstantBufferContainer(const String & constBufferNameInShader)
	:mConstantBufferNameInShader(constBufferNameInShader)
	,mConstantBuffer(nullptr)
	,mNeedUpdate(True)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CConstantBufferContainer::~CConstantBufferContainer()
{
	DEVILX_DELETE(mConstantBuffer);
}

CConstantBuffer * NSDevilX::NSRenderSystem::NSD3D11::CConstantBufferContainer::getConstantBufferMT()
{
	if(!mNeedUpdate)
		return mConstantBuffer;
	auto & is_update_ref=mNeedUpdate.beginWrite();
	if(is_update_ref)
	{
		if(nullptr==mConstantBuffer)
		{
			auto desc=CSystemImp::getSingleton().getConstantBufferDescriptionManager()->getDescription(mConstantBufferNameInShader);
			if(nullptr!=desc)
				mConstantBuffer=DEVILX_NEW CConstantBuffer(desc);
		}
		if(nullptr!=mConstantBuffer)
		{
			_updateConstantBuffer(mConstantBuffer->getCache());
			mConstantBuffer->needUpdate();
			is_update_ref=False;
		}
	}
	mNeedUpdate.endWrite();
	return mConstantBuffer;
}