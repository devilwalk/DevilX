    float4 position=float4(iPosition, 1.0);
#if SKELETON_ANIMATION
	float3 world_position_temp=float3(0.0,0.0,0.0);
	for(int i=0;i<4;++i)
	{
		int matrix_index=3*iBlendIndex[i];
		world_position_temp+=float3(dot(position,gSkeletonAnimationMatrix[matrix_index]),dot(position,gSkeletonAnimationMatrix[matrix_index+1]),dot(position,gSkeletonAnimationMatrix[matrix_index+2]))*iBlendWeight[i];
	}
	float4 world_position=float4(world_position_temp,1.0);
#else
	float4 world_position = float4(dot(position,gWorldMatrix[0]),dot(position,gWorldMatrix[1]),dot(position,gWorldMatrix[2]),1.0);
end
    oPosition = float4(dot(world_position,gViewProjectionMatrix[0]),dot(world_position,gViewProjectionMatrix[1]),dot(world_position,gViewProjectionMatrix[2]),dot(world_position,gViewProjectionMatrix[3]));
#if OUTPUT_MAIN_UV
	oMainUV=iMainUV;
#endif
	oQuery=iQuery;