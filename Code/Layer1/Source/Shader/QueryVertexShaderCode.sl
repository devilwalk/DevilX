    float4 world_position = mul(gWorldMatrix, float4(iPosition, 1.0));
    oPosition = mul(gViewProjectionMatrix, world_position);
#if OUTPUT_MAIN_UV
	oMainUV=iMainUV;
#endif
	oQuery=iQuery;