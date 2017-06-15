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
	glUseProgram(mPass->getProgram()->getInternal());
	for(UInt32 i=0;i<mConstantBuffers.size();++i)
	{
		mConstantBuffers[i]->submit();
		glBindBufferBase(GL_UNIFORM_BUFFER,i,mConstantBuffers[i]->getInternal());
		glUniformBlockBinding(CSystemImp::getSingleton().getClearViewportProgram()->getInternal(),CSystemImp::getSingleton().getClearViewportProgram()->getSlot(mConstantBuffers[i]->getDescription()->getName()),i);
	}
	if(mIndexCount)
		glDrawElements(mPrimitiveTopology,mIndexCount,GL_UNSIGNED_INT,&mIndexBufferOffset);
	else
		glDrawArrays(mPrimitiveTopology,mVertexBufferOffset,mVertexCount);
	glBindBuffer(GL_UNIFORM_BUFFER,0);
	glUseProgram(0);
	glBindVertexArray(0);
}
