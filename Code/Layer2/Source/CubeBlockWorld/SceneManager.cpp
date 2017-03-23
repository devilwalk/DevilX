#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockWorld;
const CUInt3 NSDevilX::NSCubeBlockWorld::CSceneManager::sChunkSize(32);
NSDevilX::NSCubeBlockWorld::CSceneManager::CSceneManager(const String & name,ITerrainGenerator * generator,NSRenderSystem::IScene * renderScene)
	:mName(name)
	,mRenderScene(renderScene)
	,mBlockScene(nullptr)
	,mRange(CInt3(INT_MIN),CInt3(INT_MAX))
{
	mTerrainGeneratorInstance=generator->createInstance(this);
	mBlockScene=NSCubeBlockSystem::getSystem()->createScene(mRenderScene);
}

NSDevilX::NSCubeBlockWorld::CSceneManager::~CSceneManager()
{}

Void NSDevilX::NSCubeBlockWorld::CSceneManager::update()
{
	for(auto const & loader:mLoaders)
		loader.second->update();
}

Void NSDevilX::NSCubeBlockWorld::CSceneManager::loadChunkMT(DirectX::FXMVECTOR positionVec)
{
	const DirectX::XMVECTOR chunk_size_vec=getChunkSize();
	auto loaded=_getChunkLoaded(positionVec);
	if(!loaded)
		return;
	auto & loaded_count=loaded->beginWrite();
	if(0==loaded_count)
	{
		if(!getTerrainGenerator()->generateChunk(positionVec))
		{
			CInt3 start=DirectX::XMVectorMin(positionVec*chunk_size_vec,getRange().getMax());
			CInt3 end=DirectX::XMVectorMax(start+chunk_size_vec-CInt3::sOne,getRange().getMin());
			for(auto x=start.x;x<=end.x;++x)
			{
				for(auto y=start.y;y<=end.y;++y)
				{
					for(auto z=start.z;z<=end.z;++z)
					{
						DirectX::XMVECTOR block_pos_vec=CInt3(x,y,z);
						auto block=getTerrainGenerator()->generateBlock(block_pos_vec);
						if(block)
							getScene()->setBlockMT(block_pos_vec,block);
					}
				}
			}
		}
	}
	++loaded_count;
	loaded->endWrite();
}

Void NSDevilX::NSCubeBlockWorld::CSceneManager::unloadChunkMT(DirectX::FXMVECTOR positionVec)
{
	const DirectX::XMVECTOR chunk_size_vec=getChunkSize();
	auto loaded=_getChunkLoaded(positionVec);
	if(!loaded)
		return;
	auto & loaded_count=loaded->beginWrite();
	--loaded_count;
	if(0==loaded_count)
	{
		CInt3 start=DirectX::XMVectorMin(positionVec*chunk_size_vec,getRange().getMax());
		CInt3 end=DirectX::XMVectorMax(start+chunk_size_vec-CInt3::sOne,getRange().getMin());
		getScene()->setBlockMT(CRange3I(start,end),nullptr);
	}
	loaded->endWrite();
}

ITerrainGeneratorInstance * NSDevilX::NSCubeBlockWorld::CSceneManager::getTerrainGenerator() const
{
	return mTerrainGeneratorInstance;
}

const CUInt3 & NSDevilX::NSCubeBlockWorld::CSceneManager::getChunkSize() const
{
	// TODO: insert return statement here
	return sChunkSize;
}

NSCubeBlockSystem::IScene * NSDevilX::NSCubeBlockWorld::CSceneManager::getScene() const
{
	return mBlockScene;
}

ISceneLoader * NSDevilX::NSCubeBlockWorld::CSceneManager::createLoader(const String & name)
{
	if(getLoader(name))
		return nullptr;
	auto ret=DEVILX_NEW CSceneLoader(name,this);
	mLoaders.add(name,ret);
	return ret;
}

ISceneLoader * NSDevilX::NSCubeBlockWorld::CSceneManager::getLoader(const String & name) const
{
	return mLoaders.get(name);
}

Void NSDevilX::NSCubeBlockWorld::CSceneManager::destroyLoader(ISceneLoader * loader)
{
	mLoaders.destroy(loader->getName());
}

Void NSDevilX::NSCubeBlockWorld::CSceneManager::setRange(const CRange3I & range)
{
	assert(range.isValidate());
	mRange=range;
}

const CRange3I & NSDevilX::NSCubeBlockWorld::CSceneManager::getRange() const
{
	// TODO: insert return statement here
	return mRange;
}

TSharedReadData<Int32>* NSDevilX::NSCubeBlockWorld::CSceneManager::_getChunkLoaded(DirectX::FXMVECTOR positionVec)
{
	const CInt3 chunk_pos(positionVec);
	const DirectX::XMVECTOR block_pos_vec=positionVec*getChunkSize();
	if(!getRange().contains(block_pos_vec))
		return nullptr;
	const DirectX::XMVECTOR chunk_size_vec=getChunkSize();
	const DirectX::XMVECTOR value_offset_vec=CInt3((chunk_pos.x<0)?-1:0,(chunk_pos.y<0)?-1:0,(chunk_pos.z<0)?-1:0);
	const CInt3 value_offset(value_offset_vec);
	const DirectX::XMVECTOR chunk_pos_abs_vec=DirectX::XMVectorAbs(positionVec);
	const CInt3 chunk_pos_abs(chunk_pos_abs_vec);
	auto & chunk_loaded_xyz=mChunkLoadeds[value_offset.x+1][value_offset.y+1][value_offset.z+1];
	chunk_loaded_xyz.lockRead();
	Boolean need_resize=chunk_loaded_xyz.size()<=static_cast<UInt32>(chunk_pos_abs.x);
	chunk_loaded_xyz.unLockRead();
	if(need_resize)
	{
		chunk_loaded_xyz.lockWrite();
		while(chunk_loaded_xyz.size()<=static_cast<UInt32>(chunk_pos_abs.x))
			chunk_loaded_xyz.push_back(nullptr);
		chunk_loaded_xyz.unLockWrite();
	}
	chunk_loaded_xyz.lockRead();
	auto chunk_yz=chunk_loaded_xyz[chunk_pos_abs.x];
	chunk_loaded_xyz.unLockRead();
	if(!chunk_yz)
	{
		chunk_loaded_xyz.lockWrite();
		auto & chunk_yz_ref=chunk_loaded_xyz[chunk_pos_abs.x];
		if(!chunk_yz_ref)
		{
			chunk_yz_ref=DEVILX_NEW TVectorMT<TVectorMT<TSharedReadData<Int32>*>*>;
		}
		chunk_yz=chunk_yz_ref;
		chunk_loaded_xyz.unLockWrite();
	}

	chunk_yz->lockRead();
	need_resize=chunk_yz->size()<=static_cast<UInt32>(chunk_pos_abs.y);
	chunk_yz->unLockRead();
	if(need_resize)
	{
		chunk_yz->lockWrite();
		while(chunk_yz->size()<=static_cast<UInt32>(chunk_pos_abs.y))
			chunk_yz->push_back(nullptr);
		chunk_yz->unLockWrite();
	}
	chunk_yz->lockRead();
	auto chunk_z=(*chunk_yz)[chunk_pos_abs.y];
	chunk_yz->unLockRead();
	if(!chunk_z)
	{
		chunk_yz->lockWrite();
		auto & chunk_z_ref=(*chunk_yz)[chunk_pos_abs.y];
		if(!chunk_z_ref)
		{
			chunk_z_ref=DEVILX_NEW TVectorMT<TSharedReadData<Int32>*>;
		}
		chunk_z=chunk_z_ref;
		chunk_yz->unLockWrite();
	}

	chunk_z->lockRead();
	need_resize=chunk_z->size()<=static_cast<UInt32>(chunk_pos_abs.z);
	chunk_z->unLockRead();
	if(need_resize)
	{
		chunk_z->lockWrite();
		while(chunk_z->size()<=static_cast<UInt32>(chunk_pos_abs.z))
			chunk_z->push_back(nullptr);
		chunk_z->unLockWrite();
	}
	chunk_z->lockRead();
	auto loaded=(*chunk_z)[chunk_pos_abs.z];
	chunk_z->unLockRead();
	if(!loaded)
	{
		chunk_z->lockWrite();
		auto & loaded_ref=(*chunk_z)[chunk_pos_abs.z];
		if(!loaded_ref)
		{
			loaded_ref=DEVILX_NEW TSharedReadData<Int32>(0);
		}
		loaded=loaded_ref;
		chunk_z->unLockWrite();
	}
	return loaded;
}
