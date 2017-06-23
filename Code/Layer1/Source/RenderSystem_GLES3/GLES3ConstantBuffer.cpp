#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CConstantBuffer::CConstantBuffer(CConstantBufferDescription * description)
	:mDescription(description)
	,mInternal(0)
{
	glGenBuffers(1,&mInternal);
	CUtility::checkGLError();
	glBindBuffer(GL_UNIFORM_BUFFER,getInternal());
	CUtility::checkGLError();
	glBufferData(GL_UNIFORM_BUFFER,getDescription()->getSizeInBytes(),nullptr,GL_DYNAMIC_DRAW);
	CUtility::checkGLError();
	glBindBuffer(GL_UNIFORM_BUFFER,0);
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
		glBindBuffer(GL_UNIFORM_BUFFER,getInternal());
		CUtility::checkGLError();
		auto dst=glMapBufferRange(GL_UNIFORM_BUFFER,0,mCache.size(),GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT);
		CUtility::checkGLError();
		memcpy(dst,&mCache[0],mCache.size());
		glUnmapBuffer(GL_UNIFORM_BUFFER);
		CUtility::checkGLError();
		glBindBuffer(GL_UNIFORM_BUFFER,0);
		CUtility::checkGLError();
		is_update_ref=False;
	}
	mNeedUpdate.endWrite();
}
