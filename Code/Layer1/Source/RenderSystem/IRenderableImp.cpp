#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IGeometryUsageImp::IGeometryUsageImp()
	:mStartIndexLocation(0)
	,mIndexCount(0)
	,mBaseVertexLocation(0)
	,mVertexCount(0)
	,mStartVertexLocation(0)
{
}

NSDevilX::NSRenderSystem::IGeometryUsageImp::~IGeometryUsageImp()
{
}

Void NSDevilX::NSRenderSystem::IGeometryUsageImp::setStartIndexLocation(UInt32 location)
{
	mStartIndexLocation=location;
}

UInt32 NSDevilX::NSRenderSystem::IGeometryUsageImp::getStartIndexLocation() const
{
	return mStartIndexLocation;
}

Void NSDevilX::NSRenderSystem::IGeometryUsageImp::setIndexCount(UInt32 count)
{
	mIndexCount=count;
}

UInt32 NSDevilX::NSRenderSystem::IGeometryUsageImp::getIndexCount() const
{
	return mIndexCount;
}

Void NSDevilX::NSRenderSystem::IGeometryUsageImp::setBaseVertexLocation(UInt32 location)
{
	mBaseVertexLocation=location;
}

UInt32 NSDevilX::NSRenderSystem::IGeometryUsageImp::getBaseVertexLocation() const
{
	return mBaseVertexLocation;
}

Void NSDevilX::NSRenderSystem::IGeometryUsageImp::setVertexCount(UInt32 count)
{
	mVertexCount=count;
}

UInt32 NSDevilX::NSRenderSystem::IGeometryUsageImp::getVertexCount() const
{
	return mVertexCount;
}

Void NSDevilX::NSRenderSystem::IGeometryUsageImp::setStartVertexLocation(UInt32 location)
{
	mStartVertexLocation=location;
}

UInt32 NSDevilX::NSRenderSystem::IGeometryUsageImp::getStartVertexLocation() const
{
	return mStartVertexLocation;
}

NSDevilX::NSRenderSystem::IRenderableImp::IRenderableImp()
	:mGeometry(nullptr)
	,mGeometryUsage(nullptr)
	,mMaterial(nullptr)
{
	mGeometryUsage=DEVILX_NEW IGeometryUsageImp();
}

NSDevilX::NSRenderSystem::IRenderableImp::~IRenderableImp()
{
	DEVILX_DELETE(mGeometryUsage);
}

IGeometryUsage * NSDevilX::NSRenderSystem::IRenderableImp::queryInterface_IGeometryUsage() const
{
	return mGeometryUsage;
}

Void NSDevilX::NSRenderSystem::IRenderableImp::setGeometry(IGeometry * geometry)
{
	mGeometry=static_cast<IGeometryImp*>(geometry);
}

IGeometry * NSDevilX::NSRenderSystem::IRenderableImp::getGeometry() const
{
	return mGeometry;
}

Void NSDevilX::NSRenderSystem::IRenderableImp::setVisible(Bool visible)
{
	mVisible=visible;
}

Bool NSDevilX::NSRenderSystem::IRenderableImp::getVisible() const
{
	return mVisible;
}

Void NSDevilX::NSRenderSystem::IRenderableImp::setMaterial(IMaterial * material)
{
	mMaterial=static_cast<IMaterialImp*>(material);
}

IMaterial * NSDevilX::NSRenderSystem::IRenderableImp::getMaterial() const
{
	return mMaterial;
}
