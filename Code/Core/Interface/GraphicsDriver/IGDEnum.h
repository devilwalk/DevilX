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
				enum EInstanceMajorType
				{
					EInstanceMajorType_D3D,
					EInstanceMajorType_Vulkan,
					EInstanceMajorType_GL,
					EInstanceMajorType_Software
				};
				enum EInstanceMinorType_D3D
				{
					EInstanceMinorType_D3D_12_1,
					EInstanceMinorType_D3D_12_0,
					EInstanceMinorType_D3D_11_1,
					EInstanceMinorType_D3D_11_0,
					EInstanceMinorType_D3D_10_1,
					EInstanceMinorType_D3D_10_0,
					EInstanceMinorType_D3D_9_3,
				};
				enum EInstanceMinorType_GL
				{
					EInstanceMinorType_GL_4_6,
					EInstanceMinorType_GL_4_5,
					EInstanceMinorType_GL_4_4,
					EInstanceMinorType_GL_4_3,
					EInstanceMinorType_GL_4_2,
					EInstanceMinorType_GL_4_1,
					EInstanceMinorType_GL_4_0,
					EInstanceMinorType_GL_3_3,
					EInstanceMinorType_GL_3_2,
					EInstanceMinorType_GL_3_1,
					EInstanceMinorType_GL_3_0,
					EInstanceMinorType_GL_2_0,
					EInstanceMinorType_GL_ES3_2,
					EInstanceMinorType_GL_ES3_1,
					EInstanceMinorType_GL_ES3_0,
					EInstanceMinorType_GL_ES2_0
				};
				enum EInstanceMinorType_Software
				{

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