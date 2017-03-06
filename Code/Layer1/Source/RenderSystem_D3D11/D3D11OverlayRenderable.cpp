#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::COverlayRenderable::COverlayRenderable(COverlayMaterial * material,COverlayManager * manager)
	:mMaterial(material)
	,mManager(manager)
	,mGeometry(nullptr)
{
	mGeometry=CSystemImp::getSingleton().getGeometry(static_cast<IGeometryImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager()->createGeometry("Internal/OverlayRenderable/"+CStringConverter::toString(reinterpret_cast<SizeT>(this)))));
}

NSDevilX::NSRenderSystem::NSD3D11::COverlayRenderable::~COverlayRenderable()
{
	ISystemImp::getSingleton().queryInterface_IResourceManager()->destroyGeometry(mGeometry->getInterfaceImp());
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayRenderable::render(CRenderOperation & ro)
{
	ro.mGeometry=mGeometry;
	ro.mIndexBufferOffset=0;
	ro.mIndexCount=mGeometry->getInterfaceImp()->getIndexBuffer()->getCount();
	ro.mPrimitiveTopology=D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	ro.mVertexBufferOffset=0;
	ro.mVertexCount=mGeometry->getInterfaceImp()->getVertexBuffer()->getCount();
	ro.mPass=mMaterial;
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayRenderable::addElement(IOverlayElementImp * element)
{
	UInt32 index=-1;
	if(mFrees.empty())
	{
		index=static_cast<UInt32>(mPositions.size());
		mPositions.push_back(CFloat3(-1000.0f));
		mPositions.push_back(CFloat3(-1000.0f));
		mPositions.push_back(CFloat3(-1000.0f));
		mPositions.push_back(CFloat3(-1000.0f));
		mUVs.push_back(CFloat2::sZero);
		mUVs.push_back(CFloat2(1.0f,0.0f));
		mUVs.push_back(CFloat2(0.0f,1.0f));
		mUVs.push_back(CFloat2::sOne);
		mDiffuses.push_back(CFloatRGBA::sWhite.rgba8());
		mDiffuses.push_back(CFloatRGBA::sWhite.rgba8());
		mDiffuses.push_back(CFloatRGBA::sWhite.rgba8());
		mDiffuses.push_back(CFloatRGBA::sWhite.rgba8());
		mIndices.push_back(index);
		mIndices.push_back(index+1);
		mIndices.push_back(index+2);
		mIndices.push_back(index+2);
		mIndices.push_back(index+1);
		mIndices.push_back(index+3);
		mGeometry->getInterfaceImp()->getVertexBuffer()->setCount(static_cast<UInt32>(mPositions.size()));
		mGeometry->getInterfaceImp()->getVertexBuffer()->setPositions(&mPositions[0]);
		mGeometry->getInterfaceImp()->getVertexBuffer()->setTextureCoords(&mUVs[0]);
		mGeometry->getInterfaceImp()->getVertexBuffer()->setDiffuses(&mDiffuses[0]);
		mGeometry->getInterfaceImp()->getIndexBuffer()->setCount(static_cast<UInt32>(mIndices.size()));
		mGeometry->getInterfaceImp()->getIndexBuffer()->setIndices(&mIndices[0]);
	}
	else
	{
		index=mFrees.back();
		mFrees.pop_back();
	}
	mRectangles[element]=index;
	_updateElementPosition(element);
	_updateElementTextureCoord(element);
	_updateElementDiffuse(element);
	element->addListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndPositionChange);
	element->addListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndSizeChange);
	element->addListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndUVTransformChange);
	element->addListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndColourUnitStateCreate);
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayRenderable::removeElement(IOverlayElementImp * element)
{
	const auto vertex_start=mRectangles.get(element);
	mPositions[vertex_start]=CFloat3(-1000.0f);
	mPositions[vertex_start+1]=CFloat3(-1000.0f);
	mPositions[vertex_start+2]=CFloat3(-1000.0f);
	mPositions[vertex_start+3]=CFloat3(-1000.0f);
	mGeometry->getInterfaceImp()->getVertexBuffer()->updatePositions(vertex_start,4);
	mFrees.push_back(vertex_start);
	mRectangles.erase(element);
	element->removeListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndPositionChange);
	element->removeListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndSizeChange);
	element->removeListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndUVTransformChange);
	element->removeListener(static_cast<TMessageReceiver<IOverlayElementImp>*>(this),IOverlayElementImp::EMessage_EndColourUnitStateCreate);
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayRenderable::onMessage(IOverlayElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IOverlayElementImp::EMessage_EndPositionChange:
	case IOverlayElementImp::EMessage_EndSizeChange:
		_updateElementPosition(notifier);
	break;
	case IOverlayElementImp::EMessage_EndUVTransformChange:
		_updateElementTextureCoord(notifier);
		break;
	case IOverlayElementImp::EMessage_EndColourUnitStateCreate:
		static_cast<const IOverlayElementImp*>(notifier)->getColourUnitState()->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndEnableChange);
		static_cast<const IOverlayElementImp*>(notifier)->getColourUnitState()->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayRenderable::onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IColourUnitStateImp::EMessage_EndValueChange:
	case IColourUnitStateImp::EMessage_EndEnableChange:
		_updateElementDiffuse(static_cast<IOverlayElementImp*>(notifier->getUserPointer(0)));
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayRenderable::_updateElementPosition(IOverlayElementImp * element)
{
	const auto vertex_start=mRectangles.get(element);
	CFloat2 rel_pos=element->getPosition()*CFloat2(2.0f,-2.0f)-CFloat2(1.0f,-1.0f);
	CFloat2 rel_size=element->getSize()*2.0f;
	mPositions[vertex_start]=CFloat3(rel_pos.x,rel_pos.y,0.5f);
	mPositions[vertex_start+1]=CFloat3(rel_pos.x+rel_size.x,rel_pos.y,0.5f);
	mPositions[vertex_start+2]=CFloat3(rel_pos.x,rel_pos.y-rel_size.y,0.5f);
	mPositions[vertex_start+3]=CFloat3(rel_pos.x+rel_size.x,rel_pos.y-rel_size.y,0.5f);
	mGeometry->getInterfaceImp()->getVertexBuffer()->updatePositions(vertex_start,4);
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayRenderable::_updateElementTextureCoord(IOverlayElementImp * element)
{
	const auto vertex_start=mRectangles.get(element);
	mUVs[vertex_start]=element->getUVOffset();
	mUVs[vertex_start+1]=element->getUVOffset()+CFloat2(element->getUVScale().x,0.0f);
	mUVs[vertex_start+2]=element->getUVOffset()+CFloat2(0.0f,element->getUVScale().x);
	mUVs[vertex_start+3]=element->getUVOffset()+element->getUVScale();
	mGeometry->getInterfaceImp()->getVertexBuffer()->updateTextureCoords(vertex_start,4);
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayRenderable::_updateElementDiffuse(IOverlayElementImp * element)
{
	const auto vertex_start=mRectangles.get(element);
	if(const_cast<const IOverlayElementImp*>(element)->getColourUnitState()
		&&const_cast<const IOverlayElementImp*>(element)->getColourUnitState()->getEnable())
	{
		mDiffuses[vertex_start]=const_cast<const IOverlayElementImp*>(element)->getColourUnitState()->getValue().rgba8();
		mDiffuses[vertex_start+1]=const_cast<const IOverlayElementImp*>(element)->getColourUnitState()->getValue().rgba8();
		mDiffuses[vertex_start+2]=const_cast<const IOverlayElementImp*>(element)->getColourUnitState()->getValue().rgba8();
		mDiffuses[vertex_start+3]=const_cast<const IOverlayElementImp*>(element)->getColourUnitState()->getValue().rgba8();
	}
	else
	{
		mDiffuses[vertex_start]=CFloatRGBA::sWhite.rgba8();
		mDiffuses[vertex_start+1]=CFloatRGBA::sWhite.rgba8();
		mDiffuses[vertex_start+2]=CFloatRGBA::sWhite.rgba8();
		mDiffuses[vertex_start+3]=CFloatRGBA::sWhite.rgba8();
	}
	mGeometry->getInterfaceImp()->getVertexBuffer()->updateDiffuses(vertex_start,4);
}
