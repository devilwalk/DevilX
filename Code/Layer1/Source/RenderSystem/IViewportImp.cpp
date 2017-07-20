#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::IViewportImp::IViewportImp(const String & name,IRenderTargetImp * rt)
	:mName(name)
	,mRenderTarget(rt)
	,mCamera(nullptr)
	,mLeft(0)
	,mTop(0)
	,mWidth(1.0f)
	,mHeight(1.0f)
	,mOrder(100)
	,mTechnique(IEnum::ERenderTechnique_Forward)
{
}

NSDevilX::NSRenderSystem::IViewportImp::~IViewportImp()
{
}

Boolean NSDevilX::NSRenderSystem::IViewportImp::isFullViewport() const
{
	return mLeft==0&&mTop==0&&mWidth==1.0f&&mHeight==1.0f;
}

IOverlay * NSDevilX::NSRenderSystem::IViewportImp::queryInterface_IOverlay() const
{
	return const_cast<IViewportImp*>(this);
}

const String & NSDevilX::NSRenderSystem::IViewportImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

Void NSDevilX::NSRenderSystem::IViewportImp::setCamera(ICamera * camera)
{
	assert(nullptr==static_cast<ICameraImp*>(camera)->getViewport());
	if(camera!=mCamera)
	{
		notify(EMessage_BeginCameraChange,static_cast<ICameraImp*>(camera));
		if(mCamera)
			mCamera->setViewport(nullptr);
		mCamera=static_cast<ICameraImp*>(camera);
		if(mCamera)
			mCamera->setViewport(this);
		notify(EMessage_EndCameraChange);
	}
}

ICamera * NSDevilX::NSRenderSystem::IViewportImp::getCamera() const
{
	return mCamera;
}

Void NSDevilX::NSRenderSystem::IViewportImp::setLeft(Float left)
{
	if(getLeft()!=left)
	{
		notify(EMessage_BeginLeftChange);
		mLeft=left;
		notify(EMessage_EndLeftChange);
	}
}

Float NSDevilX::NSRenderSystem::IViewportImp::getLeft() const
{
	return mLeft;
}

Void NSDevilX::NSRenderSystem::IViewportImp::setTop(Float top)
{
	if(getTop()!=top)
	{
		notify(EMessage_BeginTopChange);
		mTop=top;
		notify(EMessage_EndTopChange);
	}
}

Float NSDevilX::NSRenderSystem::IViewportImp::getTop() const
{
	return mTop;
}

Void NSDevilX::NSRenderSystem::IViewportImp::setWidth(Float width)
{
	if(getWidth()!=width)
	{
		notify(EMessage_BeginWidthChange);
		mWidth=width;
		notify(EMessage_EndWidthChange);
	}
}

Float NSDevilX::NSRenderSystem::IViewportImp::getWidth() const
{
	return mWidth;
}

Void NSDevilX::NSRenderSystem::IViewportImp::setHeight(Float height)
{
	if(getHeight()!=height)
	{
		notify(EMessage_BeginHeightChange);
		mHeight=height;
		notify(EMessage_EndHeightChange);
	}
}

Float NSDevilX::NSRenderSystem::IViewportImp::getHeight() const
{
	return mHeight;
}

Void NSDevilX::NSRenderSystem::IViewportImp::setOrder(UInt32 order)
{
	if(order!=mOrder)
	{
		notify(EMessage_BeginOrderChange);
		mOrder=order;
		notify(EMessage_EndOrderChange);
	}
}

UInt32 NSDevilX::NSRenderSystem::IViewportImp::getOrder() const
{
	return mOrder;
}

Void NSDevilX::NSRenderSystem::IViewportImp::setTechnique(IEnum::ERenderTechnique technique)
{
	if(technique!=mTechnique)
	{
		notify(EMessage_BeginTechniqueChange);
		mTechnique=technique;
		notify(EMessage_EndTechniqueChange);
	}
}

IEnum::ERenderTechnique NSDevilX::NSRenderSystem::IViewportImp::getTechnique() const
{
	switch(mTechnique)
	{
	case IEnum::ERenderTechnique_Forward:
		return IEnum::ERenderTechnique_Forward;
	case IEnum::ERenderTechnique_DeferredShading:
		return IEnum::ERenderTechnique_DeferredShading;
	case IEnum::ERenderTechnique_DeferredLighting:
		return IEnum::ERenderTechnique_DeferredLighting;
	default:
		return IEnum::ERenderTechnique_Forward;
	}
}

Void NSDevilX::NSRenderSystem::IViewportImp::setClearColour(const CColour & colour)
{
	if(colour!=mClearColour)
	{
		notify(EMessage_BeginClearColourChange);
		mClearColour=colour;
		notify(EMessage_EndClearColourChange);
	}
}

const CColour & NSDevilX::NSRenderSystem::IViewportImp::getClearColour() const
{
	// TODO: insert return statement here
	return mClearColour;
}

IQuery * NSDevilX::NSRenderSystem::IViewportImp::createQuery(const String & name)
{
	if(mQueries.has(name))
		return nullptr;
	notify(EMessage_BeginQueryCreate);
	auto ret=DEVILX_NEW IQueryImp(name,this);
	mQueries.add(name,ret);
	notify(EMessage_EndQueryCreate,ret);
	if(getQueies().size()==1)
		notify(EMessage_QueryEnableChange);
	return ret;
}

IQuery * NSDevilX::NSRenderSystem::IViewportImp::getQuery(const String & name) const
{
	return mQueries.get(name);
}

Void NSDevilX::NSRenderSystem::IViewportImp::destroyQuery(IQuery * query)
{
	if(!mQueries.has(query->getName()))
		return;
	notify(EMessage_BeginQueryDestroy,static_cast<IQueryImp*>(query));
	mQueries.destroy(query->getName());
	notify(EMessage_EndQueryDestroy);
	if(getQueies().empty())
		notify(EMessage_QueryEnableChange);
}

const UInt32 * NSDevilX::NSRenderSystem::IViewportImp::getQueryDatas() const
{
	return mQueryDatas.empty()?nullptr:&mQueryDatas[0];
}

UInt32 NSDevilX::NSRenderSystem::IViewportImp::getQueryDatasCount() const
{
	return static_cast<UInt32>(mQueryDatas.size());
}

IOverlayElement * NSDevilX::NSRenderSystem::IViewportImp::createElement(const String & name)
{
	if(mOverlayElements.has(name))
		return nullptr;
	notify(EMessage_BeginOverlayElementCreate);
	auto ret=DEVILX_NEW IOverlayElementImp(name);
	mOverlayElements.add(name,ret);
	notify(EMessage_EndOverlayElementCreate,ret);
	return ret;
}

IOverlayElement * NSDevilX::NSRenderSystem::IViewportImp::getElement(const String & name) const
{
	return mOverlayElements.get(name);
}

Void NSDevilX::NSRenderSystem::IViewportImp::destroyElement(IOverlayElement * element)
{
	if(!mOverlayElements.has(element->getName()))
		return;
	notify(EMessage_BeginOverlayElementDestroy,static_cast<IOverlayElementImp*>(element));
	mOverlayElements.destroy(element->getName());
	notify(EMessage_EndOverlayElementDestroy);
}
