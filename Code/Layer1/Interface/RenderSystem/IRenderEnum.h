#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IEnum
		{
		public:
			enum ESceneManagerAlgorithm
			{
				ESceneManagerAlgorithm_Simple,
				ESceneManagerAlgorithm_QuadTree,
				ESceneManagerAlgorithm_Octree,
				ESceneManagerAlgorithm_Grid
			};
			enum ERenderTechnique
			{
				ERenderTechnique_Forward,
				ERenderTechnique_DeferredShading,
				ERenderTechnique_DeferredLighting
			};
			enum ELightType
			{
				ELightType_Directional,
				ELightType_Point,
				ELightType_Spot
			};
			enum EProjectionType
			{
				EProjectionType_Perspective,
				EProjectionType_Ortho
			};
			enum EOperationType
			{
				EOperationType_PointList,
				EOperationType_LineList,
				EOperationType_LineStrip,
				EOperationType_TriangleList,
				EOperationType_TriangleStrip
			};
			enum ERenderableSurfaceFormat
			{
				ERenderableSurfaceFormat_R8G8B8A8
			};
			enum ETexture2DFormat
			{
				ETexture2DFormat_R8G8B8A8,
				ETexture2DFormat_A8,
				ETexture2DFormat_BC1,
				ETexture2DFormat_BC2,
				ETexture2DFormat_BC3
			};
			enum ETextureCubeFormat
			{
				ETextureCubeFormat_R8G8B8A8,
				ETextureCubeFormat_BC1,
				ETextureCubeFormat_BC2,
				ETextureCubeFormat_BC3
			};
			enum ETextureType
			{
				ETextureType_2D,
				ETextureType_Cube
			};
			enum ECubeTextureFace
			{
				ECubeTextureFace_Positive_X,
				ECubeTextureFace_Negative_X,
				ECubeTextureFace_Positive_Y,
				ECubeTextureFace_Negative_Y,
				ECubeTextureFace_Positive_Z,
				ECubeTextureFace_Negative_Z
			};
			enum ETextureCoord
			{
				ETextureCoord_0,
				ETextureCoord_1
			};
			enum EMaterialAmbientModel
			{
				EMaterialAmbientModel_None,
				EMaterialAmbientModel_Constant,
				EMaterialAmbientModel_Hemisphere,
				EMaterialAmbientModel_SphericalHarmonics
			};
			enum EMaterialDiffuseModel
			{
				EMaterialDiffuseModel_None,
				EMaterialDiffuseModel_Lambert,
				EMaterialDiffuseModel_OrenNayar,
				EMaterialDiffuseModel_Minnaert,
				EMaterialDiffuseModel_Disney
			};
			enum EMaterialSpecularModel
			{
				EMaterialSpecularModel_None,
				EMaterialSpecularModel_Phong,
				EMaterialSpecularModel_BlinnPhong,
				EMaterialSpecularModel_CookTorrance,
				EMaterialSpecularModel_UE4
			};
			enum EShaderType
			{
				EShaderType_VS,
				EShaderType_PS,
				EShaderType_GS,
				EShaderType_CS
			};
			enum EShaderCodeType
			{
				EShaderCodeType_HLSL_6_0,
				EShaderCodeType_HLSL_5_0,
				EShaderCodeType_HLSL_4_0,
				EShaderCodeType_GLSL_4_5,
				EShaderCodeType_GLSLES_3_2
			};
			enum EProgramResourceType
			{
				EProgramResourceType_Unknown,
				EProgramResourceType_ConstantBuffer,
				EProgramResourceType_TextureBuffer,
				EProgramResourceType_Texture,
				EProgramResourceType_Sampler
			};
			enum EAutoGPUPropgramParameterDataSource
			{
				EAutoGPUPropgramParameterDataSource_WorldMatrix_Coloume_0,
				EAutoGPUPropgramParameterDataSource_WorldMatrix_Coloume_1,
				EAutoGPUPropgramParameterDataSource_WorldMatrix_Coloume_2,
				EAutoGPUPropgramParameterDataSource_ViewMatrix_Coloume_0,
				EAutoGPUPropgramParameterDataSource_ViewMatrix_Coloume_1,
				EAutoGPUPropgramParameterDataSource_ViewMatrix_Coloume_2,
				EAutoGPUPropgramParameterDataSource_ProjectionMatrix_Coloume_0,
				EAutoGPUPropgramParameterDataSource_ProjectionMatrix_Coloume_1,
				EAutoGPUPropgramParameterDataSource_ProjectionMatrix_Coloume_2,
				EAutoGPUPropgramParameterDataSource_ProjectionMatrix_Coloume_4,
				EAutoGPUPropgramParameterDataSource_WorldViewMatrix_Coloume_0,
				EAutoGPUPropgramParameterDataSource_WorldViewMatrix_Coloume_1,
				EAutoGPUPropgramParameterDataSource_WorldViewMatrix_Coloume_2,
				EAutoGPUPropgramParameterDataSource_WorldViewMatrix_Coloume_3,
				EAutoGPUPropgramParameterDataSource_ViewProjectionMatrix_Coloume_0,
				EAutoGPUPropgramParameterDataSource_ViewProjectionMatrix_Coloume_1,
				EAutoGPUPropgramParameterDataSource_ViewProjectionMatrix_Coloume_2,
				EAutoGPUPropgramParameterDataSource_ViewProjectionMatrix_Coloume_3,
				EAutoGPUPropgramParameterDataSource_WorldViewProjectionMatrix_Coloume_0,
				EAutoGPUPropgramParameterDataSource_WorldViewProjectionMatrix_Coloume_1,
				EAutoGPUPropgramParameterDataSource_WorldViewProjectionMatrix_Coloume_2,
				EAutoGPUPropgramParameterDataSource_WorldViewProjectionMatrix_Coloume_3
			};
			enum ESamplerFilter
			{
				ESamplerFilter_MIN_MAG_MIP_POINT,
				ESamplerFilter_MIN_MAG_POINT_MIP_LINEAR,
				ESamplerFilter_MIN_POINT_MAG_LINEAR_MIP_POINT,
				ESamplerFilter_MIN_POINT_MAG_MIP_LINEAR,
				ESamplerFilter_MIN_LINEAR_MAG_MIP_POINT,
				ESamplerFilter_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
				ESamplerFilter_MIN_MAG_LINEAR_MIP_POINT,
				ESamplerFilter_MIN_MAG_MIP_LINEAR,
				ESamplerFilter_ANISOTROPIC,
				ESamplerFilter_COMPARISON_MIN_MAG_MIP_POINT,
				ESamplerFilter_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
				ESamplerFilter_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
				ESamplerFilter_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
				ESamplerFilter_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
				ESamplerFilter_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
				ESamplerFilter_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
				ESamplerFilter_COMPARISON_MIN_MAG_MIP_LINEAR,
				ESamplerFilter_COMPARISON_ANISOTROPIC,
				ESamplerFilter_MINIMUM_MIN_MAG_MIP_POINT,
				ESamplerFilter_MINIMUM_MIN_MAG_POINT_MIP_LINEAR,
				ESamplerFilter_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
				ESamplerFilter_MINIMUM_MIN_POINT_MAG_MIP_LINEAR,
				ESamplerFilter_MINIMUM_MIN_LINEAR_MAG_MIP_POINT,
				ESamplerFilter_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
				ESamplerFilter_MINIMUM_MIN_MAG_LINEAR_MIP_POINT,
				ESamplerFilter_MINIMUM_MIN_MAG_MIP_LINEAR,
				ESamplerFilter_MINIMUM_ANISOTROPIC,
				ESamplerFilter_MAXIMUM_MIN_MAG_MIP_POINT,
				ESamplerFilter_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR,
				ESamplerFilter_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
				ESamplerFilter_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR,
				ESamplerFilter_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT,
				ESamplerFilter_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
				ESamplerFilter_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT,
				ESamplerFilter_MAXIMUM_MIN_MAG_MIP_LINEAR,
				ESamplerFilter_MAXIMUM_ANISOTROPIC
			};
			enum ETextureAddressMode
			{
				ETextureAddressMode_WRAP,
				ETextureAddressMode_MIRROR,
				ETextureAddressMode_CLAMP,
				ETextureAddressMode_BORDER,
				ETextureAddressMode_MIRROR_ONCE
			};
			enum EComparisonFunction
			{
				EComparisonFunction_NEVER,
				EComparisonFunction_LESS,
				EComparisonFunction_EQUAL,
				EComparisonFunction_LESS_EQUAL,
				EComparisonFunction_GREATER,
				EComparisonFunction_NOT_EQUAL,
				EComparisonFunction_GREATER_EQUAL,
				EComparisonFunction_ALWAYS
			};
		};
	}
}