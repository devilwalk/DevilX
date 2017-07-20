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
	// TODO: �ڴ˴����� return ���
	return mName;
}

IViewport * NSDevilX::NSRenderSystem::IQueryImp::getViewport() const
{
	return mViewport;
}

Void NSDevilX::NSRenderSystem::IQueryImp::setArea(const CFloat2 & startPosition,const CFloat2 & endPosition)
{
	if((getStartPosition()!=startPosition)||(getEndPosition()!=endPosition))
	{
		notify(EMessage_BeginAreaChange);
		mStartPosition=startPosition;
		mEndPosition=endPosition;
		notify(EMessage_EndAreaChange);
	}
}

const CFloat2 & NSDevilX::NSRenderSystem::IQueryImp::getStartPosition() const
{
	// TODO: �ڴ˴����� return ���
	return mStartPosition;
}

const CFloat2 & NSDevilX::NSRenderSystem::IQueryImp::getEndPosition() const
{
	// TODO: �ڴ˴����� return ���
	return mEndPosition;
}
