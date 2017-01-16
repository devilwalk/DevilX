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
			enum EColourUnitStateType
			{
				EColourUnitStateType_Ambient,
				EColourUnitStateType_Diffuse,
				EColourUnitStateType_Specular,
				EColourUnitStateType_Emissive
			};
			enum ETextureUnitStateType
			{
				ETextureUnitStateType_Diffuse,
				ETextureUnitStateType_Specular,
				ETextureUnitStateType_Normal,
				ETextureUnitStateType_Light
			};
			enum ETextureFormat
			{
				ETextureFormat_R8G8B8A8,
				ETextureFormat_BC1,
				ETextureFormat_BC2,
				ETextureFormat_BC3,
				ETextureFormat_Font,
				ETextureFormat_Shadow,
				ETextureFormat_Environment
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
		};
	}
}