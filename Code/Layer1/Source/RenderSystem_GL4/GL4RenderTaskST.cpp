#include "Precompiler.h"
#if DEVILX_RENDERSYSTEM_GL4_MODE==DEVILX_RENDERSYSTEM_GL4_ST
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CRenderTask::CRenderTask(CViewport * viewport)
	:mViewport(viewport)
{
}

NSDevilX::NSRenderSystem::NSGL4::CRenderTask::~CRenderTask()
{
	for(auto task:mTasks)
		DEVILX_DELETE(task);
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderTask::process()
{
	for(auto task:mTasks)
		task->process();
}

NSDevilX::NSRenderSystem::NSGL4::CClearViewportTask::CClearViewportTask(CViewport * viewport)
	:CRenderTask(viewport)
	,CConstantBufferContainer("cbClearViewport")
	,mClearDepth(1.0f)
	,mClearStencil(0)
{
}

NSDevilX::NSRenderSystem::NSGL4::CClearViewportTask::~CClearViewportTask()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CClearViewportTask::process()
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
		}
		glDepthFunc(GL_ALWAYS);
		glDepthMask(mClearDepth>=0.0f);
		if(mClearStencil>0.0f)
		{
			glEnable(GL_STENCIL_TEST);
			glStencilFunc(GL_ALWAYS,mClearStencil,0xff);
			glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);
		}
		else
		{
			glStencilMask(0);
		}
		glDisable(GL_CULL_FACE);
		glUseProgram(CSystemImp::getSingleton().getClearViewportProgram()->getInternal());
		auto cb=getConstantBufferMT();
		cb->submit();
		glBindBufferBase(GL_UNIFORM_BUFFER,0,cb->getInternal());
		glUniformBlockBinding(CSystemImp::getSingleton().getClearViewportProgram()->getInternal(),CSystemImp::getSingleton().getClearViewportProgram()->getSlot(cb->getDescription()->getName()),0);
		glDrawArrays(GL_TRIANGLE_STRIP,0,4);
		glBindBuffer(GL_UNIFORM_BUFFER,0);
		glUseProgram(0);
		glEnable(GL_CULL_FACE);
		glStencilMask(0xffffffff);
		glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
		glDisable(GL_STENCIL_TEST);
		glDepthMask(true);
		glDepthFunc(GL_LEQUAL);
		for(GLuint i=0;i<8;++i)
		{
			glColorMaski(i,true,true,true,true);
		}
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CClearViewportTask::_updateConstantBuffer(Byte * buffer)
{
	for(auto i=0;i<8;++i)
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gClearColour"+CStringConverter::toString(i)).mOffsetInBytes;
		memcpy(&buffer[offset],&mClearColour[i],sizeof(CColour));
	}
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gClearDepth").mOffsetInBytes;
	memcpy(&buffer[offset],&mClearDepth,sizeof(Float));
}

NSDevilX::NSRenderSystem::NSGL4::CRenderSceneForwardTask::CRenderSceneForwardTask(CViewport * viewport)
	:CRenderTask(viewport)
{
	mTasks.push_back(DEVILX_NEW CAmbientTask(mViewport));
}

NSDevilX::NSRenderSystem::NSGL4::CRenderSceneForwardTask::~CRenderSceneForwardTask()
{
	for(auto task:mLightTaskPool)
		DEVILX_DELETE(task);
}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderSceneForwardTask::process()
{
}

NSDevilX::NSRenderSystem::NSGL4::CRenderSceneForwardTask::CAmbientTask::CAmbientTask(CViewport * viewport)
	:CRenderTask(viewport)
{
}

NSDevilX::NSRenderSystem::NSGL4::CRenderSceneForwardTask::CAmbientTask::~CAmbientTask()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderSceneForwardTask::CAmbientTask::process()
{
}

NSDevilX::NSRenderSystem::NSGL4::CRenderSceneForwardTask::CLightTask::CLightTask(CLight * light,CViewport * viewport)
	:CRenderTask(viewport)
	,mLight(light)
{
}

NSDevilX::NSRenderSystem::NSGL4::CRenderSceneForwardTask::CLightTask::~CLightTask()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderSceneForwardTask::CLightTask::process()
{
}

NSDevilX::NSRenderSystem::NSGL4::CForwardRenderTask::CForwardRenderTask(CViewport * viewport)
	:CRenderTask(viewport)
{
	mTasks.push_back(DEVILX_NEW CClearViewportTask(viewport));
	mTasks.push_back(DEVILX_NEW CRenderSceneForwardTask(viewport));
}

NSDevilX::NSRenderSystem::NSGL4::CForwardRenderTask::~CForwardRenderTask()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CForwardRenderTask::setClearColour(const CColour & colour)
{
	static_cast<CClearViewportTask*>(mTasks[0])->setClearColour(0,colour);
}

Void NSDevilX::NSRenderSystem::NSGL4::CForwardRenderTask::setClearDepth(Float depth)
{
	static_cast<CClearViewportTask*>(mTasks[0])->setClearDepth(depth);
}

Void NSDevilX::NSRenderSystem::NSGL4::CForwardRenderTask::setClearStencil(Int32 stencil)
{
	static_cast<CClearViewportTask*>(mTasks[0])->setClearStencil(stencil);
}

Void NSDevilX::NSRenderSystem::NSGL4::CForwardRenderTask::process()
{
	mTasks[0]->process();
	mTasks[1]->process();
}

NSDevilX::NSRenderSystem::NSGL4::CRenderSceneGBufferTask::CRenderSceneGBufferTask(CViewport * viewport)
	:CRenderTask(viewport)
{}

NSDevilX::NSRenderSystem::NSGL4::CRenderSceneGBufferTask::~CRenderSceneGBufferTask()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CRenderSceneGBufferTask::process()
{
}
#endif