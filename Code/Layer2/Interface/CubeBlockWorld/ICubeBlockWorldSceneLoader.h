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
			virtual Void setChunkPosition(const CInt3 & position)=0;
			virtual Void setBlockPosition(const CInt3 & position)=0;
			virtual const CInt3 & getChunkPosition()const=0;
			virtual Void setSyncChunkRange(const CUInt3 & range)=0;
			virtual const CUInt3 & getSyncChunkRange()const=0;
			virtual Void setAsyncChunkRange(const CUInt3 & range)=0;
			virtual const CUInt3 & getAsyncChunkRange()const=0;
		};
	}
}