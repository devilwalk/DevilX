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
			virtual Void setChunkRange(const CInt3 & range)=0;
			virtual const CInt3 & getChunkRange()const=0;
		};
	}
}