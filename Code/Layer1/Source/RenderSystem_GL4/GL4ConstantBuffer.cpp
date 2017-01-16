#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CConstantBuffer::CConstantBuffer(CConstantBufferDescription * description)
	:mDescription(description)
	,mInternal(0)
{
	glGenBuffers(1,&mInternal);
	glNamedBufferData(getInternal(),getDescription()->getSizeInBytes(),nullptr,GL_DYNAMIC_DRAW);
	mCache.resize(getDescription()->getSizeInBytes());
}

NSDevilX::NSRenderSystem::NSGL4::CConstantBuffer::~CConstantBuffer()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CConstantBuffer::submit()
{
	if(!mNeedUpdate)
		return;
	auto & is_update_ref=mNeedUpdate.beginWrite();
	if(is_update_ref)
	{
		glNamedBufferSubData(getInternal(),0,mCache.size(),&mCache[0]);
		is_update_ref=False;
	}
	mNeedUpdate.endWrite();
}
