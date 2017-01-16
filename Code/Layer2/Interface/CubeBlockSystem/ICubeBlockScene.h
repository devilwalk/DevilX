#pragma once
#include "ICubeBlock.h"
namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		class IScene
		{
		protected:
			virtual ~IScene(){}
		public:
			virtual Void setBlockMT(DirectX::FXMVECTOR positionVec,IBlock * block)=0;
			virtual Void setBlockMT(const CRange3I & range,IBlock * block)=0;
			virtual IBlock * getBlockMT(DirectX::FXMVECTOR positionVec)=0;
		};
	}
}