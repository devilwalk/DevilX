#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CRenderOperation::CRenderOperation()
	:mVertexArrayObject(0)
	,mPass(nullptr)
	,mPrimitiveTopology(GL_TRIANGLES)
	,mIndexCount(0)
	,mIndexBufferOffset(0)
	,mVertexCount(0)
	,mVertexBufferOffset(0)
{}

NSDevilX::NSRenderSystem::NSGL4::CRenderOperation::~CRenderOperation()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderOperation::process()
{
	glBindVertexArray(mVertexArrayObject);
	CUtility::checkGLError();
	glUseProgram(mPass->getProgram()->getInternal());
	CUtility::checkGLError();
	for(UInt32 i=0;i<mConstantBuffers.size();++i)
	{
		mConstantBuffers[i]->submit();
		glBindBufferBase(GL_UNIFORM_BUFFER,i,mConstantBuffers[i]->getInternal());
		CUtility::checkGLError();
		glUniformBlockBinding(CSystemImp::getSingleton().getClearViewportProgram()->getInternal(),CSystemImp::getSingleton().getClearViewportProgram()->getSlot(mConstantBuffers[i]->getDescription()->getName()),i);
		CUtility::checkGLError();
	}
	if(mIndexCount)
		glDrawElements(mPrimitiveTopology,mIndexCount,GL_UNSIGNED_INT,reinterpret_cast<VoidPtr>(mIndexBufferOffset));
	else
		glDrawArrays(mPrimitiveTopology,mVertexBufferOffset,mVertexCount);
	CUtility::checkGLError();
	glBindBuffer(GL_UNIFORM_BUFFER,0);
	CUtility::checkGLError();
	glUseProgram(0);
	CUtility::checkGLError();
	glBindVertexArray(0);
	CUtility::checkGLError();
}
