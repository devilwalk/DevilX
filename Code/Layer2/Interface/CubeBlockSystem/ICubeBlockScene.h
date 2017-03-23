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
			virtual Void setBlockMT(const CInt3 & position,IBlock * block)=0;
			virtual Void setBlockMT(const CRange3I & range,IBlock * block)=0;
			virtual IBlock * getBlockMT(const CInt3 & position)=0;
		};
	}
}