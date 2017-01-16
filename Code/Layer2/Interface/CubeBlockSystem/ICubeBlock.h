#pragma once
#include "ICubeBlockEnum.h"
#include "ICubeBlockFace.h"
namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		class IBlock
		{
		protected:
			virtual ~IBlock(){}
		public:
			virtual const String & getName()const=0;
			virtual IBlockFace * getFace(IEnum::EBlockFaceType type)const=0;
		};
	}
}