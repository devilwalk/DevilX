#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CConstantBuffer::CConstantBuffer(CConstantBufferDescription * description)
	:mDescription(description)
	,mInternal(0)
{
	glCreateBuffers(1,&mInternal);
	CUtility::checkGLError();
	glNamedBufferStorage(getInternal(),getDescription()->getSizeInBytes(),nullptr,GL_MAP_WRITE_BIT);
	CUtility::checkGLError();
	mCache.resize(getDescription()->getSizeInBytes());
}

NSDevilX::NSRenderSystem::NSGLES3::CConstantBuffer::~CConstantBuffer()
{
	glDeleteBuffers(1,&mInternal);
}

Void NSDevilX::NSRenderSystem::NSGLES3::CConstantBuffer::submit()
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
