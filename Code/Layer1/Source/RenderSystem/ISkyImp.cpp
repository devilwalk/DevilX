#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::ISkyImp::ISkyImp(const String & name,ISceneImp * scene)
	:mSceneElement(nullptr)
	,mGeometry(nullptr)
	,mVisible(True)
	,mOrder(0)
{
	mSceneElement=DEVILX_NEW ISceneElementImp(name,scene,this,ISceneElementImp::EContainerObjectType_Sky);
}

NSDevilX::NSRenderSystem::ISkyImp::~ISkyImp()
{
	DEVILX_DELETE(mSceneElement);
}

ISceneElement * NSDevilX::NSRenderSystem::ISkyImp::queryInterface_ISceneElement() const
{
	return mSceneElement;
}

Void NSDevilX::NSRenderSystem::ISkyImp::setVisible(Bool visible)
{
	if(visible!=mVisible)
	{
		CMessageNotifier::notify(EMessage_BeginVisibleChange);
		mVisible=visible;
		CMessageNotifier::notify(EMessage_EndVisibleChange);
	}
}

Bool NSDevilX::NSRenderSystem::ISkyImp::getVisible() const
{
	return mVisible;
}

Void NSDevilX::NSRenderSystem::ISkyImp::setGeometry(IGeometry * geometry)
{
	if(geometry!=getGeometry())
	{
		notify(EMessage_BeginGeometryChange,static_cast<IGeometryImp*>(geometry));
		mGeometry=static_cast<IGeometryImp*>(geometry);
		notify(EMessage_EndGeometryChange);
	}
}

IGeometry * NSDevilX::NSRenderSystem::ISkyImp::getGeometry() const
{
	return mGeometry;
}

Void NSDevilX::NSRenderSystem::ISkyImp::setOrder(Int32 order)
{
	mOrder=order;
}

Int32 NSDevilX::NSRenderSystem::ISkyImp::getOrder() const
{
	return mOrder;
}

IColourUnitState * NSDevilX::NSRenderSystem::ISkyImp::getColourUnitState()
{
	if(!mColourUnitState)
	{
		notify(EMessage_BeginColourUnitStateCreate);
		mColourUnitState=DEVILX_NEW IColourUnitStateImp();
		notify(EMessage_EndColourUnitStateCreate);
	}
	return mColourUnitState;
}

ITextureUnitState * NSDevilX::NSRenderSystem::ISkyImp::getTextureUnitState()
{
	if(!mTextureUnitState)
	{
		notify(EMessage_BeginTextureUnitStateCreate);
		mTextureUnitState=DEVILX_NEW ITextureUnitStateImp();
		notify(EMessage_EndTextureUnitStateCreate);
	}
	return mTextureUnitState;
}
