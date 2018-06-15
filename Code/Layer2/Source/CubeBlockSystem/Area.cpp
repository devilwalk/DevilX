#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockSystem;

namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		namespace NSInternal
		{
			static Boolean optimizeBlockRange(VoidPtr parameter)
			{
				auto ranges=static_cast<CArea::SBlockRanges*>(parameter);

				return true;
			}
		}
	}
}

NSDevilX::NSCubeBlockSystem::CArea::SRenderable::SRenderable(IRenderMaterialImp * material,CArea * area)
	:mMaterial(material)
	,mArea(area)
	,mRenderable(nullptr)
{
}

NSDevilX::NSCubeBlockSystem::CArea::SRenderable::~SRenderable()
{
	if(mRenderable)
	{
		NSRenderSystem::getSystem()->queryInterface_IResourceManager()->destroyGeometry(mRenderable->getGeometry());
		mArea->getEntity()->destroySubEntity(mRenderable);
	}
}

Void NSDevilX::NSCubeBlockSystem::CArea::SRenderable::initialize()
{
	if(!mRenderable)
	{
		mRenderable=mArea->getEntity()->createSubEntity(CStringConverter::toString(mMaterial));
		mRenderable->setGeometry(NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createGeometry(mArea->getEntity()->queryInterface_ISceneElement()->getName()+"/"+mRenderable->getName()));
		mRenderable->getGeometry()->setVertexBuffer(sGeometry->getVertexBuffer());
		mRenderable->queryInterface_IGeometryUsage()->setVertexCount(sGeometry->getVertexBuffer()->getCount());
		mRenderable->setAmbientModel(NSRenderSystem::IEnum::EMaterialAmbientModel_Constant);
		mRenderable->setDiffuseModel(NSRenderSystem::IEnum::EMaterialDiffuseModel_Lambert);
		mRenderable->setSpecularModel(NSRenderSystem::IEnum::EMaterialSpecularModel_BlinnPhong);
		if(mMaterial)
		{
			mRenderable->getDiffuseColourUnitState()->setValue(mMaterial->getColour());
		}
	}
}

Void NSDevilX::NSCubeBlockSystem::CArea::SRenderable::onMessage(IRenderMaterialImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IRenderMaterialImp::EMessage_EndColourChange:
		mRenderable->getDiffuseColourUnitState()->setValue(mMaterial->getColour());
		break;
	}
}

NSRenderSystem::IGeometry * NSDevilX::NSCubeBlockSystem::CArea::sGeometry=nullptr;
DirectX::XMVECTOR NSDevilX::NSCubeBlockSystem::CArea::calculateAreaPosition(const CInt3 & blockPosition)
{
	const DirectX::XMVECTOR position_vec=blockPosition;
	DirectX::XMVECTOR area_size_vec=CInt3(CArea::sBlockSize);
	DirectX::XMVECTOR value_offset_vec=CInt3((blockPosition.x<0)?-1:0,(blockPosition.y<0)?-1:0,(blockPosition.z<0)?-1:0);
	CInt3 value_offset(value_offset_vec);
	const DirectX::XMVECTOR area_pos_vec=position_vec/area_size_vec+value_offset_vec;
	return area_pos_vec;
}

NSDevilX::NSCubeBlockSystem::CArea::CArea(const CInt3 & position,ISceneImp * scene)
	:mPosition(position)
	,mScene(scene)
	,mEntity(nullptr)
	,mVisibleArea(nullptr)
	,mNeedFillRenderable(false)
	,mNeedUpdateRenderable(false)
{
}

NSDevilX::NSCubeBlockSystem::CArea::~CArea()
{
	mRenderables.lockWrite();
	for(auto const & renderable_pair:mRenderables)
	{
		auto renderable=renderable_pair.second;
		DEVILX_DELETE(renderable);
	}
	mRenderables.clear();
	mRenderables.unLockWrite();
	mScene->getRenderScene()->destroyVisibleArea(mVisibleArea);
	mScene->getRenderScene()->destroyEntity(mEntity);
}

Void NSDevilX::NSCubeBlockSystem::CArea::setBlock(const CInt3 & position,IBlockImp * block)
{
	assert(position>=CInt3::sZero);
	assert(position<CInt3(sBlockSize));
	setBlock(CRange3I(position,position),block);
	if(block)
	{
		auto ranges=_getRangesMT(block);
		ranges->lockWrite();
		Boolean need_merge=true;
		for(auto iter=ranges->begin(),end=ranges->end();end!=iter;++iter)
		{
			auto test=*iter;
			if(test->contains(position))
			{
				need_merge=false;
				break;
			}
		}
		if(need_merge)
		{
			CRange3I merge_range(position,position);
			do
			{
				need_merge=false;
				for(auto iter=ranges->begin(),end=ranges->end();end!=iter;++iter)
				{
					auto test=*iter;
					if(CRange3I::EMergeResult_Success==test->merge(merge_range))
					{
						merge_range.setMin(test->getMin());
						merge_range.setMax(test->getMax());
						DEVILX_DELETE test;
						ranges->erase(iter);
						need_merge=true;
						break;
					}
				}
			}
			while(need_merge);
			ranges->push_back(DEVILX_NEW CRange3I(merge_range));
			mNeedFillRenderable=true;
		}
		ranges->unLockWrite();
	}
	else
	{
		CRange3I * dst_range=nullptr;
		TListMT<CRange3I*> * dst_ranges=nullptr;
		mBlocks.lockRead();
		for(auto const & block_pair:mBlocks)
		{
			auto ranges=block_pair.second;
			ranges->lockWrite();
			for(auto iter=ranges->begin(),end=ranges->end();end!=iter;++iter)
			{
				auto range=*iter;
				if(range->contains(position))
				{
					dst_range=range;
					dst_ranges=ranges;
					ranges->erase(iter);
					break;
				}
			}
			ranges->unLockWrite();
			if(dst_range)
				break;
		}
		mBlocks.unLockRead();
		if(dst_range)
		{
			TList<CRange3I*> new_ranges;
			CRange3I::eraseRange(*dst_range,CRange3I(position,position),new_ranges);
			dst_ranges->lockWrite();
			dst_ranges->insert(dst_ranges->end(),new_ranges.begin(),new_ranges.end());
			mNeedFillRenderable=true;
			dst_ranges->unLockWrite();
		}
	}
}

Void NSDevilX::NSCubeBlockSystem::CArea::setBlock(const CRange3I & range,IBlockImp * block)
{
	assert(range.getMin()>=CInt3::sZero);
	assert(range.getMax()<CInt3(sBlockSize));
	auto & ranges=mBlocks[block];
	if(!ranges)
		ranges=DEVILX_NEW SBlockRanges;
	Boolean can_merge=false;
	ranges->mOptimized.beginRead();
	for(auto test_range:ranges->mRanges)
	{
		if((!test_range->contains(range))&&CRange3I::EMergeResult_Success==test_range->merge(range,nullptr))
		{
			can_merge=true;
			break;
		}
	}
	ranges->mOptimized.endRead();

	auto & ref=ranges->mOptimized.beginWrite();
	ranges->mRanges.push_back(DEVILX_NEW CRange3I(range));
	if(can_merge)
	{
		ref=False;
		ISystemImp::getSingleton().getRenderableThreadPool()->submitMT(NSInternal::optimizeBlockRange,ranges);
	}
	ranges->mOptimized.endWrite();
}

IBlockImp * NSDevilX::NSCubeBlockSystem::CArea::getBlock(const CInt3 & position) const
{
	IBlockImp * ret=nullptr;
	for(auto const & block_pair:mBlocks)
	{
		auto ranges=block_pair.second;
		ranges->mOptimized.beginRead();
		for(auto range:ranges->mRanges)
		{
			if(range->contains(position))
			{
				ret=block_pair.first;
				break;
			}
		}
		ranges->mOptimized.endRead();
		if(ret)
			break;
	}
	return ret;
}

Void NSDevilX::NSCubeBlockSystem::CArea::update(Bool & needNextProcess)
{
	_initialize();
	if(mNeedFillRenderable)
	{
		mNeedFillRenderable=false;
		ISystemImp::getSingleton().getRenderableThreadPool()->submitMT(_fillRenderableThreadFunction,this);
	}
	if(!mNeedUpdateRenderable)
		return;
	if(mRenderables.tryLockRead())
	{
		for(auto const & renderable_pair:mRenderables)
		{
			auto renderable=renderable_pair.second;
			if(renderable->mIndicesFill.empty())
			{
				DEVILX_DELETE renderable;
				mRenderables[renderable_pair.first]=nullptr;
			}
			else
			{
				renderable->initialize();
				if(renderable->mIndicesFill.size()>renderable->mIndices.size())
				{
					renderable->mIndices.resize(renderable->mIndicesFill.size());
					renderable->mRenderable->getGeometry()->getIndexBuffer()->setCount(static_cast<UInt32>(renderable->mIndices.size()));
					renderable->mRenderable->getGeometry()->getIndexBuffer()->setIndices(&renderable->mIndices[0]);
				}
				memcpy(&renderable->mIndices[0],&renderable->mIndicesFill[0],renderable->mIndicesFill.size()*sizeof(renderable->mIndicesFill[0]));
				renderable->mRenderable->getGeometry()->getIndexBuffer()->updateIndices();
				renderable->mRenderable->queryInterface_IGeometryUsage()->setIndexCount(static_cast<UInt32>(renderable->mIndicesFill.size()));
				renderable->mIndicesFill.swap(TVector<UInt32>());
			}
		}
		mNeedUpdateRenderable=false;
		mRenderables.unLockRead();
		needNextProcess=false;
	}
}

static Void fillIndices(Int32 x,Int32 y,Int32 z,IEnum::EBlockFaceType faceType,IBlockImp * block,CArea * area,TMapMT<IRenderMaterialImp*,CArea::SRenderable*> & renderables)
{
	const auto pitch_count=CArea::sBlockSize*CArea::sBlockSize;
	const auto vertex_index=(x*pitch_count+y*CArea::sBlockSize+z)*24;
	auto face=block->getFace(faceType);
	auto & renderable_ref=renderables[static_cast<IRenderMaterialImp*>(face->getRenderMaterial())];
	if(!renderable_ref)
		renderable_ref=DEVILX_NEW CArea::SRenderable(static_cast<IRenderMaterialImp*>(face->getRenderMaterial()),area);
	auto renderable=renderable_ref;
	renderable->mIndicesFill.push_back(vertex_index+faceType*4);
	renderable->mIndicesFill.push_back(vertex_index+faceType*4+1);
	renderable->mIndicesFill.push_back(vertex_index+faceType*4+2);
	renderable->mIndicesFill.push_back(vertex_index+faceType*4+2);
	renderable->mIndicesFill.push_back(vertex_index+faceType*4+1);
	renderable->mIndicesFill.push_back(vertex_index+faceType*4+3);
}

Boolean NSDevilX::NSCubeBlockSystem::CArea::_fillRenderableThreadFunction(VoidPtr parameter)
{
	CArea * const area=static_cast<CArea*>(parameter);
	area->mRenderables.lockWrite();
	for(auto const & renderable_pair:area->mRenderables)
	{
		auto renderable=renderable_pair.second;
		if(renderable)
			renderable->mIndicesFill.clear();
	}
	TMap<IBlockImp*,TList<CRange3I*>*> blocks;
	area->mBlocks.lockRead();
	for(auto const & block_pair:area->mBlocks)
	{
		auto & ranges_to=blocks[block_pair.first];
		ranges_to=DEVILX_NEW TList<CRange3I*>;
		auto & ranges_from=*block_pair.second;
		ranges_from.lockRead();
		for(auto range:ranges_from)
			ranges_to->push_back(DEVILX_NEW CRange3I(*range));
		ranges_from.unLockRead();
	}
	area->mBlocks.unLockRead();
	for(auto const & block_pair:blocks)
	{
		auto block=block_pair.first;
		auto const & ranges=*block_pair.second;
		for(auto range:ranges)
		{
			//±éÀú±íÃæ·½¿é
			//top
			for(auto x=range->getMin().x;x<=range->getMax().x;++x)
			{
				for(auto z=range->getMin().z;z<=range->getMax().z;++z)
				{
					auto y=range->getMax().y;
					//²âÊÔtopÊÇ·ñÕÚµ²
					DirectX::XMVECTOR block_pos=CInt3(x,y+1,z);
					if(y==sBlockSize-1)
					{
						//if(nullptr!=area->getScene()->getBlockMT(area->_getPositionInScene(block_pos)))
						//{
						//	continue;
						//}
					}
					else
					{
						if(nullptr!=area->getBlockMT(block_pos))
						{
							continue;
						}
					}
					fillIndices(x,y,z,IEnum::EBlockFaceType_Positive_Y,block,area,area->mRenderables);
				}
			}
			//bottom
			for(auto x=range->getMin().x;x<=range->getMax().x;++x)
			{
				for(auto z=range->getMin().z;z<=range->getMax().z;++z)
				{
					auto y=range->getMin().y;
					//²âÊÔbottomÊÇ·ñÕÚµ²
					DirectX::XMVECTOR block_pos=CInt3(x,y-1,z);
					if(y==0)
					{
						//if(nullptr!=area->getScene()->getBlockMT(area->_getPositionInScene(block_pos)))
						//{
						//	continue;
						//}
					}
					else
					{
						if(nullptr!=area->getBlockMT(block_pos))
						{
							continue;
						}
					}
					fillIndices(x,y,z,IEnum::EBlockFaceType_Negative_Y,block,area,area->mRenderables);
				}
			}
			//left
			for(auto y=range->getMin().y;y<=range->getMax().y;++y)
			{
				for(auto z=range->getMin().z;z<=range->getMax().z;++z)
				{
					auto x=range->getMin().x;
					//²âÊÔleftÊÇ·ñÕÚµ²
					DirectX::XMVECTOR block_pos=CInt3(x-1,y,z);
					if(x==0)
					{
						//if(nullptr!=area->getScene()->getBlockMT(area->_getPositionInScene(block_pos)))
						//{
						//	continue;
						//}
					}
					else
					{
						if(nullptr!=area->getBlockMT(block_pos))
						{
							continue;
						}
					}
					fillIndices(x,y,z,IEnum::EBlockFaceType_Negative_X,block,area,area->mRenderables);
				}
			}
			//right
			for(auto y=range->getMin().y;y<=range->getMax().y;++y)
			{
				for(auto z=range->getMin().z;z<=range->getMax().z;++z)
				{
					auto x=range->getMax().x;
					DirectX::XMVECTOR block_pos=CInt3(x+1,y,z);
					if(x==sBlockSize-1)
					{
						//if(nullptr!=area->getScene()->getBlockMT(area->_getPositionInScene(block_pos)))
						//{
						//	continue;
						//}
					}
					else
					{
						if(nullptr!=area->getBlockMT(block_pos))
						{
							continue;
						}
					}
					fillIndices(x,y,z,IEnum::EBlockFaceType_Positive_X,block,area,area->mRenderables);
				}
			}
			//front
			for(auto x=range->getMin().x;x<=range->getMax().x;++x)
			{
				for(auto y=range->getMin().y;y<=range->getMax().y;++y)
				{
					auto z=range->getMin().z;
					DirectX::XMVECTOR block_pos=CInt3(x,y,z-1);
					if(z==0)
					{
						//if(nullptr!=area->getScene()->getBlockMT(area->_getPositionInScene(block_pos)))
						//{
						//	continue;
						//}
					}
					else
					{
						if(nullptr!=area->getBlockMT(block_pos))
						{
							continue;
						}
					}
					fillIndices(x,y,z,IEnum::EBlockFaceType_Negative_Z,block,area,area->mRenderables);
				}
			}
			//back
			for(auto x=range->getMin().x;x<=range->getMax().x;++x)
			{
				for(auto y=range->getMin().y;y<=range->getMax().y;++y)
				{
					auto z=range->getMax().z;
					DirectX::XMVECTOR block_pos=CInt3(x,y,z+1);
					if(z==sBlockSize-1)
					{
						//if(nullptr!=area->getScene()->getBlockMT(area->_getPositionInScene(block_pos)))
						//{
						//	continue;
						//}
					}
					else
					{
						if(nullptr!=area->getBlockMT(block_pos))
						{
							continue;
						}
					}
					fillIndices(x,y,z,IEnum::EBlockFaceType_Positive_Z,block,area,area->mRenderables);
				}
			}
			DEVILX_DELETE(range);
		}
		DEVILX_DELETE(&ranges);
	}
	area->mNeedUpdateRenderable=true;
	area->mRenderables.unLockWrite();
	return true;
}

Void NSDevilX::NSCubeBlockSystem::CArea::_initialize()
{
	if(!sGeometry)
	{
		sGeometry=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createGeometry("CubeSystem/Geometry");
		sGeometry->getVertexBuffer()->setCount(24*sBlockSize*sBlockSize*sBlockSize);
		const auto pitch_count=sBlockSize*sBlockSize;
		auto positions=new CFloat3[sGeometry->getVertexBuffer()->getCount()];
		auto normals=new CFloat3[sGeometry->getVertexBuffer()->getCount()];
		auto texture_coords=new CFloat2[sGeometry->getVertexBuffer()->getCount()];
		for(auto block_index_x=0;block_index_x<sBlockSize;++block_index_x)
		{
			for(auto block_index_y=0;block_index_y<sBlockSize;++block_index_y)
			{
				for(auto block_index_z=0;block_index_z<sBlockSize;++block_index_z)
				{
					const auto vertex_index=(block_index_x*pitch_count+block_index_y*sBlockSize+block_index_z)*24;
					//right
					positions[vertex_index+0]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z));
					positions[vertex_index+1]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z+1));
					positions[vertex_index+2]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z));
					positions[vertex_index+3]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z+1));
					normals[vertex_index+0]=CFloat3::sUnitX;
					normals[vertex_index+1]=CFloat3::sUnitX;
					normals[vertex_index+2]=CFloat3::sUnitX;
					normals[vertex_index+3]=CFloat3::sUnitX;
					//left
					positions[vertex_index+4]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z+1));
					positions[vertex_index+5]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z));
					positions[vertex_index+6]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z+1));
					positions[vertex_index+7]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z));
					normals[vertex_index+4]=-CFloat3::sUnitX;
					normals[vertex_index+5]=-CFloat3::sUnitX;
					normals[vertex_index+6]=-CFloat3::sUnitX;
					normals[vertex_index+7]=-CFloat3::sUnitX;
					//top
					positions[vertex_index+8]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z+1));
					positions[vertex_index+9]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z+1));
					positions[vertex_index+10]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z));
					positions[vertex_index+11]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z));
					normals[vertex_index+8]=CFloat3::sUnitY;
					normals[vertex_index+9]=CFloat3::sUnitY;
					normals[vertex_index+10]=CFloat3::sUnitY;
					normals[vertex_index+11]=CFloat3::sUnitY;
					//bottom
					positions[vertex_index+12]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z));
					positions[vertex_index+13]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z));
					positions[vertex_index+14]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z+1));
					positions[vertex_index+15]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z+1));
					normals[vertex_index+12]=-CFloat3::sUnitY;
					normals[vertex_index+13]=-CFloat3::sUnitY;
					normals[vertex_index+14]=-CFloat3::sUnitY;
					normals[vertex_index+15]=-CFloat3::sUnitY;
					//back
					positions[vertex_index+16]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z+1));
					positions[vertex_index+17]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z+1));
					positions[vertex_index+18]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z+1));
					positions[vertex_index+19]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z+1));
					normals[vertex_index+16]=CFloat3::sUnitZ;
					normals[vertex_index+17]=CFloat3::sUnitZ;
					normals[vertex_index+18]=CFloat3::sUnitZ;
					normals[vertex_index+19]=CFloat3::sUnitZ;
					//front
					positions[vertex_index+20]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z));
					positions[vertex_index+21]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y+1),static_cast<Float>(block_index_z));
					positions[vertex_index+22]=CFloat3(static_cast<Float>(block_index_x),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z));
					positions[vertex_index+23]=CFloat3(static_cast<Float>(block_index_x+1),static_cast<Float>(block_index_y),static_cast<Float>(block_index_z));
					normals[vertex_index+20]=-CFloat3::sUnitZ;
					normals[vertex_index+21]=-CFloat3::sUnitZ;
					normals[vertex_index+22]=-CFloat3::sUnitZ;
					normals[vertex_index+23]=-CFloat3::sUnitZ;

					for(auto i=0;i<6;++i)
					{
						texture_coords[vertex_index+i*4+0]=CFloat2(0.0f,0.0f);
						texture_coords[vertex_index+i*4+1]=CFloat2(1.0f,0.0f);
						texture_coords[vertex_index+i*4+2]=CFloat2(0.0f,1.0f);
						texture_coords[vertex_index+i*4+3]=CFloat2(1.0f,1.0f);
					}
				}
			}
		}
		sGeometry->getVertexBuffer()->setPositions(positions);
		sGeometry->getVertexBuffer()->setNormals(normals);
		sGeometry->getVertexBuffer()->setTextureCoords(texture_coords);
	}
	if(!mEntity)
	{
		mEntity=mScene->getRenderScene()->createEntity("Cube/Area/"+CStringConverter::toString(mPosition.x)+"_"+CStringConverter::toString(mPosition.y)+"_"+CStringConverter::toString(mPosition.z));
		mEntity->queryInterface_ISceneElement()->getTransformer()->setPosition(CFloat3(static_cast<Float>(mPosition.x),static_cast<Float>(mPosition.y),static_cast<Float>(mPosition.z))*32.0f);
		mVisibleArea=mScene->getRenderScene()->createVisibleArea(mEntity->queryInterface_ISceneElement()->getName());
		mVisibleArea->attachObject(mEntity->queryInterface_ISceneElement());
		mVisibleArea->setBoundingBox(DirectX::BoundingBox(CFloat3(16.0f,16.0f,16.0f),CFloat3(16.5f,16.5f,16.5f)));
		mVisibleArea->setTransformer(mEntity->queryInterface_ISceneElement()->getTransformer());
	}
}

decltype(CArea::mBlocks)::value_type::second_type NSDevilX::NSCubeBlockSystem::CArea::_getRangesMT(IBlockImp * block)
{
	decltype(CArea::mBlocks)::value_type::second_type ret=nullptr;
	mBlocks.lockRead();
	auto has=mBlocks.has(block);
	mBlocks.unLockRead();
	if(!has)
	{
		mBlocks.lockWrite();
		has=mBlocks.has(block);
		if(!has)
			mBlocks.add(block,DEVILX_NEW TListMT<CRange3I*>);
		mBlocks.unLockWrite();
	}
	mBlocks.lockRead();
	ret=mBlocks.get(block);
	mBlocks.unLockRead();
	return ret;
}

DirectX::XMVECTOR NSDevilX::NSCubeBlockSystem::CArea::_getPositionInScene(DirectX::FXMVECTOR position) const
{
	return getPosition()*sBlockSize+position;
}
