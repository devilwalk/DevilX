#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IQueryImp::IQueryImp(const String & name,IViewportImp * vp)
	:mName(name)
	,mViewport(vp)
{}

NSDevilX::NSRenderSystem::IQueryImp::~IQueryImp()
{}

const String & NSDevilX::NSRenderSystem::IQueryImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

IViewport * NSDevilX::NSRenderSystem::IQueryImp::getViewport() const
{
	return mViewport;
}

Void NSDevilX::NSRenderSystem::IQueryImp::setArea(const CFloat2 & startPosition,const CFloat2 & endPosition)
{
	mStartPosition=startPosition;
	mEndPosition=endPosition;
}

const CFloat2 & NSDevilX::NSRenderSystem::IQueryImp::getStartPosition() const
{
	// TODO: 在此处插入 return 语句
	return mStartPosition;
}

const CFloat2 & NSDevilX::NSRenderSystem::IQueryImp::getEndPosition() const
{
	// TODO: 在此处插入 return 语句
	return mEndPosition;
}
