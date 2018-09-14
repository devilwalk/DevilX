#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CEnum
			{
			public:
				enum ETechniqueType
				{
					ETechniqueType_Forward,
					ETechniqueType_GBufferDS,
					ETechniqueType_GBufferDL,
					ETechniqueType_Query,
					ETechniqueType_Count
				};
				enum EForwardPassType
				{
					EForwardPassType_NoLight,
					EForwardPassType_Ambient=EForwardPassType_NoLight,
					EForwardPassType_DirectionLight,
					EForwardPassType_PointLight,
					EForwardPassType_SpotLight,
					EForwardPassType_Count
				};
				enum EVertexBufferType
				{
					EVertexBufferType_Position,
					EVertexBufferType_Normal,
					EVertexBufferType_Tangent,
					EVertexBufferType_TextureCoord0,
					EVertexBufferType_TextureCoord1,
					EVertexBufferType_BlendWeight,
					EVertexBufferType_BlendIndex,
					EVertexBufferType_Diffuse,
					EVertexBufferType_GeometryCount,
					EVertexBufferType_Query=EVertexBufferType_GeometryCount,
					EVertexBufferType_Count
				};
			};
		}
	}
}