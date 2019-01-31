#pragma once
namespace NSDevilX
{
	namespace NSGameEngine
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
		};
	}
}