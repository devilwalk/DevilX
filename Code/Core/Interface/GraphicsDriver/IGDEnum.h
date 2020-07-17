#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IEnum
			{
			public:
				enum EInstance
				{
					EInstance_Vulkan,
					EInstance_D3D12_1,
					EInstance_D3D12_0,
					EInstance_GL4_6,
					EInstance_D3D11_1,
					EInstance_D3D11_0,
					EInstance_GL4_5,
					EInstance_GL4_4,
					EInstance_GL4_3,
					EInstance_GL4_2,
					EInstance_GL4_1,
					EInstance_GL4_0,
					EInstance_D3D10_1,
					EInstance_D3D10_0,
					EInstance_GL3_3,
					EInstance_GL3_2,
					EInstance_GL3_1,
					EInstance_GL3_0,
					EInstance_D3D9_3,
					EInstance_GL2_0,
					EInstance_GLES3_2,
					EInstance_GLES3_1,
					EInstance_GLES3_0,
					EInstance_GLES2_0
				};

				enum EQueue
				{
					EQueue_3D,
					EQueue_Compute,
					EQueue_PCIETransfer
				};
			};
		}
	}
}