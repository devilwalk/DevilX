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
			virtual Void setBlock(const CInt3 & position,IBlock * block)=0;
			virtual Void setBlock(const CRange3I & range,IBlock * block)=0;
			virtual IBlock * getBlock(const CInt3 & position)const=0;
		};
	}
}