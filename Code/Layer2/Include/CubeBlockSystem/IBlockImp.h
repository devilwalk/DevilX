#pragma once
#include "IBlockFaceImp.h"
namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		class IBlockImp
			:public TBaseObject<IBlockImp>
			,public IBlock
		{
		protected:
			const String mName;
			IBlockFaceImp * mFaces[6];
		public:
			IBlockImp(const String & name);
			~IBlockImp();

			// Inherited via IBlock
			virtual const String & getName() const override;
			virtual IBlockFace * getFace(IEnum::EBlockFaceType type) const override;
		};
	}
}