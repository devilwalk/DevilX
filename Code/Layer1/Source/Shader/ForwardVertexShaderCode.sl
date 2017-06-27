    float4 world_position = mul(gWorldMatrix, float4(iPosition, 1.0));
    oPosition = mul(gViewProjectionMatrix, world_position);
#if OUTPUT_WORLD_POSITION
	oWorldPosition = world_position.xyz;
#endif
#if OUTPUT_WORLD_NORMAL
	oWorldNormal = mul(convert(gWorldMatrix), iNormal);
#endif
#if OUTPUT_WORLD_TANGENT
	oWorldTangent = mul(convert(gWorldMatrix), iTangent);
#endif
#if OUTPUT_MAIN_UV
	oMainUV = iMainUV;
#endif
#if OUTPUT_DIFFUSE
	oDiffuse = iDiffuse;
#endif