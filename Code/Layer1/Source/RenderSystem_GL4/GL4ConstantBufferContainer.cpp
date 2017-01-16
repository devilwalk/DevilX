#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CConstantBufferContainer::CConstantBufferContainer(const String & constBufferNameInShader)
	:mConstantBufferNameInShader(constBufferNameInShader)
	,mConstantBuffer(nullptr)
	,mNeedUpdate(True)
{
}

NSDevilX::NSRenderSystem::NSGL4::CConstantBufferContainer::~CConstantBufferContainer()
{
	DEVILX_DELETE(mConstantBuffer);
}

CConstantBuffer * NSDevilX::NSRenderSystem::NSGL4::CConstantBufferContainer::getConstantBufferMT()
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