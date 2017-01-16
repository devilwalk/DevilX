#pragma once
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class ISceneLoader
		{
		protected:
			virtual ~ISceneLoader(){}
		public:
			virtual const String & getName()const=0;
			virtual Void setChunkPosition(DirectX::FXMVECTOR positionVec)=0;
			virtual Void setBlockPosition(DirectX::FXMVECTOR positionVec)=0;
			virtual const CSInt3 & getChunkPosition()const=0;
			virtual Void setChunkRange(const CSInt3 & range)=0;
			virtual const CSInt3 & getChunkRange()const=0;
		};
	}
}