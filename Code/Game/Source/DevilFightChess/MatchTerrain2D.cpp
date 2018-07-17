#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CMatchTerrain2D::CMatchTerrain2D(CMatchMap * map)
	:mMap(map)
	,mGeometry(nullptr)
	,mRenderEntity(nullptr)
	,mRenderVisibleArea(nullptr)
	,mQueryBuffer(nullptr)
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
	UInt32 * query_datas=reinterpret_cast<UInt32*>(DEVILX_ALLOC(sizeof(UInt32)*mGeometry->getVertexBuffer()->getCount()));
	for(auto grid_x=0;grid_x<getMap()->getColumeCount();++grid_x)
	{
		for(auto grid_y=0;grid_y<getMap()->getRowCount();++grid_y)
		{
			const auto grid_index=grid_x*getMap()->getRowCount()+grid_y;
			positions[grid_index*4+0]=CFloat3(static_cast<Float>(grid_x),static_cast<Float>(grid_y),0.0f);
			uvs[grid_index*4+0]=CFloat2(0.0f,0.0f);
			positions[grid_index*4+1]=CFloat3(static_cast<Float>(grid_x)+1.0f,static_cast<Float>(grid_y),0.0f);
			uvs[grid_index*4+1]=CFloat2(1.0f,0.0f);
			positions[grid_index*4+2]=CFloat3(static_cast<Float>(grid_x),static_cast<Float>(grid_y)+1.0f,0.0f);
			uvs[grid_index*4+2]=CFloat2(0.0f,1.0f);
			positions[grid_index*4+3]=CFloat3(static_cast<Float>(grid_x)+1.0f,static_cast<Float>(grid_y)+1.0f,0.0f);
			uvs[grid_index*4+3]=CFloat2(1.0f,1.0f);

			query_datas[grid_index*4+0]=grid_index;
			query_datas[grid_index*4+1]=grid_index;
			query_datas[grid_index*4+2]=grid_index;
			query_datas[grid_index*4+3]=grid_index;
		}
	}
	mGeometry->getVertexBuffer()->setPositions(positions);
	mGeometry->getVertexBuffer()->setTextureCoords(uvs);
	mQueryBuffer=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createBuffer("MatchTerrain2D/Query");
	mQueryBuffer->setSize(grid_count*4);
	mQueryBuffer->setDatas(query_datas);
	mRenderEntity=getMap()->getScene()->getRenderScene()->createEntity("MatchTerrain2D");
	auto query_sub_entity=mRenderEntity->createSubEntity("Query");
	query_sub_entity->setGeometry(mGeometry);
	query_sub_entity->setQueriable(True);
	query_sub_entity->setRenderable(False);
	query_sub_entity->queryInterface_IGeometryUsage()->setVertexCount(mGeometry->getVertexBuffer()->getCount());
	query_sub_entity->queryInterface_IGeometryUsage()->setIndexCount(mGeometry->getIndexBuffer()->getCount());
	auto sub_entity=mRenderEntity->createSubEntity(mRenderableNameGenerator.generateNext());
	sub_entity->setGeometry(mGeometry);
	sub_entity->queryInterface_IGeometryUsage()->setVertexCount(mGeometry->getVertexBuffer()->getCount());
	sub_entity->queryInterface_IGeometryUsage()->setIndexCount(mGeometry->getIndexBuffer()->getCount());
	mSubEntities[CApp::getSingleton().getGame()->getMatchMapGridRenderMaterialManager()->getDefaultMaterial()->getMaterial2D()].push_back(sub_entity);
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
	DEVILX_FREE(reinterpret_cast<VoidPtr>(reinterpret_cast<SizeT>(mQueryBuffer->getDatas())));
	DEVILX_FREE(reinterpret_cast<VoidPtr>(reinterpret_cast<SizeT>(mGeometry->getIndexBuffer()->getIndices())));
	DEVILX_DELETE(mGeometry->getVertexBuffer()->getPositions());
	DEVILX_DELETE(mGeometry->getVertexBuffer()->getTextureCoords());
	NSRenderSystem::getSystem()->queryInterface_IResourceManager()->destroyGeometry(mGeometry);
	NSRenderSystem::getSystem()->queryInterface_IResourceManager()->destroyBuffer(mQueryBuffer);
	getMap()->getScene()->getRenderScene()->destroyEntity(mRenderEntity);
	getMap()->getScene()->getRenderScene()->destroyVisibleArea(mRenderVisibleArea);
}

UInt32 NSDevilX::NSFightChess::CMatchTerrain2D::_calculateIndexStart(UInt16 rowIndex,UInt16 columnIndex) const
{
	const auto grid_index=columnIndex*getMap()->getRowCount()+rowIndex;
	return grid_index*6;
}

Void NSDevilX::NSFightChess::CMatchTerrain2D::onMessage(CMatchTerrain2DChunk * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CMatchMapGrid::EMessage_BeginRenderMaterialChange:
	{
		auto index_start=_calculateIndexStart(notifier->getRowIndex(),notifier->getColumeIndex());
		auto & sub_entities=mSubEntities[notifier->getRenderMaterial()->getMaterial2D()];
		for(auto iter=sub_entities.begin();sub_entities.end()!=iter;++iter)
		{
			auto sub_entity=*iter;
			if((sub_entity->queryInterface_IGeometryUsage()->getIndexBufferOffset()<=index_start)&&(sub_entity->queryInterface_IGeometryUsage()->getIndexBufferOffset()+sub_entity->queryInterface_IGeometryUsage()->getIndexCount()>index_start))
			{
				if(sub_entity->queryInterface_IGeometryUsage()->getIndexBufferOffset()<index_start)
				{
					auto first_sub_entity=mRenderEntity->createSubEntity(mRenderableNameGenerator.generateNext());
					first_sub_entity->setGeometry(mGeometry);
					first_sub_entity->queryInterface_IGeometryUsage()->setVertexCount(mGeometry->getVertexBuffer()->getCount());
					first_sub_entity->queryInterface_IGeometryUsage()->setIndexBufferOffset(sub_entity->queryInterface_IGeometryUsage()->getIndexBufferOffset());
					first_sub_entity->queryInterface_IGeometryUsage()->setIndexCount(index_start-sub_entity->queryInterface_IGeometryUsage()->getIndexBufferOffset());
					sub_entities.insert(iter,first_sub_entity);
				}
				sub_entity->queryInterface_IGeometryUsage()->setIndexCount(sub_entity->queryInterface_IGeometryUsage()->getIndexBufferOffset()+sub_entity->queryInterface_IGeometryUsage()->getIndexCount()-(index_start+6));
				sub_entity->queryInterface_IGeometryUsage()->setIndexBufferOffset(index_start+6);
				break;
			}
		}
	}
	break;
	case CMatchMapGrid::EMessage_EndRenderMaterialChange:
	{
		Boolean added=false;
		auto index_start=_calculateIndexStart(notifier->getRowIndex(),notifier->getColumeIndex());
		auto & sub_entities=mSubEntities[notifier->getRenderMaterial()->getMaterial2D()];
		for(auto iter=sub_entities.begin();sub_entities.end()!=iter;++iter)
		{
			auto sub_entity=*iter;
			if(sub_entity->queryInterface_IGeometryUsage()->getIndexBufferOffset()==index_start+6)
			{
				sub_entity->queryInterface_IGeometryUsage()->setIndexBufferOffset(index_start);
				added=true;
				break;
			}
			else if(sub_entity->queryInterface_IGeometryUsage()->getIndexBufferOffset()+sub_entity->queryInterface_IGeometryUsage()->getIndexCount()==index_start)
			{
				sub_entity->queryInterface_IGeometryUsage()->setIndexCount(sub_entity->queryInterface_IGeometryUsage()->getIndexCount()+6);
				++iter;
				if(sub_entities.end()!=iter)
				{
					auto next_sub_entity=*iter;
					if(sub_entity->queryInterface_IGeometryUsage()->getIndexBufferOffset()+sub_entity->queryInterface_IGeometryUsage()->getIndexCount()==next_sub_entity->queryInterface_IGeometryUsage()->getIndexBufferOffset())
					{
						sub_entity->queryInterface_IGeometryUsage()->setIndexCount(sub_entity->queryInterface_IGeometryUsage()->getIndexCount()+next_sub_entity->queryInterface_IGeometryUsage()->getIndexCount());
						sub_entities.erase(iter);
						mRenderEntity->destroySubEntity(next_sub_entity);
					}
				}
				added=true;
				break;
			}
		}
		if(!added)
		{
			auto sub_entity=mRenderEntity->createSubEntity(mRenderableNameGenerator.generateNext());
			sub_entity->setGeometry(mGeometry);
			sub_entity->queryInterface_IGeometryUsage()->setVertexCount(mGeometry->getVertexBuffer()->getCount());
			sub_entity->queryInterface_IGeometryUsage()->setIndexBufferOffset(index_start);
			sub_entity->queryInterface_IGeometryUsage()->setIndexCount(6);
		}
	}
	break;
	}
}
