#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchTerrain2D::CMatchTerrain2D(CMatchMap * map)
	:mMap(map)
	,mGeometry(nullptr)
	,mRenderEntity(nullptr)
	,mRenderVisibleArea(nullptr)
	,mRenderableNameGenerator("")
{
	mGeometry=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createGeometry("MatchTerrain2D");
	const auto grid_count=getMap()->getRowCount()*getMap()->getColumeCount();
	mGeometry->getIndexBuffer()->setCount(grid_count*6);
	UInt32 * indics=reinterpret_cast<UInt32*>(DEVILX_ALLOC(sizeof(UInt32)*mGeometry->getIndexBuffer()->getCount()));
	for(auto grid_index=0;grid_index<grid_count;++grid_index)
	{
		indics[0+grid_index*6]=grid_index*4+0;
		indics[1+grid_index*6]=grid_index*4+1;
		indics[2+grid_index*6]=grid_index*4+2;
		indics[3+grid_index*6]=grid_index*4+2;
		indics[4+grid_index*6]=grid_index*4+1;
		indics[5+grid_index*6]=grid_index*4+3;
	}
	mGeometry->getIndexBuffer()->setIndices(indics);
	mGeometry->getVertexBuffer()->setCount(grid_count*4);
	CFloat3 * positions=DEVILX_NEW CFloat3[mGeometry->getVertexBuffer()->getCount()];
	CFloat2 * uvs=DEVILX_NEW CFloat2[mGeometry->getVertexBuffer()->getCount()];
	for(auto grid_x=0;grid_x<getMap()->getColumeCount();++grid_x)
	{
		for(auto grid_y=0;grid_y<getMap()->getRowCount();++grid_y)
		{
			const auto grid_index=grid_x*getMap()->getRowCount()+grid_y;
			positions[grid_index*4+0]=CFloat3(grid_x,grid_y,0.0f);
			uvs[grid_index*4+0]=CFloat2(0.0f,0.0f);
			positions[grid_index*4+1]=CFloat3(grid_x+1.0f,grid_y,0.0f);
			uvs[grid_index*4+1]=CFloat2(1.0f,0.0f);
			positions[grid_index*4+2]=CFloat3(grid_x,grid_y+1.0f,0.0f);
			uvs[grid_index*4+2]=CFloat2(0.0f,1.0f);
			positions[grid_index*4+3]=CFloat3(grid_x+1.0f,grid_y+1.0f,0.0f);
			uvs[grid_index*4+3]=CFloat2(1.0f,1.0f);
		}
	}
	mGeometry->getVertexBuffer()->setPositions(positions);
	mGeometry->getVertexBuffer()->setTextureCoords(uvs);
	mRenderEntity=getMap()->getScene()->getRenderScene()->createEntity("MatchTerrain2D");
	auto renderable=mRenderEntity->createRenderable(mRenderableNameGenerator.generateNext());
	renderable->setGeometry(mGeometry);
	renderable->queryInterface_IGeometryUsage()->setVertexCount(mGeometry->getVertexBuffer()->getCount());
	renderable->queryInterface_IGeometryUsage()->setIndexCount(mGeometry->getIndexBuffer()->getCount());
	mRenderables[CApp::getSingleton().getGame()->getMatchMapGridRenderMaterialManager()->getDefaultMaterial()->getMaterial2D()].push_back(renderable);
	mRenderVisibleArea=getMap()->getScene()->getRenderScene()->createVisibleArea("MatchTerrain2D");
	mRenderVisibleArea->attachObject(mRenderEntity->queryInterface_ISceneElement());
	mRenderVisibleArea->setBoundingBox(DirectX::BoundingBox(CFloat3::sZero,CFloat3(10000.0f)));

	for(UInt16 row=0;row<getMap()->getRowCount();++row)
	{
		for(UInt16 colume=0;colume<getMap()->getColumeCount();++colume)
		{
			auto grid=getMap()->getGrid(row,colume);
			grid->addListener(this,CMatchMapGrid::EMessage_BeginRenderMaterialChange);
			grid->addListener(this,CMatchMapGrid::EMessage_EndRenderMaterialChange);
		}
	}
}

NSDevilX::NSFightChess::CMatchTerrain2D::~CMatchTerrain2D()
{
	DEVILX_FREE(reinterpret_cast<VoidPtr>(reinterpret_cast<SizeT>(mGeometry->getIndexBuffer()->getIndices())));
	DEVILX_DELETE(mGeometry->getVertexBuffer()->getPositions());
	DEVILX_DELETE(mGeometry->getVertexBuffer()->getTextureCoords());
	NSRenderSystem::getSystem()->queryInterface_IResourceManager()->destroyGeometry(mGeometry);
	getMap()->getScene()->getRenderScene()->destroyEntity(mRenderEntity);
	getMap()->getScene()->getRenderScene()->destroyVisibleArea(mRenderVisibleArea);
}

Void NSDevilX::NSFightChess::CMatchTerrain2D::onMessage(CMatchMapGrid * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CMatchMapGrid::EMessage_BeginRenderMaterialChange:
	{
		auto index_start=_calculateIndexStart(notifier->getRowIndex(),notifier->getColumeIndex());
		auto & renderables=mRenderables[notifier->getRenderMaterial()->getMaterial2D()];
		for(auto iter=renderables.begin();renderables.end()!=iter;++iter)
		{
			auto renderable=*iter;
			if((renderable->queryInterface_IGeometryUsage()->getIndexBufferOffset()<=index_start)&&(renderable->queryInterface_IGeometryUsage()->getIndexBufferOffset()+renderable->queryInterface_IGeometryUsage()->getIndexCount()>index_start))
			{
				if(renderable->queryInterface_IGeometryUsage()->getIndexBufferOffset()<index_start)
				{
					auto first_renderable=mRenderEntity->createRenderable(mRenderableNameGenerator.generateNext());
					first_renderable->setGeometry(mGeometry);
					first_renderable->queryInterface_IGeometryUsage()->setVertexCount(mGeometry->getVertexBuffer()->getCount());
					first_renderable->queryInterface_IGeometryUsage()->setIndexBufferOffset(renderable->queryInterface_IGeometryUsage()->getIndexBufferOffset());
					first_renderable->queryInterface_IGeometryUsage()->setIndexCount(index_start-renderable->queryInterface_IGeometryUsage()->getIndexBufferOffset());
					renderables.insert(iter,first_renderable);
				}
				renderable->queryInterface_IGeometryUsage()->setIndexCount(renderable->queryInterface_IGeometryUsage()->getIndexBufferOffset()+renderable->queryInterface_IGeometryUsage()->getIndexCount()-(index_start+6));
				renderable->queryInterface_IGeometryUsage()->setIndexBufferOffset(index_start+6);
				break;
			}
		}
	}
	break;
	case CMatchMapGrid::EMessage_EndRenderMaterialChange:
	{
		Boolean added=false;
		auto index_start=_calculateIndexStart(notifier->getRowIndex(),notifier->getColumeIndex());
		auto & renderables=mRenderables[notifier->getRenderMaterial()->getMaterial2D()];
		for(auto iter=renderables.begin();renderables.end()!=iter;++iter)
		{
			auto renderable=*iter;
			if(renderable->queryInterface_IGeometryUsage()->getIndexBufferOffset()==index_start+6)
			{
				renderable->queryInterface_IGeometryUsage()->setIndexBufferOffset(index_start);
				added=true;
				break;
			}
			else if(renderable->queryInterface_IGeometryUsage()->getIndexBufferOffset()+renderable->queryInterface_IGeometryUsage()->getIndexCount()==index_start)
			{
				renderable->queryInterface_IGeometryUsage()->setIndexCount(renderable->queryInterface_IGeometryUsage()->getIndexCount()+6);
				++iter;
				if(renderables.end()!=iter)
				{
					auto next_renderable=*iter;
					if(renderable->queryInterface_IGeometryUsage()->getIndexBufferOffset()+renderable->queryInterface_IGeometryUsage()->getIndexCount()==next_renderable->queryInterface_IGeometryUsage()->getIndexBufferOffset())
					{
						renderable->queryInterface_IGeometryUsage()->setIndexCount(renderable->queryInterface_IGeometryUsage()->getIndexCount()+next_renderable->queryInterface_IGeometryUsage()->getIndexCount());
						renderables.erase(iter);
						mRenderEntity->destroyRenderable(next_renderable);
					}
				}
				added=true;
				break;
			}
		}
		if(!added)
		{
			auto renderable=mRenderEntity->createRenderable(mRenderableNameGenerator.generateNext());
			renderable->setGeometry(mGeometry);
			renderable->queryInterface_IGeometryUsage()->setVertexCount(mGeometry->getVertexBuffer()->getCount());
			renderable->queryInterface_IGeometryUsage()->setIndexBufferOffset(index_start);
			renderable->queryInterface_IGeometryUsage()->setIndexCount(6);
		}
	}
	break;
	}
}