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
	mAreas.destroy<CArea>();
	if(mSelfRenderScene)
		NSRenderSystem::getSystem()->destroyScene(getRenderScene());
}

Void NSDevilX::NSCubeBlockSystem::ISceneImp::update()
{
	Bool need_next_process=True;
	for(auto area:mAreas)
	{
		if(!need_next_process)
			break;
		static_cast<CArea*>(area)->update(need_next_process);
	}
}

Void NSDevilX::NSCubeBlockSystem::ISceneImp::setBlock(const CInt3 & position,IBlock * block)
{
	const CInt3 area_pos(CArea::calculateAreaPosition(position));
	auto & area=mAreas[area_pos];
	if(!area)
	{
		area=DEVILX_NEW CArea(area_pos,this);
	}
	static_cast<CArea*>(area)->setBlock(position-static_cast<CArea*>(area)->getPosition()*CArea::sBlockSize,static_cast<IBlockImp*>(block));
}

Void NSDevilX::NSCubeBlockSystem::ISceneImp::setBlock(const CRange3I & range,IBlock * block)
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
				auto & area=mAreas[area_pos];
				if(!area)
				{
					area=DEVILX_NEW CArea(area_pos,this);
				}
				const CRange3I area_range=static_cast<CArea*>(area)->getBlockRange();
				CRange3I::createIntersection(area_range,range,intersection);
				intersection.setMin(intersection.getMin()-area_range.getMin());
				intersection.setMax(intersection.getMax()-area_range.getMin());
				static_cast<CArea*>(area)->setBlock(intersection,static_cast<IBlockImp*>(block));
			}
		}
	}
}

IBlock * NSDevilX::NSCubeBlockSystem::ISceneImp::getBlock(const CInt3 & position) const
{
	const CInt3 area_pos(CArea::calculateAreaPosition(position));
	auto area=static_cast<const CArea*>(mAreas[area_pos]);
	if(area)
	{
		CInt3 block_pos=position-area->getPosition()*CArea::sBlockSize;
		return area->getBlock(block_pos);
	}
	else
	{
		return nullptr;
	}
}