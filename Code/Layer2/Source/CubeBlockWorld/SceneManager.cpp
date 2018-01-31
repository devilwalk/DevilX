#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockWorld;
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		namespace NSInternal
		{
			static Void loadFunc(CSceneManager * sm,const CInt3 & position,CSceneManager::SChunkState * state)
			{
				TVector<CInt3> block_positions;
				auto num_pos=sm->getTerrainGenerator()->generateChunkMT(position,nullptr);
				if(num_pos)
				{
					block_positions.resize(num_pos);
					sm->getTerrainGenerator()->generateChunkMT(position,&block_positions[0]);
					TMap<NSCubeBlockSystem::IBlock*,TVector<CInt3> > temp;
					for(auto const & position:block_positions)
					{
						auto block=sm->getTerrainGenerator()->generateBlockMT(position);
						if(block)
						{
							temp[block].push_back(position);
						}
					}
					for(auto const & pair:temp)
					{
						auto & loads=state->mPreLoads[pair.first];
						CRange3I::createRanges(pair.second,loads);
					}
				}
				if(!state->mPreLoads.empty())
					state->mState.write(CSceneManager::SChunkState::EState_PreLoaded);
				else
					state->mState.write(CSceneManager::SChunkState::EState_Loaded);
			}
			struct SLoadThreadParameter
				:public TBaseObject<SLoadThreadParameter>
			{
				CSceneManager * const mSceneManager;
				const CInt3 mPosition;
				CSceneManager::SChunkState * mState;
				SLoadThreadParameter(CSceneManager * sceneManager,const CInt3 & position,CSceneManager::SChunkState * state)
					:mSceneManager(sceneManager)
					,mPosition(position)
					,mState(state)
				{}
			};
			static Boolean loadThread(VoidPtr parameter)
			{
				SLoadThreadParameter * const loader_parameter=static_cast<SLoadThreadParameter*>(parameter);
				CSceneManager * const scene_manager=loader_parameter->mSceneManager;
				const CInt3 position=loader_parameter->mPosition;
				CSceneManager::SChunkState * const state=loader_parameter->mState;
				DEVILX_DELETE(loader_parameter);
				loadFunc(scene_manager,position,state);
				return true;
			}
		}
	}
}
const CUInt3 NSDevilX::NSCubeBlockWorld::CSceneManager::sChunkSize(32);
NSDevilX::NSCubeBlockWorld::CSceneManager::CSceneManager(const String & name,ITerrainGenerator * generator,NSRenderSystem::IScene * renderScene)
	:mName(name)
	,mLoadThreadPool(nullptr)
	,mRenderScene(renderScene)
	,mBlockScene(nullptr)
	,mRange(CInt3(INT_MIN),CInt3(INT_MAX))
{
	mLoadThreadPool=DEVILX_NEW CThreadPool(4);
	mTerrainGeneratorInstance=generator->createInstance(this);
	mBlockScene=NSCubeBlockSystem::getSystem()->createScene(mRenderScene);
}

NSDevilX::NSCubeBlockWorld::CSceneManager::~CSceneManager()
{
	DEVILX_DELETE(mLoadThreadPool);
}

Void NSDevilX::NSCubeBlockWorld::CSceneManager::update()
{
	for(auto & load_pair:mChunkLoadStates)
	{
		auto & state=load_pair.second->mState.beginWrite();
		if(SChunkState::EState_Loaded==state)
			state=SChunkState::EState_Unloading;
		else if(SChunkState::EState_PreLoaded==state)
		{
			for(auto const & pair:load_pair.second->mPreLoads)
			{
				for(auto const & range:pair.second)
				{
					mBlockScene->setBlockMT(range,pair.first);
				}
			}
			load_pair.second->mPreLoads.swap(decltype(load_pair.second->mPreLoads)());
			state=SChunkState::EState_Loaded;
		}
		load_pair.second->mState.endWrite();
	}
	//sync prepare
	for(auto const & loader_pair:mLoaders)
	{
		auto loader=loader_pair.second;
		for(Int32 x=-static_cast<Int32>(loader->getSyncChunkRange().x);x<=static_cast<Int32>(loader->getSyncChunkRange().x);x++)
		{
			for(Int32 y=-static_cast<Int32>(loader->getSyncChunkRange().y);y<=static_cast<Int32>(loader->getSyncChunkRange().y);y++)
			{
				for(Int32 z=-static_cast<Int32>(loader->getSyncChunkRange().z);z<=static_cast<Int32>(loader->getSyncChunkRange().z);z++)
				{
					CInt3 chunk_pos=CInt3(x,y,z)+loader->getChunkPosition();
					auto & state=mChunkLoadStates[chunk_pos];
					if(state)
					{
					}
					else
					{
						state=DEVILX_NEW SChunkState();
						state->mState.write(SChunkState::EState_Prepare);
					}
				}
			}
		}
	}
	//async load
	TVector<CRange3I> async_loads;
	for(auto const & loader_pair:mLoaders)
	{
		auto loader=loader_pair.second;
		for(Int32 x=-static_cast<Int32>(loader->getAsyncChunkRange().x);x<=static_cast<Int32>(loader->getAsyncChunkRange().x);x++)
		{
			for(Int32 y=-static_cast<Int32>(loader->getAsyncChunkRange().y);y<=static_cast<Int32>(loader->getAsyncChunkRange().y);y++)
			{
				for(Int32 z=-static_cast<Int32>(loader->getAsyncChunkRange().z);z<=static_cast<Int32>(loader->getAsyncChunkRange().z);z++)
				{
					CInt3 chunk_pos(x,y,z);
					auto & state=mChunkLoadStates[chunk_pos];
					if(state)
					{
						if(SChunkState::EState_Unloading==state->mState)
							state->mState.write(SChunkState::EState_Loaded);
					}
					else
					{
						state=DEVILX_NEW SChunkState();
						state->mState.write(SChunkState::EState_Loading);
						NSInternal::SLoadThreadParameter * param=DEVILX_NEW NSInternal::SLoadThreadParameter(this,chunk_pos,state);
						mLoadThreadPool->submitMT(NSInternal::loadThread,param);
					}
				}
			}
		}
	}
	//sync load
	for(auto const & loader_pair:mLoaders)
	{
		auto loader=loader_pair.second;
		for(Int32 x=-static_cast<Int32>(loader->getSyncChunkRange().x);x<=static_cast<Int32>(loader->getSyncChunkRange().x);x++)
		{
			for(Int32 y=-static_cast<Int32>(loader->getSyncChunkRange().y);y<=static_cast<Int32>(loader->getSyncChunkRange().y);y++)
			{
				for(Int32 z=-static_cast<Int32>(loader->getSyncChunkRange().z);z<=static_cast<Int32>(loader->getSyncChunkRange().z);z++)
				{
					CInt3 chunk_pos=CInt3(x,y,z)+loader->getChunkPosition();
					auto & state=mChunkLoadStates[chunk_pos];
					if(SChunkState::EState_Unloading==state->mState)
						state->mState.write(SChunkState::EState_Loaded);
					else if(SChunkState::EState_Loading==state->mState)
					{
						CTimer::sleep(10);
						z--;
					}
					else if(SChunkState::EState_Prepare==state->mState)
					{
						NSInternal::loadFunc(this,chunk_pos,state);
					}
				}
			}
		}
	}
	//unload
	for(auto iter=mChunkLoadStates.begin();iter!=mChunkLoadStates.end();)
	{
		if(SChunkState::EState_Unloading==iter->second->mState)
		{
			const auto & chunk_pos=iter->first;
			CRange3I block_range;
			block_range.setMin(chunk_pos*CSceneManager::sChunkSize);
			block_range.setMax(block_range.getMin()+CSceneManager::sChunkSize-CInt3::sOne);
			mBlockScene->setBlockMT(block_range,nullptr);
			iter=mChunkLoadStates.erase(iter);
		}
		else
		{
			++iter;
		}
	}
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