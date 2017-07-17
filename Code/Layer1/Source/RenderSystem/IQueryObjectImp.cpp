#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IQueryObjectImp::IQueryObjectImp(const String & name,ISceneImp * scene)
	:mSceneElement(nullptr)
	,mGeometryUsage(nullptr)
	,mGeometry(nullptr)
	,mVisible(True)
{
	mSceneElement=DEVILX_NEW ISceneElementImp(name,scene,this,ISceneElementImp::EContainerObjectType_QueryObject);
	mGeometryUsage=DEVILX_NEW IGeometryUsageImp();
}

NSDevilX::NSRenderSystem::IQueryObjectImp::~IQueryObjectImp()
{
	DEVILX_DELETE(mSceneElement);
	DEVILX_DELETE(mGeometryUsage);
}

ISceneElement * NSDevilX::NSRenderSystem::IQueryObjectImp::queryInterface_ISceneElement() const
{
	return mSceneElement;
}

IGeometryUsage * NSDevilX::NSRenderSystem::IQueryObjectImp::queryInterface_IGeometryUsage() const
{
	return mGeometryUsage;
}

Void NSDevilX::NSRenderSystem::IQueryObjectImp::setGeometry(IGeometry * geometry)
{
	if(getGeometry()!=geometry)
	{
		notify(EMessage_BeginGeometryChange);
		mGeometry=static_cast<IGeometryImp*>(geometry);
		notify(EMessage_EndGeometryChange);
	}
}

IGeometry * NSDevilX::NSRenderSystem::IQueryObjectImp::getGeometry() const
{
	return mGeometry;
}

Void NSDevilX::NSRenderSystem::IQueryObjectImp::setVisible(Bool visible)
{
	if(getVisible()!=visible)
	{
		notify(EMessage_BeginVisibleChange);
		mVisible=visible;
		notify(EMessage_EndVisibleChange);
	}
}

Bool NSDevilX::NSRenderSystem::IQueryObjectImp::getVisible() const
{
	return mVisible;
}
