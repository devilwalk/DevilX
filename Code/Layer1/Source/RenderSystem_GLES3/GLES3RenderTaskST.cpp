#include "Precompiler.h"
#if DEVILX_RENDERSYSTEM_GLES3_MODE==DEVILX_RENDERSYSTEM_GLES3_ST
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CRenderTask::CRenderTask(CViewport * viewport)
	:mViewport(viewport)
{
}

NSDevilX::NSRenderSystem::NSGLES3::CRenderTask::~CRenderTask()
{
	for(auto task:mTasks)
		DEVILX_DELETE(task);
}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderTask::process()
{
	for(auto task:mTasks)
		task->process();
}

NSDevilX::NSRenderSystem::NSGLES3::CClearViewportTask::CClearViewportTask(CViewport * viewport)
	:CRenderTask(viewport)
	,CConstantBufferContainer("cbClearViewport")
	,mClearDepth(1.0f)
	,mClearStencil(0)
{
}

NSDevilX::NSRenderSystem::NSGLES3::CClearViewportTask::~CClearViewportTask()
{}

Void NSDevilX::NSRenderSystem::NSGLES3::CClearViewportTask::process()
{
	if(mViewport->isFullViewport())
	{
		for(UInt32 i=0;i<8;++i)
		{
			if(mClearColour[i]>=CFloat4::sZero)
				mViewport->getRenderTarget()->clear(i,mClearColour[i]);
		}
		mViewport->getRenderTarget()->clear(mClearDepth,mClearStencil);
	}
	else
	{
		mViewport->setup();
		for(GLuint i=0;i<8;++i)
		{
			Boolean write_colour=mClearColour[i]>=CFloat4::sZero;
			glColorMaski(i,write_colour,write_colour,write_colour,write_colour);
			CUtility::checkGLError();
		}
		glDepthFunc(GL_ALWAYS);
		CUtility::checkGLError();
		glDepthMask(mClearDepth>=0.0f);
		CUtility::checkGLError();
		if(mClearStencil>0.0f)
		{
			glEnable(GL_STENCIL_TEST);
			CUtility::checkGLError();
			glStencilFunc(GL_ALWAYS,mClearStencil,0xff);
			CUtility::checkGLError();
			glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);
			CUtility::checkGLError();
		}
		else
		{
			glStencilMask(0);
			CUtility::checkGLError();
		}
		glDisable(GL_CULL_FACE);
		CUtility::checkGLError();
		glUseProgram(CSystemImp::getSingleton().getClearViewportProgram()->getInternal());
		CUtility::checkGLError();
		auto cb=getConstantBufferMT();
		cb->submit();
		glBindBufferBase(GL_UNIFORM_BUFFER,0,cb->getInternal());
		CUtility::checkGLError();
		glUniformBlockBinding(CSystemImp::getSingleton().getClearViewportProgram()->getInternal(),CSystemImp::getSingleton().getClearViewportProgram()->getSlot(cb->getDescription()->getName()),0);
		CUtility::checkGLError();
		glDrawArrays(GL_TRIANGLE_STRIP,0,4);
		CUtility::checkGLError();
		glBindBuffer(GL_UNIFORM_BUFFER,0);
		CUtility::checkGLError();
		glUseProgram(0);
		CUtility::checkGLError();
		glEnable(GL_CULL_FACE);
		CUtility::checkGLError();
		glStencilMask(0xffffffff);
		CUtility::checkGLError();
		glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
		CUtility::checkGLError();
		glDisable(GL_STENCIL_TEST);
		CUtility::checkGLError();
		glDepthMask(true);
		CUtility::checkGLError();
		glDepthFunc(GL_LEQUAL);
		CUtility::checkGLError();
		for(GLuint i=0;i<8;++i)
		{
			glColorMaski(i,true,true,true,true);
			CUtility::checkGLError();
		}
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CClearViewportTask::_updateConstantBuffer(Byte * buffer)
{
	for(auto i=0;i<8;++i)
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gClearColour"+CStringConverter::toString(i)).mOffsetInBytes;
		memcpy(&buffer[offset],&mClearColour[i],sizeof(CColour));
	}
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gClearDepth").mOffsetInBytes;
	memcpy(&buffer[offset],&mClearDepth,sizeof(Float));
}

NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneForwardTask::CRenderSceneForwardTask(CViewport * viewport)
	:CRenderTask(viewport)
{
	mTasks.push_back(DEVILX_NEW CAmbientTask(mViewport));
}

NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneForwardTask::~CRenderSceneForwardTask()
{
	for(auto task:mLightTaskPool)
		DEVILX_DELETE(task);
}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneForwardTask::process()
{
}

NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneForwardTask::CAmbientTask::CAmbientTask(CViewport * viewport)
	:CRenderTask(viewport)
{
}

NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneForwardTask::CAmbientTask::~CAmbientTask()
{}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneForwardTask::CAmbientTask::process()
{
}

NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneForwardTask::CLightTask::CLightTask(CLight * light,CViewport * viewport)
	:CRenderTask(viewport)
	,mLight(light)
{
}

NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneForwardTask::CLightTask::~CLightTask()
{}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneForwardTask::CLightTask::process()
{
}

NSDevilX::NSRenderSystem::NSGLES3::CForwardRenderTask::CForwardRenderTask(CViewport * viewport)
	:CRenderTask(viewport)
{
	mTasks.push_back(DEVILX_NEW CClearViewportTask(viewport));
	mTasks.push_back(DEVILX_NEW CRenderSceneForwardTask(viewport));
}

NSDevilX::NSRenderSystem::NSGLES3::CForwardRenderTask::~CForwardRenderTask()
{}

Void NSDevilX::NSRenderSystem::NSGLES3::CForwardRenderTask::setClearColour(const CColour & colour)
{
	static_cast<CClearViewportTask*>(mTasks[0])->setClearColour(0,colour);
}

Void NSDevilX::NSRenderSystem::NSGLES3::CForwardRenderTask::setClearDepth(Float depth)
{
	static_cast<CClearViewportTask*>(mTasks[0])->setClearDepth(depth);
}

Void NSDevilX::NSRenderSystem::NSGLES3::CForwardRenderTask::setClearStencil(Int32 stencil)
{
	static_cast<CClearViewportTask*>(mTasks[0])->setClearStencil(stencil);
}

Void NSDevilX::NSRenderSystem::NSGLES3::CForwardRenderTask::process()
{
	mTasks[0]->process();
	mTasks[1]->process();
}

NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneGBufferTask::CRenderSceneGBufferTask(CViewport * viewport)
	:CRenderTask(viewport)
{}

NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneGBufferTask::~CRenderSceneGBufferTask()
{}

Void NSDevilX::NSRenderSystem::NSGLES3::CRenderSceneGBufferTask::process()
{
}
#endif