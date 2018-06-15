#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IEnum
		{
		public:
			enum EDeviceType
			{
				EDeviceType_Compute
			};
			enum EComputeDeviceType
			{
				EComputeDeviceType_CPU,
				EComputeDeviceType_GPU
			};
			enum EResourceLocationType
			{
				EResourceLocationType_SystemMemory,
				EResourceLocationType_GPUMemory
			};
		};
	}
}