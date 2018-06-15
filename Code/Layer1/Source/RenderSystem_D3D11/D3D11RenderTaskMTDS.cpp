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
				static Void threadFunction(VoidPtr parameter)
				{
					auto task=static_cast<CRenderTask*>(parameter);
					task->prepare();
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
	mTasks.destroyAll();
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
	if(_needSubmit())
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
		{
			if(task)
				task->prepare();
		}
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::process()
{
	CSystemImp::getSingleton().getRenderTaskThreadPool()->waitMT(mThreadSyncGroupID);
	_process();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::postProcess()
{}

Boolean NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::_needSubmit() const
{
	return true;
}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderTask::_process()
{
	if(mTasks.empty())
	{
		if(mCommandList)
		{
			CSystemImp::getSingleton().getImmediateContext()->ExecuteCommandList(mCommandList,FALSE);
			mCommandList->Release();
			mCommandList=nullptr;
		}
	}
	else
	{
		for(auto task:mTasks)
		{
			if(task)
				task->process();
		}
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
		{
			if(task)
				task->clearState();
		}
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
		if(mViewport->getRenderTarget()->getDepthStencil())
			context->ClearDepthStencilView(mViewport->getRenderTarget()->getDepthStencil()->getInternal(),clear_flag,mClearDepth,static_cast<UInt8>(mClearStencil));
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

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CAmbientTask::CAmbientTask(CViewport * viewport)
	:CRenderTask(viewport)
{}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CAmbientTask::~CAmbientTask()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CAmbientTask::process()
{
	TVector<CSubEntityImp*> solid_renderables,transparent_renderables;
	for(auto object:mViewport->getCamera()->getInterfaceImp()->getVisibleEntities())
	{
		for(UInt32 i=0;i<object->getSubEntityCount();++i)
		{
			if(object->getSubEntity(i)->isRenderable())
			{
				auto renderable=static_cast<ISubEntityImp*>(object->getSubEntity(i))->getUserPointer<CSubEntityImp>(0);
				if(renderable->getInterfaceImp()->getTransparentEnable())
					transparent_renderables.push_back(renderable);
				else
					solid_renderables.push_back(renderable);
			}
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
{}

NSDevilX::NSRenderSystem::NSD3D11::CRenderSceneForwardTask::CLightTask::~CLightTask()
{}

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
		for(UInt32 i=0;i<object->getSubEntityCount();++i)
		{
			if(object->getSubEntity(i)->isRenderable())
			{
				auto renderable=static_cast<ISubEntityImp*>(object->getSubEntity(i))->getUserPointer<CSubEntityImp>(0);
				if((renderable->getInterfaceImp()->getDiffuseModel()!=IEnum::EMaterialDiffuseModel_None)||
					(renderable->getInterfaceImp()->getSpecularModel()!=IEnum::EMaterialSpecularModel_None))
				{
					renderable->renderForward(mLight,operation);
					mSubmitConstantBuffers.insert(mSubmitConstantBuffers.end(),operation.mConstantBuffers.begin(),operation.mConstantBuffers.end());
					operation.mConstantBuffers.insert(operation.mConstantBuffers.end(),common_constant_buffers.begin(),common_constant_buffers.end());
					operation.process();
					operation.mConstantBuffers.clear();
				}
			}
		}
	}
	CRenderTask::prepare();
}

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
			for(UInt32 i=0;i<object->getSubEntityCount();++i)
			{
				if(object->getSubEntity(i)->isRenderable())
				{
					auto renderable=static_cast<ISubEntityImp*>(object->getSubEntity(i))->getUserPointer<CSubEntityImp>(0);
					if((renderable->getInterfaceImp()->getDiffuseModel()!=IEnum::EMaterialDiffuseModel_None)||
						(renderable->getInterfaceImp()->getSpecularModel()!=IEnum::EMaterialSpecularModel_None))
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
	else
	{
		CSystemImp::getSingleton().getRenderTaskThreadPool()->waitMT(mThreadSyncGroupID);
		for(auto cb:mSubmitConstantBuffers)
			cb->submit();
		mSubmitConstantBuffers.clear();
		CRenderTask::_process();
	}
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
			task=DEVILX_NEW CLightTask(light->getUserPointer<CLight>(0),mViewport);
		else
		{
			task=mLightTaskPool.back();
			task->setLight(light->getUserPointer<CLight>(0));
			mLightTaskPool.pop_back();
		}
		mTasks.push_back(task);
	}
	CLightTask * first_light_task=nullptr;
	for(auto light:mViewport->getCamera()->getInterfaceImp()->getVisibleLights())
	{
		CLightTask * task=nullptr;
		if(mLightTaskPool.empty())
			task=DEVILX_NEW CLightTask(light->getUserPointer<CLight>(0),mViewport);
		else
		{
			task=mLightTaskPool.back();
			task->setLight(light->getUserPointer<CLight>(0));
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
	CSystemImp::getSingleton().getRenderTaskThreadPool()->waitMT(mThreadSyncGroupID);
	mViewport->setupMT(CSystemImp::getSingleton().getImmediateContext());
	CRenderTask::_process();
}

NSDevilX::NSRenderSystem::NSD3D11::CQuerySceneTask::CQuerySceneTask(CViewport * viewport)
	:CRenderTask(viewport)
{

}

NSDevilX::NSRenderSystem::NSD3D11::CQuerySceneTask::~CQuerySceneTask()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CQuerySceneTask::prepare()
{
	mViewport->getCamera()->getInterfaceImp()->findVisibleObjectsMT();
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
	CRenderOperation operation(mContext);
	for(auto object:mViewport->getCamera()->getInterfaceImp()->getVisibleEntities())
	{
		for(UInt32 i=0;i<object->getSubEntityCount();++i)
		{
			if(object->getSubEntity(i)->isQueriable())
			{
				auto renderable=static_cast<ISubEntityImp*>(object->getSubEntity(i))->getUserPointer<CSubEntityImp>(0);
				renderable->query(operation);
				mSubmitConstantBuffers.insert(mSubmitConstantBuffers.end(),operation.mConstantBuffers.begin(),operation.mConstantBuffers.end());
				operation.mConstantBuffers.insert(operation.mConstantBuffers.end(),common_constant_buffers.begin(),common_constant_buffers.end());
				operation.process();
				operation.mConstantBuffers.clear();
			}
		}
	}
	CComPtr<ID3D11Resource> rt_res;
	mViewport->getRenderTarget()->getRTView(0)->GetResource(&rt_res);
	for(const auto & query:mQueries)
	{
		mContext->CopySubresourceRegion1(query.mBuffer,0,0,0,0,rt_res,0,query.mBox,D3D11_COPY_DISCARD);
	}
	CRenderTask::prepare();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CQuerySceneTask::process()
{
	CSystemImp::getSingleton().getRenderTaskThreadPool()->waitMT(mThreadSyncGroupID);
	for(auto cb:mSubmitConstantBuffers)
		cb->submit();
	mSubmitConstantBuffers.clear();
	CRenderTask::_process();
}

Boolean NSDevilX::NSRenderSystem::NSD3D11::CQuerySceneTask::_needSubmit() const
{
	return !mQueries.empty();
}

NSDevilX::NSRenderSystem::NSD3D11::CForwardRenderTask::CForwardRenderTask(CViewport * viewport)
	:CRenderTask(viewport)
{
	mTasks.resize(2);
	mTasks[0]=DEVILX_NEW CClearViewportTask(viewport);
	if(getViewport()->getCamera())
		mTasks[1]=DEVILX_NEW CRenderSceneForwardTask(viewport);
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
	if(getViewport()->getCamera()&&(nullptr==mTasks[1]))
		mTasks[1]=DEVILX_NEW CRenderSceneForwardTask(getViewport());
	else if((nullptr==getViewport()->getCamera())&&((nullptr!=mTasks[1])))
	{
		DEVILX_DELETE(mTasks[1]);
		mTasks[1]=nullptr;
	}
	if(mTasks[1])
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

NSDevilX::NSRenderSystem::NSD3D11::CQueryTask::CQueryTask(CViewport * viewport)
	:CRenderTask(viewport)
{
	mTasks.resize(2);
	mTasks[0]=DEVILX_NEW CClearViewportTask(viewport);
	static_cast<CClearViewportTask*>(mTasks[0])->setClearColour(0,CFloatRGBA::sWhite);
	mTasks[1]=DEVILX_NEW CQuerySceneTask(viewport);
}

NSDevilX::NSRenderSystem::NSD3D11::CQueryTask::~CQueryTask()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CQueryTask::setClearDepth(Float depth)
{
	static_cast<CClearViewportTask*>(mTasks[0])->setClearDepth(depth);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CQueryTask::setClearStencil(Int32 stencil)
{
	static_cast<CClearViewportTask*>(mTasks[0])->setClearStencil(stencil);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CQueryTask::setQueryRange(SizeT key,const CFloat2 & startPosition,const CFloat2 & endPosition)
{
	auto & query=mQueries[key];
	query.mAreaPosition=CFloat4(startPosition,endPosition);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CQueryTask::removeQueryRange(SizeT key)
{
	mQueries.erase(key);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CQueryTask::prepare()
{
	if(getViewport()->getCamera())
	{
		static_cast<CQuerySceneTask*>(mTasks[1])->clearQuery();
		for(auto & query_pair:mQueries)
		{
			auto & query=query_pair.second;
			if((query.mAreaPosition>=CFloat4::sZero)&&(query.mAreaPosition<=CFloat4::sOne))
			{
				const CUInt4 new_box=query.mAreaPosition*CFloat4(mViewport->getInternal().Width,mViewport->getInternal().Height,mViewport->getInternal().Width,mViewport->getInternal().Height)+CFloat4(0,0,1.0f,1.0f)+CFloat4(mViewport->getInternal().TopLeftX,mViewport->getInternal().TopLeftY,mViewport->getInternal().TopLeftX,mViewport->getInternal().TopLeftY);
				if(((new_box.z-new_box.x)!=(query.mBox.right-query.mBox.left))||(new_box.w-new_box.y)!=(query.mBox.bottom-query.mBox.top))
				{
					D3D11_TEXTURE2D_DESC desc={0};
					desc.ArraySize=1;
					desc.BindFlags=0;
					desc.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
					desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
					desc.Height=new_box.w-new_box.y;
					desc.MipLevels=1;
					desc.SampleDesc.Count=1;
					desc.SampleDesc.Quality=0;
					desc.Usage=D3D11_USAGE_STAGING;
					desc.Width=new_box.z-new_box.x;
					CSystemImp::getSingleton().getDevice()->CreateTexture2D(&desc,nullptr,&query.mBuffer);
				}
				if(new_box!=CUInt4(query.mBox.left,query.mBox.top,query.mBox.right,query.mBox.bottom))
				{
					query.mBox.left=new_box.x;
					query.mBox.top=new_box.y;
					query.mBox.right=new_box.z;
					query.mBox.bottom=new_box.w;
				}
				static_cast<CQuerySceneTask*>(mTasks[1])->addQuery(query.mBox,query.mBuffer);
			}
		}
		mTasks[1]->submit();
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CQueryTask::postProcess()
{
	mQueryResults.clear();
	for(auto & query_pair:mQueries)
	{
		auto const & query=query_pair.second;
		if((query.mAreaPosition>=CFloat4::sZero)&&(query.mAreaPosition<=CFloat4::sOne)&&query.mBuffer)
		{
			D3D11_MAPPED_SUBRESOURCE res;
			CSystemImp::getSingleton().getImmediateContext()->Map(query.mBuffer,0,D3D11_MAP_READ,0,&res);
			for(UInt32 u=0;u<query.mBox.right-query.mBox.left;++u)
			{
				for(UInt32 v=0;v<query.mBox.bottom-query.mBox.top;++v)
				{
					UInt32 result=*reinterpret_cast<UInt32*>(static_cast<Byte*>(res.pData)+v*res.RowPitch+u*sizeof(UInt32));
					if(result<static_cast<UInt32>(-1))
						mQueryResults.insert(result);
				}
			}
			CSystemImp::getSingleton().getImmediateContext()->Unmap(query.mBuffer,0);
		}
	}
}

#endif