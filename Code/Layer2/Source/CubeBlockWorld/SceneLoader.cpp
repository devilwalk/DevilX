#include "Precompiler.h"
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		namespace NSInternal
		{
			struct SLoadThreadParameter
				:public TBaseObject<SLoadThreadParameter>
			{
				CSceneManager * const mSceneManager;
				const CInt3 mPosition;
				const Bool mIsLoad;
				SLoadThreadParameter(CSceneManager * sceneManager,DirectX::FXMVECTOR position,Bool isLoad)
					:mSceneManager(sceneManager)
					,mPosition(position)
					,mIsLoad(isLoad)
				{}
			};
			static Boolean loadThread(VoidPtr parameter)
			{
				SLoadThreadParameter * const loader_parameter=static_cast<SLoadThreadParameter*>(parameter);
				if(loader_parameter->mIsLoad)
					loader_parameter->mSceneManager->loadChunkMT(loader_parameter->mPosition);
				else
					loader_parameter->mSceneManager->unloadChunkMT(loader_parameter->mPosition);
				DEVILX_DELETE(loader_parameter);
				return true;
			}
			struct SDispatchThreadParameter
				:public TBaseObject<SDispatchThreadParameter>
			{
				CThreadPool * const mThreadPool;
				CSceneManager * const mSceneManager;
				const CRange3I * const mRange;
				const Bool mIsLoad;
				SDispatchThreadParameter(CThreadPool * threadPool,CSceneManager * sceneManager,const CRange3I * range,Bool isLoad)
					:mThreadPool(threadPool)
					,mSceneManager(sceneManager)
					,mRange(range)
					,mIsLoad(isLoad)
				{}
				~SDispatchThreadParameter()
				{
					DEVILX_DELETE(mRange);
				}
			};
			static Boolean dispatchThread(VoidPtr parameter)
			{
				SDispatchThreadParameter * const loader_parameter=static_cast<SDispatchThreadParameter*>(parameter);
				//加载方式从中心向外环加载
				/*Int32 range=std::max<Int32>(std::max<Int32>(loader_parameter->mRange.x,loader_parameter->mRange.y),loader_parameter->mRange.z);
				for(auto i=0;i<=range;++i)
				{
				CSInt3 start=DirectX::XMVectorMax(loader_parameter->mPosition-CSInt3(i),loader_parameter->mPosition-loader_parameter->mRange);
				CSInt3 end=DirectX::XMVectorMin(loader_parameter->mPosition+CSInt3(i),loader_parameter->mPosition+loader_parameter->mRange);
				//top
				for(auto x=start.x;x<=end.x;++x)
				{
				for(auto z=start.z;z<=end.z;++z)
				{
				CSInt3 chunk_pos(x,end.y,z);
				loader_parameter->mThreadPool->submitMT(loadThread,DEVILX_NEW SLoadThreadParameter(loader_parameter->mSceneManager,chunk_pos));
				}
				}
				//bottom
				for(auto x=start.x;x<=end.x;++x)
				{
				for(auto z=start.z;z<=end.z;++z)
				{
				CSInt3 chunk_pos(x,start.y,z);
				loader_parameter->mThreadPool->submitMT(loadThread,DEVILX_NEW SLoadThreadParameter(loader_parameter->mSceneManager,chunk_pos));
				}
				}
				//left
				for(auto y=start.y;y<=end.y;++y)
				{
				for(auto z=start.z;z<=end.z;++z)
				{
				CSInt3 chunk_pos(start.x,y,z);
				loader_parameter->mThreadPool->submitMT(loadThread,DEVILX_NEW SLoadThreadParameter(loader_parameter->mSceneManager,chunk_pos));
				}
				}
				//right
				for(auto y=start.y;y<=end.y;++y)
				{
				for(auto z=start.z;z<=end.z;++z)
				{
				CSInt3 chunk_pos(end.x,y,z);
				loader_parameter->mThreadPool->submitMT(loadThread,DEVILX_NEW SLoadThreadParameter(loader_parameter->mSceneManager,chunk_pos));
				}
				}
				//front
				for(auto x=start.x;x<=end.x;++x)
				{
				for(auto y=start.y;y<=end.y;++y)
				{
				CSInt3 chunk_pos(x,y,start.z);
				loader_parameter->mThreadPool->submitMT(loadThread,DEVILX_NEW SLoadThreadParameter(loader_parameter->mSceneManager,chunk_pos));
				}
				}
				//back
				for(auto x=start.x;x<=end.x;++x)
				{
				for(auto y=start.y;y<=end.y;++y)
				{
				CSInt3 chunk_pos(x,y,end.z);
				loader_parameter->mThreadPool->submitMT(loadThread,DEVILX_NEW SLoadThreadParameter(loader_parameter->mSceneManager,chunk_pos));
				}
				}
				}*/
				for(auto x=loader_parameter->mRange->getMin().x;x<=loader_parameter->mRange->getMax().x;++x)
				{
					for(auto y=loader_parameter->mRange->getMin().y;y<=loader_parameter->mRange->getMax().y;++y)
					{
						for(auto z=loader_parameter->mRange->getMin().z;z<=loader_parameter->mRange->getMax().z;++z)
						{
							CInt3 chunk_pos(x,y,z);
							loader_parameter->mThreadPool->submitMT(loadThread,DEVILX_NEW SLoadThreadParameter(loader_parameter->mSceneManager,chunk_pos,loader_parameter->mIsLoad));
						}
					}
				}
				DEVILX_DELETE(loader_parameter);
				return true;
			}
		}
	}
}
using namespace NSDevilX;
using namespace NSCubeBlockWorld;

NSDevilX::NSCubeBlockWorld::CSceneLoader::CSceneLoader(const String & name,CSceneManager * sceneManager)
	:mName(name)
	,mSceneManager(sceneManager)
	,mThreadPool(nullptr)
	,mPosition(0)
	,mRange(0)
{
	mThreadPool=DEVILX_NEW CThreadPool(4);
}

NSDevilX::NSCubeBlockWorld::CSceneLoader::~CSceneLoader()
{
	DEVILX_DELETE(mThreadPool);
}

Void NSDevilX::NSCubeBlockWorld::CSceneLoader::update()
{
	process();
}

const String & NSDevilX::NSCubeBlockWorld::CSceneLoader::getName() const
{
	// TODO: insert return statement here
	return mName;
}

Void NSDevilX::NSCubeBlockWorld::CSceneLoader::setChunkPosition(const CInt3 & position)
{
	if(position!=mPosition)
	{
		mPosition=position;
		addDirtyFlag(EDirtyFlag_Load);
	}
}

Void NSDevilX::NSCubeBlockWorld::CSceneLoader::setBlockPosition(const CInt3 & position)
{
	CInt3 block_position(position);
	DirectX::XMVECTOR chunk_size_vec=CInt3(CSceneManager::sChunkSize);
	DirectX::XMVECTOR value_offset_vec=CInt3((block_position.x<0)?-1:0,(block_position.y<0)?-1:0,(block_position.z<0)?-1:0);
	CInt3 value_offset(value_offset_vec);
	const DirectX::XMVECTOR chunk_pos_vec=CInt3((position-value_offset_vec)/chunk_size_vec)+value_offset_vec;
	setChunkPosition(chunk_pos_vec);
}

const CInt3 & NSDevilX::NSCubeBlockWorld::CSceneLoader::getChunkPosition() const
{
	// TODO: insert return statement here
	return mPosition;
}

Void NSDevilX::NSCubeBlockWorld::CSceneLoader::setChunkRange(const CInt3 & range)
{
	if(range!=mRange)
	{
		mRange=range;
		addDirtyFlag(EDirtyFlag_Load);
	}
}

const CInt3 & NSDevilX::NSCubeBlockWorld::CSceneLoader::getChunkRange() const
{
	// TODO: insert return statement here
	return mRange;
}

Boolean NSDevilX::NSCubeBlockWorld::CSceneLoader::_process(UInt32 flagIndex,OUT Bool & needNextProcess)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Load:
		_processLoad();
		return true;
	}
	return CDirtyFlagContainer::_process(flagIndex,needNextProcess);
}

Void NSDevilX::NSCubeBlockWorld::CSceneLoader::_processLoad()
{
	auto const new_loaded_range_min_vec=DirectX::XMVectorMax(mPosition-mRange,mSceneManager->getRange().getMin());
	CInt3 new_loaded_range_max=DirectX::XMVectorMin(mPosition+mRange,mSceneManager->getRange().getMax());
	DirectX::XMVECTOR const new_loaded_range_max_vec=new_loaded_range_max;
	const CRange3I new_loaded_range(new_loaded_range_min_vec,new_loaded_range_max_vec);
	TList<CRange3I*> need_to_loaded_ranges;
	TList<CRange3I*> need_to_unloaded_ranges;
	if(new_loaded_range.isValidate())
	{
		if(mLoadedRange.isValidate())
		{
			CRange3I intersect;
			CRange3I::createIntersection(new_loaded_range,mLoadedRange,intersect);
			if(intersect.isValidate())
			{
				CRange3I::eraseRange(new_loaded_range,intersect,need_to_loaded_ranges);
				CRange3I::eraseRange(mLoadedRange,intersect,need_to_unloaded_ranges);
			}
			else
			{
				need_to_loaded_ranges.push_back(DEVILX_NEW CRange3I(new_loaded_range));
				need_to_unloaded_ranges.push_back(DEVILX_NEW CRange3I(mLoadedRange));
			}
		}
		else
		{
			need_to_loaded_ranges.push_back(DEVILX_NEW CRange3I(new_loaded_range));
		}
	}
	else
	{
		if(mLoadedRange.isValidate())
		{
			need_to_unloaded_ranges.push_back(DEVILX_NEW CRange3I(mLoadedRange));
		}
	}
	//过滤同步加载的chunk
	Boolean need_sync_load=false;
	const CRange3I sync_load_range(mPosition/*-CSInt3::sOne*/,mPosition/*+CSInt3::sOne*/);
	TList<CRange3I*> temp_need_to_loaded_ranges;
	for(auto range:need_to_loaded_ranges)
	{
		CRange3I intersect;
		CRange3I::createIntersection(sync_load_range,*range,intersect);
		if(intersect.isValidate())
		{
			CRange3I::eraseRange(*range,intersect,temp_need_to_loaded_ranges);
			need_sync_load=true;
		}
		else
		{
			temp_need_to_loaded_ranges.push_back(range);
		}
	}
	need_to_loaded_ranges=temp_need_to_loaded_ranges;
	for(auto range:need_to_loaded_ranges)
		mThreadPool->submitMT(NSInternal::dispatchThread,DEVILX_NEW NSInternal::SDispatchThreadParameter(mThreadPool,mSceneManager,range,True));
	for(auto range:need_to_unloaded_ranges)
		mThreadPool->submitMT(NSInternal::dispatchThread,DEVILX_NEW NSInternal::SDispatchThreadParameter(mThreadPool,mSceneManager,range,False));
	if(need_sync_load)
	{
		for(auto y=sync_load_range.getMin().y;y<=sync_load_range.getMax().y;++y)
		{
			for(auto x=sync_load_range.getMin().x;x<=sync_load_range.getMax().x;++x)
			{
				for(auto z=sync_load_range.getMin().z;z<=sync_load_range.getMax().z;++z)
				{
					CInt3 block_pos(x,y,z);
					mSceneManager->loadChunkMT(block_pos);
				}
			}
		}
	}
	mLoadedRange=new_loaded_range;
}
