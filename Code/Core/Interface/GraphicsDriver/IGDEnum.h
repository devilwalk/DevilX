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
				enum class EInstance
				{
					Vulkan,
					GL4_6,
					GL4_5,
					GL4_4,
					GL4_3,
					GL4_2,
					GL4_1,
					GL4_0,
					GL3_3,
					GL3_2,
					GL3_1,
					GL3_0,
					GL2_0,
					D3D12,
					D3D11,
					D3D10,
					D3D9,
					GLES3_2,
					GLES3_1,
					GLES3_0,
					GLES2_0
				};
			};
		}
	}
}