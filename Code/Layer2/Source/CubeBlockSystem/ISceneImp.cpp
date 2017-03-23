#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockSystem;

NSDevilX::NSCubeBlockSystem::ISceneImp::ISceneImp(NSRenderSystem::IScene * renderScene)
	:mRenderScene(renderScene)
	,mSelfRenderScene(renderScene==nullptr)
{
	if(!mRenderScene)
		mRenderScene=NSRenderSystem::getSystem()->createScene(CStringConverter::toString((SizeT)this),NSRenderSystem::IEnum::ESceneManagerAlgorithm_Simple);
}

NSDevilX::NSCubeBlockSystem::ISceneImp::~ISceneImp()
{
	for(auto x=0;x<2;++x)
	{
		for(auto y=0;y<2;++y)
		{
			for(auto z=0;z<2;++z)
			{
				mAreas[x][y][z].lockWrite();
				for(auto yz:mAreas[x][y][z])
				{
					if(!yz)
						continue;
					yz->lockWrite();
					for(auto z:*yz)
					{
						if(!z)
							continue;
						z->lockWrite();
						for(auto area:*z)
						{
							DEVILX_DELETE(area);
						}
						z->unLockWrite();
						DEVILX_DELETE(z);
					}
					yz->unLockWrite();
					DEVILX_DELETE(yz);
				}
				mAreas[x][y][z].unLockWrite();
			}
		}
	}
	if(mSelfRenderScene)
		NSRenderSystem::getSystem()->destroyScene(getRenderScene());
}

Void NSDevilX::NSCubeBlockSystem::ISceneImp::update()
{
	Bool need_next_process=True;
	for(auto x=0;x<2;++x)
	{
		if(!need_next_process)
			break;
		for(auto y=0;y<2;++y)
		{
			if(!need_next_process)
				break;
			for(auto z=0;z<2;++z)
			{
				if(!need_next_process)
					break;
				mAreas[x][y][z].lockRead();
				for(auto yz:mAreas[x][y][z])
				{
					if(!need_next_process)
						break;
					if(!yz)
						continue;
					yz->lockRead();
					for(auto z:*yz)
					{
						if(!need_next_process)
							break;
						if(!z)
							continue;
						z->lockRead();
						for(auto area:*z)
						{
							if(!need_next_process)
								break;
							if(area)
								area->update(need_next_process);
						}
						z->unLockRead();
					}
					yz->unLockRead();
				}
				mAreas[x][y][z].unLockRead();
			}
		}
	}
}

Void NSDevilX::NSCubeBlockSystem::ISceneImp::setBlockMT(const CInt3 & position,IBlock * block)
{
	const DirectX::XMVECTOR position_vec=position;
	const DirectX::XMVECTOR area_size_vec=CInt3(CArea::sBlockSize);
	const DirectX::XMVECTOR value_offset_vec=CInt3((position.x<0)?-1:0,(position.y<0)?-1:0,(position.z<0)?-1:0);
	const CInt3 value_offset(value_offset_vec);
	const DirectX::XMVECTOR area_pos_vec=(position_vec-value_offset_vec)/area_size_vec+value_offset_vec;
	const DirectX::XMVECTOR area_pos_abs_vec=DirectX::XMVectorAbs(area_pos_vec);
	auto & areas_xyz=mAreas[value_offset.x+1][value_offset.y+1][value_offset.z+1];
	auto area=_createOrRetrieveAreaMT(areas_xyz,area_pos_abs_vec,area_pos_vec);
	area->setBlockMT(position_vec-area_pos_vec*area_size_vec,static_cast<IBlockImp*>(block));
}

Void NSDevilX::NSCubeBlockSystem::ISceneImp::setBlockMT(const CRange3I & range,IBlock * block)
{
	_setBlockToAreaMT(range,static_cast<IBlockImp*>(block));
}

IBlock * NSDevilX::NSCubeBlockSystem::ISceneImp::getBlockMT(const CInt3 & position)
{
	DirectX::XMVECTOR area_size_vec=CInt3(CArea::sBlockSize);
	DirectX::XMVECTOR value_offset_vec=CInt3((position.x<0)?-1:0,(position.y<0)?-1:0,(position.z<0)?-1:0);
	CInt3 value_offset(value_offset_vec);
	const DirectX::XMVECTOR area_pos_vec=position/area_size_vec+value_offset_vec;
	const DirectX::XMVECTOR area_pos_abs_vec=DirectX::XMVectorAbs(area_pos_vec);
	const CInt3 area_pos_abs(area_pos_abs_vec);

	auto & areas_xyz=mAreas[value_offset.x+1][value_offset.y+1][value_offset.z+1];
	areas_xyz.lockRead();
	Boolean has=areas_xyz.size()>static_cast<UInt32>(area_pos_abs.x);
	areas_xyz.unLockRead();
	if(!has)
		return nullptr;
	areas_xyz.lockRead();
	auto areas_yz=areas_xyz[area_pos_abs.x];
	areas_xyz.unLockRead();
	if(!areas_yz)
		return nullptr;
	areas_yz->lockRead();
	has=areas_yz->size()>static_cast<UInt32>(area_pos_abs.y);
	areas_yz->unLockRead();
	if(!has)
		return nullptr;
	areas_yz->lockRead();
	auto areas_z=(*areas_yz)[area_pos_abs.y];
	areas_yz->unLockRead();
	if(!areas_z)
		return nullptr;
	areas_z->lockRead();
	has=areas_z->size()>static_cast<UInt32>(area_pos_abs.z);
	areas_z->unLockRead();
	if(!has)
		return nullptr;
	areas_z->lockRead();
	auto area=(*areas_z)[area_pos_abs.z];
	areas_z->unLockRead();
	if(!area)
		return nullptr;
	return area->getBlockMT(position%area_size_vec);
}

CArea * NSDevilX::NSCubeBlockSystem::ISceneImp::_createOrRetrieveAreaMT(decltype(mAreas[0][0][0]) & areas,DirectX::FXMVECTOR absPositionVec,DirectX::FXMVECTOR positionVec)
{
	const CInt3 area_pos_abs(absPositionVec);

	auto & areas_xyz=areas;
	areas_xyz.lockRead();
	Boolean need_resize=areas_xyz.size()<=static_cast<UInt32>(area_pos_abs.x);
	areas_xyz.unLockRead();
	if(need_resize)
	{
		areas_xyz.lockWrite();
		while(areas_xyz.size()<=static_cast<UInt32>(area_pos_abs.x))
			areas_xyz.push_back(nullptr);
		areas_xyz.unLockWrite();
	}
	areas_xyz.lockRead();
	auto areas_yz=areas_xyz[area_pos_abs.x];
	areas_xyz.unLockRead();
	if(!areas_yz)
	{
		areas_xyz.lockWrite();
		auto & areas_yz_ref=areas_xyz[area_pos_abs.x];
		if(!areas_yz_ref)
		{
			areas_yz_ref=DEVILX_NEW TVectorMT<TVectorMT<CArea*>*>;
			//areas_yz_ref->reserve(1024);
		}
		areas_yz=areas_yz_ref;
		areas_xyz.unLockWrite();
	}

	areas_yz->lockRead();
	need_resize=areas_yz->size()<=static_cast<UInt32>(area_pos_abs.y);
	areas_yz->unLockRead();
	if(need_resize)
	{
		areas_yz->lockWrite();
		while(areas_yz->size()<=static_cast<UInt32>(area_pos_abs.y))
			areas_yz->push_back(nullptr);
		areas_yz->unLockWrite();
	}
	areas_yz->lockRead();
	auto areas_z=(*areas_yz)[area_pos_abs.y];
	areas_yz->unLockRead();
	if(!areas_z)
	{
		areas_yz->lockWrite();
		auto & areas_z_ref=(*areas_yz)[area_pos_abs.y];
		if(!areas_z_ref)
		{
			areas_z_ref=DEVILX_NEW TVectorMT<CArea*>;
			//areas_z_ref->reserve(1024);
		}
		areas_z=areas_z_ref;
		areas_yz->unLockWrite();
	}

	areas_z->lockRead();
	need_resize=areas_z->size()<=static_cast<UInt32>(area_pos_abs.z);
	areas_z->unLockRead();
	if(need_resize)
	{
		areas_z->lockWrite();
		while(areas_z->size()<=static_cast<UInt32>(area_pos_abs.z))
			areas_z->push_back(nullptr);
		areas_z->unLockWrite();
	}
	areas_z->lockRead();
	auto area=(*areas_z)[area_pos_abs.z];
	areas_z->unLockRead();
	if(!area)
	{
		areas_z->lockWrite();
		auto & area_ref=(*areas_z)[area_pos_abs.z];
		if(!area_ref)
			area_ref=DEVILX_NEW CArea(positionVec,this);
		area=area_ref;
		areas_z->unLockWrite();
	}
	return area;
}

Void NSDevilX::NSCubeBlockSystem::ISceneImp::_setBlockToAreaMT(const CRange3I & range,IBlockImp * block)
{
	const DirectX::XMVECTOR block_ranges_min_vec=range.getMin();
	const DirectX::XMVECTOR block_ranges_max_vec=range.getMax();
	const DirectX::XMVECTOR area_size_vec=CInt3(CArea::sBlockSize);
	const CInt3 min_mod=DirectX::XMVectorGreaterOrEqual(block_ranges_min_vec,CInt3::sZero);
	const CInt3 max_mod=DirectX::XMVectorGreaterOrEqual(block_ranges_max_vec,CInt3::sZero);
	const CInt3 min_offset((min_mod.x==0)?-1:0,(min_mod.y==0)?-1:0,(min_mod.z==0)?-1:0);
	const CInt3 max_offset((max_mod.x==0)?-1:0,(max_mod.y==0)?-1:0,(max_mod.z==0)?-1:0);
	const DirectX::XMVECTOR min_offset_vec=min_offset;
	const DirectX::XMVECTOR max_offset_vec=max_offset;
	const CRange3I area_ranges(CInt3((block_ranges_min_vec-min_offset)/area_size_vec)+min_offset,CInt3((block_ranges_max_vec-max_offset)/area_size_vec)+max_offset);
	CRange3I intersection(CInt3::sZero,CInt3::sZero);
	for(auto x=area_ranges.getMin().x;x<=area_ranges.getMax().x;++x)
	{
		for(auto y=area_ranges.getMin().y;y<=area_ranges.getMax().y;++y)
		{
			for(auto z=area_ranges.getMin().z;z<=area_ranges.getMax().z;++z)
			{
				const CInt3 area_pos(x,y,z);
				const DirectX::XMVECTOR area_pos_vec=area_pos;
				const DirectX::XMVECTOR area_pos_abs_vec=DirectX::XMVectorAbs(area_pos_vec);
				CInt3 value_offset((area_pos.x<0)?-1:0,(area_pos.y<0)?-1:0,(area_pos.z<0)?-1:0);
				auto & areas_xyz=mAreas[value_offset.x+1][value_offset.y+1][value_offset.z+1];
				CArea * area=_createOrRetrieveAreaMT(areas_xyz,area_pos_abs_vec,area_pos_vec);
				const CRange3I area_range(area->getPosition()*area_size_vec,area->getPosition()*area_size_vec+area_size_vec-CInt3::sOne);
				CRange3I::createIntersection(area_range,range,intersection);
				intersection.setMin(intersection.getMin()-area_range.getMin());
				intersection.setMax(intersection.getMax()-area_range.getMin());
				area->setBlockMT(intersection,static_cast<IBlockImp*>(block));
			}
		}
	}
}