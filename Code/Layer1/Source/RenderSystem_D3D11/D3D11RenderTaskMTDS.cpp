#include "Precompiler.h"
#if DEVILX_RENDERSYSTEM_D3D11_MODE==DEVILX_RENDERSYSTEM_D3D11_MT_DS
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			namespace NSInternal
			{
				static Boolean threadFunction(VoidPtr parameter)
				{
					auto task=static_cast<CRenderTask*>(parameter);
					task->prepare();
					return true;
				}
			}
		}
	}
}
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::CRenderTask(CViewport * viewport)
	:mViewport(viewport)
	,mContext(nullptr)
	,mCommandList(nullptr)
	,mThreadSyncGroupID(CSystemImp::getSingleton().getRenderTaskThreadPool()->nextSyncGroupID())
{
	CSystemImp::getSingleton().getDevice()->CreateDeferredContext1(0,&mContext);
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::~CRenderTask()
{
	clearState();
	for(auto task:mTasks)
		DEVILX_DELETE(task);
	auto ref_count=mContext->Release();
	assert(0==ref_count);
	if(mCommandList)
	{
		ref_count=mCommandList->Release();
		assert(0==ref_count);
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::submit()
{
	CSystemImp::getSingleton().getRenderTaskThreadPool()->submitMT(NSInternal::threadFunction,this,mThreadSyncGroupID);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::prepare()
{
	if(mTasks.empty())
	{
		mContext->FinishCommandList(FALSE,&mCommandList);
		assert(mCommandList);
	}
	else
	{
		for(auto task:mTasks)
			task->prepare();
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::process()
{
	CSystemImp::getSingleton().getRenderTaskThreadPool()->waitMT(mThreadSyncGroupID);
	if(mTasks.empty())
	{
		CSystemImp::getSingleton().getImmediateContext()->ExecuteCommandList(mCommandList,FALSE);
		mCommandList->Release();
		mCommandList=nullptr;
	}
	else
	{
		for(auto task:mTasks)
			task->process();
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::clearState()
{
	if(mTasks.empty())
	{
		mContext->ClearState();
		mContext->FinishCommandList(FALSE,&mCommandList);
		mCommandList->Release();
		mCommandList=nullptr;
	}
	else
	{
		for(auto task:mTasks)
			task->clearState();
	}
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
				context->ClearRenderTargetView(mViewport->getRenderTarget()->getRTView(i),reinterpret_cast<ConstFloatPtr>(static_cast<CFloat4*>(&mClearColour[i])));
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
		memcpy(&buffer[offset],&mClearColour[i],sizeof(CColour));
	}
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gClearDepth").StartOffset;
	memcpy(&buffer[offset],&mClearDepth,sizeof(Float));
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

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::prepare()
{
	mViewport->getCamera()->getInterfaceImp()->findVisibleObjectsMT();
	while(mTasks.size()>1)
	{
		mLightTaskPool.push_back(static_cast<CLightTask*>(mTasks.back()));
		mTasks.pop_back();
	}
	for(auto const & light_pair:static_cast<ISceneImp*>(static_cast<ISceneElementImp*>(mViewport->getCamera()->getInterfaceImp()->queryInterface_ISceneElement())->getScene())->getLights())
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
		mTasks.push_back(task);
	}
	CLightTask * first_light_task=nullptr;
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
		//提高线程利用率
		if(first_light_task)
			task->submit();
		else
			first_light_task=task;
		mTasks.push_back(task);
	}
	if(first_light_task)
		first_light_task->prepare();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::process()
{
	mViewport->setupMT(CSystemImp::getSingleton().getImmediateContext());
	CRenderTask::process();
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CAmbientTask::CAmbientTask(CViewport * viewport)
	:CRenderTask(viewport)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CAmbientTask::~CAmbientTask()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CAmbientTask::process()
{
	TVector<CEntityRenderableImp*> solid_renderables,transparent_renderables;
	for(auto object:mViewport->getCamera()->getInterfaceImp()->getVisibleEntities())
	{
		for(UInt32 i=0;i<object->getRenderableCount();++i)
		{
			auto renderable=static_cast<CEntityRenderableImp*>(static_cast<IEntityRenderableImp*>(object->getRenderable(i))->getUserPointer(0));
			if(renderable->getInterfaceImp()->getTransparentEnable())
				transparent_renderables.push_back(renderable);
			else
				solid_renderables.push_back(renderable);
		}
	}
	TVector<CConstantBuffer*> common_constant_buffers;
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
	if(mLight->getInterfaceImp()->getType()==IEnum::ELightType_Directional)
	{
		TVector<CConstantBuffer*> common_constant_buffers;
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
		if(auto cb=mLight->getConstantBufferMT())
		{
			cb->submit();
			common_constant_buffers.push_back(cb);
		}
		CRenderOperation operation(CSystemImp::getSingleton().getImmediateContext());
		for(auto object:mViewport->getCamera()->getInterfaceImp()->getVisibleEntities())
		{
			for(UInt32 i=0;i<object->getRenderableCount();++i)
			{
				auto renderable=static_cast<CEntityRenderableImp*>(static_cast<IEntityRenderableImp*>(object->getRenderable(i))->getUserPointer(0));
				if(renderable->getInterfaceImp()->getLightEnable())
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
		for(auto cb:mSubmitConstantBuffers)
			cb->submit();
		CRenderTask::process();
		mSubmitConstantBuffers.clear();
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CLightTask::prepare()
{
	if(mLight->getInterfaceImp()->getType()==IEnum::ELightType_Directional)
		return;
	mLight->getInterfaceImp()->findVisibleObjectsMT();
	mViewport->setupMT(mContext);
	TVector<CConstantBuffer*> common_constant_buffers;
	if(auto cb=CSystemImp::getSingleton().getConstantBufferMT())
	{
		common_constant_buffers.push_back(cb);
		mSubmitConstantBuffers.push_back(cb);
	}
	if(auto cb=getViewport()->getRenderTarget()->getConstantBufferMT())
	{
		common_constant_buffers.push_back(cb);
		mSubmitConstantBuffers.push_back(cb);
	}
	if(auto cb=getViewport()->getConstantBufferMT())
	{
		common_constant_buffers.push_back(cb);
		mSubmitConstantBuffers.push_back(cb);
	}
	if(auto cb=getViewport()->getCamera()->getConstantBufferMT())
	{
		common_constant_buffers.push_back(cb);
		mSubmitConstantBuffers.push_back(cb);
	}
	if(auto cb=mLight->getConstantBufferMT())
	{
		common_constant_buffers.push_back(cb);
		mSubmitConstantBuffers.push_back(cb);
	}
	CRenderOperation operation(mContext);
	for(auto object:mLight->getInterfaceImp()->getVisibleEntities())
	{
		for(UInt32 i=0;i<object->getRenderableCount();++i)
		{
			auto renderable=static_cast<CEntityRenderableImp*>(static_cast<IEntityRenderableImp*>(object->getRenderable(i))->getUserPointer(0));
			if(renderable->getInterfaceImp()->getLightEnable())
			{
				renderable->renderForward(mLight,operation);
				mSubmitConstantBuffers.insert(mSubmitConstantBuffers.end(),operation.mConstantBuffers.begin(),operation.mConstantBuffers.end());
				operation.mConstantBuffers.insert(operation.mConstantBuffers.end(),common_constant_buffers.begin(),common_constant_buffers.end());
				operation.process();
				operation.mConstantBuffers.clear();
			}
		}
	}
	CRenderTask::prepare();
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

Void NSDevilX::NSRenderSystem::NSD3D11::CForwardRenderTask::prepare()
{
	mTasks[1]->submit();
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneGBufferTask::CRenderSceneGBufferTask(CViewport * viewport)
	:CRenderTask(viewport)
{}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneGBufferTask::~CRenderSceneGBufferTask()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneGBufferTask::prepare()
{
}
#endif