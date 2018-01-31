#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCubeBlockWorld;

NSDevilX::NSCubeBlockWorld::CSceneLoader::CSceneLoader(const String & name,CSceneManager * sceneManager)
	:mName(name)
	,mSceneManager(sceneManager)
	,mThreadPool(nullptr)
	,mPosition(0)
{
	mThreadPool=DEVILX_NEW CThreadPool(4);
}

NSDevilX::NSCubeBlockWorld::CSceneLoader::~CSceneLoader()
{
	DEVILX_DELETE(mThreadPool);
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

Void NSDevilX::NSCubeBlockWorld::CSceneLoader::setSyncChunkRange(const CUInt3 & range)
{
	if(range!=mSyncRange)
	{
		mSyncRange=range;
	}
}

const CUInt3 & NSDevilX::NSCubeBlockWorld::CSceneLoader::getSyncChunkRange() const
{
	// TODO: insert return statement here
	return mSyncRange;
}

Void NSDevilX::NSCubeBlockWorld::CSceneLoader::setAsyncChunkRange(const CUInt3 & range)
{
	if(range!=mAsyncRange)
	{
		mAsyncRange=range;
	}
}

const CUInt3 & NSDevilX::NSCubeBlockWorld::CSceneLoader::getAsyncChunkRange() const
{
	// TODO: 在此处插入 return 语句
	return mAsyncRange;
}