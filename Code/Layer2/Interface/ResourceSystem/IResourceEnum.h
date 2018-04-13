#pragma once
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class IEnum
		{
		public:
			enum EResourceType
			{
				EResourceType_Unknown,
				EResourceType_Image,
				EResourceType_CommonFile,
				EResourceType_FBX
			};
		};
	}
}