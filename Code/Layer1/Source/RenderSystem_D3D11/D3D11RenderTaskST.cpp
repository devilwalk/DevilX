#include "Precompiler.h"
#if DEVILX_RENDERSYSTEM_D3D11_MODE==DEVILX_RENDERSYSTEM_D3D11_ST
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::CRenderTask(CViewport * viewport)
	:mViewport(viewport)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::~CRenderTask()
{
	for(auto task:mTasks)
		DEVILX_DELETE(task);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::process()
{
	for(auto task:mTasks)
		task->process();
}

NSDevilX::NSRenderSystem::NSD3D11::CClearViewportTask::CClearViewportTask(CViewport * viewport)
	:CRenderTask(viewport)
	,CConstantBufferContainer("cbClearViewport")
	,mClearDepth(1.0f)
	,mClearStencil(0)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CClearViewportTask::~CClearViewportTask()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CClearViewportTask::process()
{
	auto context=CSystemImp::getSingleton().getImmediateContext();
	if(mViewport->isFullViewport())
	{
		for(auto i=0;i<8;++i)
		{
			if((mClearColour[i]>=CFloat4::sZero)&&mViewport->getRenderTarget()->getRTView(i))
				context->ClearRenderTargetView(mViewport->getRenderTarget()->getRTView(i),reinterpret_cast<ConstFloatPtr>(&mClearColour));
		}
		UINT clear_flag=(mClearDepth>=0.0f?D3D11_CLEAR_DEPTH:0)|(mClearStencil>=0?D3D11_CLEAR_STENCIL:0);
		if(mViewport->getRenderTarget()->getDSView())
			context->ClearDepthStencilView(mViewport->getRenderTarget()->getDSView(),clear_flag,mClearDepth,static_cast<UInt8>(mClearStencil));
	}
	else
	{
		mViewport->setupMT(context);
		UInt32 flag=0;
		for(auto i=0;i<8;++i)
		{
			flag|=mClearColour[i]>=CFloat4::sZero?1:0;
		}
		flag|=mClearDepth>=0.0f?2:0;
		flag|=mClearStencil>0.0f?4:0;
		CClearViewportShader::EType type;
		switch(flag)
		{
		case 1:type=CClearViewportShader::EType_ColourOnly;break;
		case 2:type=CClearViewportShader::EType_DepthOnly;break;
		case 3:type=CClearViewportShader::EType_ColourAndDepth;break;
		case 4:type=CClearViewportShader::EType_StencilOnly;break;
		case 5:type=CClearViewportShader::EType_ColourAndStencil;break;
		case 6:type=CClearViewportShader::EType_DepthAndStencil;break;
		case 7:type=CClearViewportShader::EType_All;break;
		default:
			assert(0);
			break;
		}
		context->OMSetDepthStencilState(CSystemImp::getSingleton().getClearViewportShader()->getDepthStencilState(type),static_cast<UINT>(mClearStencil));
		context->OMSetBlendState(CSystemImp::getSingleton().getClearViewportShader()->getBlendState(type),reinterpret_cast<ConstFloatPtr>(&CFloat4::sOne),0xffffffff);
		context->RSSetState(CSystemImp::getSingleton().getClearViewportShader()->getRasterizerState());
		context->IASetInputLayout(nullptr);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		context->VSSetShader(CSystemImp::getSingleton().getClearViewportShader()->getVertexShader()->getInternal(),nullptr,0);
		auto cb=getConstantBufferMT();
		cb->submit();
		ID3D11Buffer * constant_buffer[]={cb->getInternal()};
		context->VSSetConstantBuffers(0,1,constant_buffer);
		context->PSSetShader(CSystemImp::getSingleton().getClearViewportShader()->getPixelShader()->getInternal(),nullptr,0);
		context->PSSetConstantBuffers(0,1,constant_buffer);
		context->Draw(4,0);
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CClearViewportTask::_updateConstantBuffer(Byte * buffer)
{
	for(auto i=0;i<8;++i)
	{
		auto offset=mConstantBuffer->getDescription()->getConstantDesc("gClearColour"+CStringConverter::toString(i)).StartOffset;
		*reinterpret_cast<CFloatRGBA*>(&buffer[offset])=mClearColour[i];
	}
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gClearDepth").StartOffset;
	*reinterpret_cast<Float*>(&buffer[offset])=mClearDepth;
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CRenderSceneForwardTask(CViewport * viewport)
	:CRenderTask(viewport)
{
	mTasks.push_back(DEVILX_NEW CAmbientTask(mViewport));
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::~CRenderSceneForwardTask()
{
	for(auto task:mLightTaskPool)
		DEVILX_DELETE(task);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::process()
{
	auto context=CSystemImp::getSingleton().getImmediateContext();
	mViewport->getCamera()->getInterfaceImp()->findVisibleObjectsMT();
	mViewport->setupMT(context);
	mTasks[0]->process();
	while(mTasks.size()>1)
	{
		mLightTaskPool.push_back(static_cast<CLightTask*>(mTasks.back()));
		mTasks.pop_back();
	}
	for(auto const & light_pair:static_cast<ISceneElementImp*>(mViewport->getCamera()->getInterfaceImp()->queryInterface_ISceneElement())->getScene()->getLights())
	{
		auto light=light_pair.second;
		if(light->getType()!=IEnum::ELightType_Directional)
			continue;
		CLightTask * task=nullptr;
		if(mLightTaskPool.empty())
			task=DEVILX_NEW CLightTask(static_cast<CLight*>(light->getUserPointer(0)),mViewport);
		else
		{
			task=mLightTaskPool.back();
			task->setLight(static_cast<CLight*>(light->getUserPointer(0)));
			mLightTaskPool.pop_back();
		}
		task->process();
		mTasks.push_back(task);
	}
	for(auto light:mViewport->getCamera()->getInterfaceImp()->getVisibleLights())
	{
		CLightTask * task=nullptr;
		if(mLightTaskPool.empty())
			task=DEVILX_NEW CLightTask(static_cast<CLight*>(light->getUserPointer(0)),mViewport);
		else
		{
			task=mLightTaskPool.back();
			task->setLight(static_cast<CLight*>(light->getUserPointer(0)));
			mLightTaskPool.pop_back();
		}
		task->process();
		mTasks.push_back(task);
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CAmbientTask::CAmbientTask(CViewport * viewport)
	:CRenderTask(viewport)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CAmbientTask::~CAmbientTask()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CAmbientTask::process()
{
	TVector(CRenderable*) solid_renderables,transparent_renderables,sky_solid_renderables,sky_transparent_renderables;
	for(auto object:mViewport->getCamera()->getInterfaceImp()->getVisibleRenderableObjects())
	{
		for(UInt32 i=0;i<object->getRenderableCount();++i)
		{
			auto renderable=static_cast<CRenderable*>(static_cast<IRenderableImp*>(object->getRenderable(i))->getUserPointer(0));
			if(renderable->getInterfaceImp()->getSky())
			{
				if(renderable->getInterfaceImp()->queryInterface_IMaterial()->getTransparentEnable())
					sky_transparent_renderables.push_back(renderable);
				else
					sky_solid_renderables.push_back(renderable);
			}
			else
			{
				if(renderable->getInterfaceImp()->queryInterface_IMaterial()->getTransparentEnable())
					transparent_renderables.push_back(renderable);
				else
					solid_renderables.push_back(renderable);
			}
		}
	}
	TVector(CConstantBuffer*) common_constant_buffers;
	if(auto cb=CSystemImp::getSingleton().getConstantBufferMT())
	{
		cb->submit();
		common_constant_buffers.push_back(cb);
	}
	if(auto cb=getViewport()->getRenderTarget()->getConstantBufferMT())
	{
		cb->submit();
		common_constant_buffers.push_back(cb);
	}
	if(auto cb=getViewport()->getConstantBufferMT())
	{
		cb->submit();
		common_constant_buffers.push_back(cb);
	}
	if(auto cb=getViewport()->getCamera()->getConstantBufferMT())
	{
		cb->submit();
		common_constant_buffers.push_back(cb);
	}
	CRenderOperation operation(CSystemImp::getSingleton().getImmediateContext());
	for(auto renderable:solid_renderables)
	{
		renderable->renderForward(nullptr,operation);
		for(auto cb:operation.mConstantBuffers)
			cb->submit();
		operation.mConstantBuffers.insert(operation.mConstantBuffers.end(),common_constant_buffers.begin(),common_constant_buffers.end());
		operation.process();
		operation.mConstantBuffers.clear();
	}
	for(auto renderable:sky_solid_renderables)
	{
		renderable->renderForward(nullptr,operation);
		for(auto cb:operation.mConstantBuffers)
			cb->submit();
		operation.mConstantBuffers.insert(operation.mConstantBuffers.end(),common_constant_buffers.begin(),common_constant_buffers.end());
		operation.process();
		operation.mConstantBuffers.clear();
	}
	for(auto renderable:sky_transparent_renderables)
	{
		renderable->renderForward(nullptr,operation);
		for(auto cb:operation.mConstantBuffers)
			cb->submit();
		operation.mConstantBuffers.insert(operation.mConstantBuffers.end(),common_constant_buffers.begin(),common_constant_buffers.end());
		operation.process();
		operation.mConstantBuffers.clear();
	}
	for(auto renderable:transparent_renderables)
	{
		renderable->renderForward(nullptr,operation);
		for(auto cb:operation.mConstantBuffers)
			cb->submit();
		operation.mConstantBuffers.insert(operation.mConstantBuffers.end(),common_constant_buffers.begin(),common_constant_buffers.end());
		operation.process();
		operation.mConstantBuffers.clear();
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CLightTask::CLightTask(CLight * light,CViewport * viewport)
	:CRenderTask(viewport)
	,mLight(light)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CLightTask::~CLightTask()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CLightTask::process()
{
	mLight->getInterfaceImp()->findVisibleObjectsMT();
	TVector(CConstantBuffer*) common_constant_buffers;
	if(auto cb=CSystemImp::getSingleton().getConstantBufferMT())
	{
		cb->submit();
		common_constant_buffers.push_back(cb);
	}
	if(auto cb=getViewport()->getRenderTarget()->getConstantBufferMT())
	{
		cb->submit();
		common_constant_buffers.push_back(cb);
	}
	if(auto cb=getViewport()->getConstantBufferMT())
	{
		cb->submit();
		common_constant_buffers.push_back(cb);
	}
	if(auto cb=getViewport()->getCamera()->getConstantBufferMT())
	{
		cb->submit();
		common_constant_buffers.push_back(cb);
	}
	CRenderOperation operation(CSystemImp::getSingleton().getImmediateContext());
	if(mLight->getInterfaceImp()->getType()==IEnum::ELightType_Directional)
	{
		for(auto object:mViewport->getCamera()->getInterfaceImp()->getVisibleRenderableObjects())
		{
			for(UInt32 i=0;i<object->getRenderableCount();++i)
			{
				auto renderable=static_cast<CRenderable*>(static_cast<IRenderableImp*>(object->getRenderable(i))->getUserPointer(0));
				if(renderable->getInterfaceImp()->queryInterface_IMaterial()->getLightEnable())
				{
					renderable->renderForward(mLight,operation);
					for(auto cb:operation.mConstantBuffers)
						cb->submit();
					operation.mConstantBuffers.insert(operation.mConstantBuffers.end(),common_constant_buffers.begin(),common_constant_buffers.end());
					operation.process();
					operation.mConstantBuffers.clear();
				}
			}
		}
	}
	else
	{
		for(auto object:mLight->getInterfaceImp()->getVisibleRenderableObjects())
		{
			for(UInt32 i=0;i<object->getRenderableCount();++i)
			{
				auto renderable=static_cast<CRenderable*>(static_cast<IRenderableImp*>(object->getRenderable(i))->getUserPointer(0));
				if(renderable->getInterfaceImp()->queryInterface_IMaterial()->getLightEnable())
				{
					renderable->renderForward(mLight,operation);
					for(auto cb:operation.mConstantBuffers)
						cb->submit();
					operation.mConstantBuffers.insert(operation.mConstantBuffers.end(),common_constant_buffers.begin(),common_constant_buffers.end());
					operation.process();
					operation.mConstantBuffers.clear();
				}
			}
		}
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CForwardRenderTask::CForwardRenderTask(CViewport * viewport)
	:CRenderTask(viewport)
{
	mTasks.push_back(DEVILX_NEW CClearViewportTask(viewport));
	mTasks.push_back(DEVILX_NEW CRenderSceneForwardTask(viewport));
}

NSDevilX::NSRenderSystem::NSD3D11::CForwardRenderTask::~CForwardRenderTask()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CForwardRenderTask::setClearColour(const CColour & colour)
{
	static_cast<CClearViewportTask*>(mTasks[0])->setClearColour(0,colour);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CForwardRenderTask::setClearDepth(Float depth)
{
	static_cast<CClearViewportTask*>(mTasks[0])->setClearDepth(depth);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CForwardRenderTask::setClearStencil(Int32 stencil)
{
	static_cast<CClearViewportTask*>(mTasks[0])->setClearStencil(stencil);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CForwardRenderTask::process()
{
	mTasks[0]->process();
	mTasks[1]->process();
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneGBufferTask::CRenderSceneGBufferTask(CViewport * viewport)
	:CRenderTask(viewport)
{}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneGBufferTask::~CRenderSceneGBufferTask()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneGBufferTask::process()
{
}
#endif