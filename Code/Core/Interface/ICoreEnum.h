#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IEnum
		{
		public:
			enum EGPUDeviceType
			{
				EGPUDeviceType_GL,
				EGPUDeviceType_GLES,
				EGPUDeviceType_Vulkan,
				EGPUDeviceType_CL,
				EGPUDeviceType_D3D9,
				EGPUDeviceType_D3D10,
				EGPUDeviceType_D3D11,
				EGPUDeviceType_D3D12,
			};
			enum EResourceLocationType
			{
				EResourceLocationType_SystemMemory,
				EResourceLocationType_GPUMemory
			};
		};
	}
}