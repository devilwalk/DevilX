#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IEnum
		{
		public:
			enum EQueryType
			{
				EQueryType_Ray,
				EQueryType_Box,
				EQueryType_Sphere
			};
			enum EQueryResultType
			{
				EQueryResultType_HitPoint,
				EQueryResultType_HitSubEntity
			};
		};
	}
}