#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CRenderOperation::CRenderOperation()
	:mVertexArrayObject(0)
	,mPass(nullptr)
	,mPrimitiveTopology(GL_TRIANGLES)
	,mIndexCount(0)
	,mIndexBufferOffset(0)
	,mVertexCount(0)
	,mVertexBufferOffset(0)
{}

NSDevilX::NSRenderSystem::NSGLES3::CRenderOperation::~CRenderOperation()
{}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderOperation::process()
{
	if(mScissorRect)
	{
		glEnable(GL_SCISSOR_TEST);
		CUtility::checkGLError();
		glScissor(mScissorRect->mLeft,mScissorRect->mTop,mScissorRect->mWidth,mScissorRect->mHeight);
		CUtility::checkGLError();
	}
	glUseProgram(mPass->getProgram()->getInternal());
	CUtility::checkGLError();
	for(UInt32 i=0;i<mConstantBuffers.size();++i)
	{
		mConstantBuffers[i]->submit();
		glBindBufferBase(GL_UNIFORM_BUFFER,i,mConstantBuffers[i]->getInternal());
		CUtility::checkGLError();
		glUniformBlockBinding(mPass->getProgram()->getInternal(),mPass->getProgram()->getSlot(mConstantBuffers[i]->getDescription()->getName()),i);
		CUtility::checkGLError();
	}
	for(UInt32 i=0;i<mPass->getPSTextures().size();++i)
	{
		glActiveTexture(GL_TEXTURE0+i);
		CUtility::checkGLError();
		glBindTexture(GL_TEXTURE_2D,mPass->getPSTextures()[i]->getInternal());
		CUtility::checkGLError();
	}
	CUtility::checkGLError();
	for(UInt32 i=0;i<mPass->getPSTextures().size();++i)
	{
		glBindSampler(i,mPass->getPSSamplerStates()[0]->getInternal());
		CUtility::checkGLError();
	}
	for(auto value:mPass->getEnabledState())
	{
		glEnable(value);
		CUtility::checkGLError();
	}
	for(auto value:mPass->getDisableState())
	{
		glDisable(value);
		CUtility::checkGLError();
	}
	for(auto const & function_pair:mPass->getStateFunctions())
	{
		auto function=function_pair.first;
		auto const & params=function_pair.second[0];
		switch(params.size())
		{
		case 0:typedef Void *GL_APIENTRY f0();static_cast<f0*>(function)();break;
		case 1:typedef Void *GL_APIENTRY f1(GLint);static_cast<f1*>(function)(params[0]);break;
		case 2:typedef Void *GL_APIENTRY f2(GLint,GLint);static_cast<f2*>(function)(params[0],params[1]);break;
		case 3:typedef Void *GL_APIENTRY f3(GLint,GLint,GLint);static_cast<f3*>(function)(params[0],params[1],params[2]);break;
		case 4:typedef Void *GL_APIENTRY f4(GLint,GLint,GLint,GLint);static_cast<f4*>(function)(params[0],params[1],params[2],params[3]);break;
		case 5:typedef Void *GL_APIENTRY f5(GLint,GLint,GLint,GLint,GLint);static_cast<f5*>(function)(params[0],params[1],params[2],params[3],params[4]);break;
		default:assert(0);
		}
		CUtility::checkGLError();
	}
	glBindVertexArray(mVertexArrayObject);
	CUtility::checkGLError();
	if(mIndexCount)
		glDrawElements(mPrimitiveTopology,mIndexCount,GL_UNSIGNED_INT,reinterpret_cast<VoidPtr>(mIndexBufferOffset));
	else
		glDrawArrays(mPrimitiveTopology,mVertexBufferOffset,mVertexCount);
	CUtility::checkGLError();
	glBindVertexArray(0);
	CUtility::checkGLError();
	for(auto const & function_pair:mPass->getStateFunctions())
	{
		auto function=function_pair.first;
		auto const & params=function_pair.second[1];
		switch(params.size())
		{
		case 0:typedef Void *GL_APIENTRY f0();static_cast<f0*>(function)();break;
		case 1:typedef Void *GL_APIENTRY f1(GLint);static_cast<f1*>(function)(params[0]);break;
		case 2:typedef Void *GL_APIENTRY f2(GLint,GLint);static_cast<f2*>(function)(params[0],params[1]);break;
		case 3:typedef Void *GL_APIENTRY f3(GLint,GLint,GLint);static_cast<f3*>(function)(params[0],params[1],params[2]);break;
		case 4:typedef Void *GL_APIENTRY f4(GLint,GLint,GLint,GLint);static_cast<f4*>(function)(params[0],params[1],params[2],params[3]);break;
		case 5:typedef Void *GL_APIENTRY f5(GLint,GLint,GLint,GLint,GLint);static_cast<f5*>(function)(params[0],params[1],params[2],params[3],params[4]);break;
		default:assert(0);
		}
		CUtility::checkGLError();
	}
	for(auto value:mPass->getDisableState())
	{
		glEnable(value);
		CUtility::checkGLError();
	}
	for(auto value:mPass->getEnabledState())
	{
		glDisable(value);
		CUtility::checkGLError();
	}
	for(UInt32 i=0;i<mPass->getPSTextures().size();++i)
	{
		glBindSampler(i,0);
		CUtility::checkGLError();
	}
	for(UInt32 i=0;i<mPass->getPSTextures().size();++i)
	{
		glActiveTexture(GL_TEXTURE0+i);
		CUtility::checkGLError();
		glBindTexture(GL_TEXTURE_2D,0);
		CUtility::checkGLError();
	}
	glActiveTexture(GL_TEXTURE0);
	CUtility::checkGLError();
	glBindBuffer(GL_UNIFORM_BUFFER,0);
	CUtility::checkGLError();
	glUseProgram(0);
	CUtility::checkGLError();
	if(mScissorRect)
	{
		glDisable(GL_SCISSOR_TEST);
		CUtility::checkGLError();
	}
}
