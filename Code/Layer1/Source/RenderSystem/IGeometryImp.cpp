#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IVertexBufferUsageImp::IVertexBufferUsageImp(IGeometryImp * geo)
	:mGeometry(geo)
	,mBuffer(nullptr)
	,mUsage(nullptr)
	,mAlignedOffset(0)
	,mStride(0)
	,mSemanticIndex(0)
	,mFormat(IEnum::EVertexElementFormat_Float4)
{
	mUsage=DEVILX_NEW IBufferUsageImp();
}

NSDevilX::NSRenderSystem::IVertexBufferUsageImp::~IVertexBufferUsageImp()
{
	DEVILX_DELETE(mUsage);
}

IBufferUsage * NSDevilX::NSRenderSystem::IVertexBufferUsageImp::queryInterface_IBufferUsage() const
{
	return mUsage;
}

IGeometry * NSDevilX::NSRenderSystem::IVertexBufferUsageImp::getGeometry() const
{
	return mGeometry;
}

Void NSDevilX::NSRenderSystem::IVertexBufferUsageImp::setBuffer(IBuffer * buffer)
{
	mBuffer=static_cast<IBufferImp*>(buffer);
}

IBuffer * NSDevilX::NSRenderSystem::IVertexBufferUsageImp::getBuffer() const
{
	return mBuffer;
}

Void NSDevilX::NSRenderSystem::IVertexBufferUsageImp::setFormat(UInt32 alignedByteOffset,IEnum::EVertexElementFormat format,const String & semanticName,UInt32 semanticIndex=0)
{
	mAlignedOffset=alignedByteOffset;
	mFormat=format;
	mSemanticName=semanticName;
	mSemanticIndex=semanticIndex;
}

NSDevilX::NSRenderSystem::IIndexBufferUsageImp::IIndexBufferUsageImp(IGeometryImp * geo)
	:mGeometry(geo)
	,mBuffer(nullptr)
	,mUsage(nullptr)
	,mFormat(IEnum::EIndexFormat_16)
{
	mUsage=DEVILX_NEW IBufferUsageImp();
}

NSDevilX::NSRenderSystem::IIndexBufferUsageImp::~IIndexBufferUsageImp()
{
	DEVILX_DELETE(mUsage);
}

IBufferUsage * NSDevilX::NSRenderSystem::IIndexBufferUsageImp::queryInterface_IBufferUsage() const
{
	return mUsage;
}

IGeometry * NSDevilX::NSRenderSystem::IIndexBufferUsageImp::getGeometry() const
{
	return mGeometry;
}

Void NSDevilX::NSRenderSystem::IIndexBufferUsageImp::setBuffer(IBuffer * buffer)
{
	mBuffer=static_cast<IBufferImp*>(buffer);
}

IBuffer * NSDevilX::NSRenderSystem::IIndexBufferUsageImp::getBuffer() const
{
	return mBuffer;
}

Void NSDevilX::NSRenderSystem::IIndexBufferUsageImp::setFormat(IEnum::EIndexFormat format)
{
	mFormat=format;
}

NSDevilX::NSRenderSystem::IGeometryImp::IGeometryImp(const String & name)
	:mName(name)
	,mIndexBufferUsage(nullptr)
	,mOperationType(IEnum::EOperationType_TriangleList)
{
	mIndexBufferUsage=DEVILX_NEW IIndexBufferUsageImp(this);
}

NSDevilX::NSRenderSystem::IGeometryImp::~IGeometryImp()
{
	DEVILX_SAFE_DELETE(mIndexBufferUsage);
}

Void NSDevilX::NSRenderSystem::IGeometryImp::setOperationType(IEnum::EOperationType type)
{
	mOperationType=type;
}

IEnum::EOperationType NSDevilX::NSRenderSystem::IGeometryImp::getOperationType() const
{
	return mOperationType;
}

const String & NSDevilX::NSRenderSystem::IGeometryImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

IVertexBufferUsage * NSDevilX::NSRenderSystem::IGeometryImp::getVertexBufferUsage(UInt32 slot)
{
	if(mVertexBufferUsages.size()<=slot)
		mVertexBufferUsages.resize(slot+1);
	if(!mVertexBufferUsages[slot])
		mVertexBufferUsages[slot]=DEVILX_NEW IVertexBufferUsageImp(this);
	return mVertexBufferUsages[slot];
}

IIndexBufferUsage * NSDevilX::NSRenderSystem::IGeometryImp::getIndexBufferUsage()
{
	return mIndexBufferUsage;
}
