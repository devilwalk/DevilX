#pragma once
namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		class IEnum
		{
		public:
			enum EBlockFaceType
			{
				EBlockFaceType_Positive_X,
				EBlockFaceType_Negative_X,
				EBlockFaceType_Positive_Y,
				EBlockFaceType_Negative_Y,
				EBlockFaceType_Positive_Z,
				EBlockFaceType_Negative_Z
			};
		};
	}
}