#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CQueryObjectRenderable::CQueryObjectRenderable()
	:mTransformer(nullptr)
	,mGeometry(nullptr)
	,mGeometryUsage(nullptr)
{}

NSDevilX::NSRenderSystem::NSD3D11::CQueryObjectRenderable::~CQueryObjectRenderable()
{
	DEVILX_DELETE(mGeometryUsage);
}

Boolean NSDevilX::NSRenderSystem::NSD3D11::CQueryObjectRenderable::merge(IQueryObjectImp * obj)
{
	auto transformer=CSystemImp::getSingleton().getTransformer(static_cast<ITransformerImp*>(obj->queryInterface_ISceneElement()->getTransformer()));
	auto geo=CSystemImp::getSingleton().getGeometry(static_cast<IGeometryImp*>(obj->getGeometry()));
	if(getGeometryUsage())
	{
		if((getTransformer()==transformer)
			&&(getGeometry()==geo))
		{
			if((getGeometryUsage()->getVertexBufferOffset()==obj->queryInterface_IGeometryUsage()->getVertexBufferOffset())&&(getGeometryUsage()->getVertexCount()==obj->queryInterface_IGeometryUsage()->getVertexCount()))
			{
				if(getGeometryUsage()->getIndexBufferOffset()==obj->queryInterface_IGeometryUsage()->getIndexBufferOffset()+obj->queryInterface_IGeometryUsage()->getIndexCount())
				{
					getGeometryUsage()->setIndexBufferOffset(obj->queryInterface_IGeometryUsage()->getIndexBufferOffset());
					return true;
				}
				else if(getGeometryUsage()->getIndexBufferOffset()+getGeometryUsage()->getIndexCount()==obj->queryInterface_IGeometryUsage()->getIndexBufferOffset())
				{
					getGeometryUsage()->setIndexCount(getGeometryUsage()->getIndexCount()+obj->queryInterface_IGeometryUsage()->getIndexCount());
					return true;
				}
			}
		}
	}
	else
	{
		mGeometryUsage=DEVILX_NEW IGeometryUsageImp();
		getGeometryUsage()->setVertexBufferOffset(obj->queryInterface_IGeometryUsage()->getVertexBufferOffset());
		getGeometryUsage()->setVertexCount(obj->queryInterface_IGeometryUsage()->getVertexCount());
		getGeometryUsage()->setIndexBufferOffset(obj->queryInterface_IGeometryUsage()->getIndexBufferOffset());
		getGeometryUsage()->setIndexCount(obj->queryInterface_IGeometryUsage()->getIndexCount());
		getGeometryUsage()->setOperationType(obj->queryInterface_IGeometryUsage()->getOperationType());
		return true;
	}
}
