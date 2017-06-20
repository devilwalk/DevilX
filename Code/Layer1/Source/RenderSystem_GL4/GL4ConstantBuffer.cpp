#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CConstantBuffer::CConstantBuffer(CConstantBufferDescription * description)
	:mDescription(description)
	,mInternal(0)
{
	glCreateBuffers(1,&mInternal);
	CUtility::checkGLError();
	glNamedBufferStorage(getInternal(),getDescription()->getSizeInBytes(),nullptr,GL_MAP_WRITE_BIT);
	CUtility::checkGLError();
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
		auto dst=glMapNamedBuffer(getInternal(),GL_WRITE_ONLY);
		CUtility::checkGLError();
		memcpy(dst,&mCache[0],mCache.size());
		glUnmapNamedBuffer(getInternal());
		CUtility::checkGLError();
		is_update_ref=False;
	}
	mNeedUpdate.endWrite();
}
