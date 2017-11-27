	float3 colour_emissive = gEmissiveColour;
	float3 colour_diffuse_factor = gMainColour;
    float3 colour_specular_factor = gSpecularColour;
    float alpha = gAlpha;
#if OUTPUT_DIFFUSE
    colour_emissive *= iDiffuse.rgb;
    colour_diffuse_factor *= iDiffuse.rgb;
    alpha *= iDiffuse.a;
#endif
#if USE_DIFFUSE_TEXTURE
	float4 diffuse_texture_sampler=SAMPLE_TEXTURE(Diffuse,iMainUV);
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;
	float diffuse_texture_alpha = diffuse_texture_sampler.a;
	alpha *= diffuse_texture_alpha;
	colour_diffuse_factor *= diffuse_texture_colour;
	colour_emissive *= diffuse_texture_colour;
#endif
#if USE_ALPHA_TEST
	if(alpha - gAlphaTestValue<0)discard;
#endif
#if USE_LIGHTING
    #if USE_DIRECTION_LIGHT||USE_POINT_LIGHT||USE_SPOT_LIGHT
    float3 lighting_colour=0;
    float lighting_falloff_factor=1.0;
	float3 world_normal=normalize(iWorldNormal);
		#if USE_NORMAL_TEXTURE
	float4 normal_texture_sampler=SAMPLE_TEXTURE(Normal,iMainUV);
	float3 normal_texture_normal=normal_texture_sampler.xyz * 2.0-1.0;
	float3 world_tangent=normalize(iWorldTangent);
	float3 world_binormal=cross(world_normal,world_tangent);
	float3x3 tbn=float3x3(world_tangent,world_binormal,world_normal);
	world_normal=mul(tbn,normal_texture_normal);
		#endif
		#if USE_DIRECTION_LIGHT
	float3 vertex_to_light_direction = -gDirectionLightDirection;
    float3 light_diffuse_colour = gDirectionLightDiffuseColour;
    float3 light_specular_colour = gDirectionLightSpecularColour;
	    #elif USE_POINT_LIGHT
    float3 vertex_to_light = gPointLightPosition - iWorldPosition;
    lighting_falloff_factor=calcFalloffFactor(length(vertex_to_light),gPointLightStartFallOffDistance,gPointLightReciprocalRange);
	float3 vertex_to_light_direction = normalize(vertex_to_light);
    float3 light_diffuse_colour = gPointLightDiffuseColour;
    float3 light_specular_colour = gPointLightSpecularColour;
	    #elif USE_SPOT_LIGHT
    float3 vertex_to_light = gSpotLightPosition - iWorldPosition;
    float falloff_distance_factor=calcFalloffFactor(length(vertex_to_light),gSpotLightStartFallOffDistance,gSpotLightReciprocalRange);
	float3 vertex_to_light_direction = normalize(vertex_to_light);
    float falloff_angle_factor=calcFalloffFactor(dot(vertex_to_light_direction,gSpotLightDirection),gSpotLightCosInnerCornerHalfAngle,gSpotLightReciprocalDeltaCosHalfAngle);
    lighting_falloff_factor=falloff_distance_factor*falloff_angle_factor;
    float3 light_diffuse_colour = gSpotLightDiffuseColour;
    float3 light_specular_colour = gSpotLightSpecularColour;
	    #endif
	float lighting_diffuse_factor = calcLambertDiffuseFactor(vertex_to_light_direction, world_normal);
    float3 lighting_diffuse_colour = light_diffuse_colour * lighting_diffuse_factor;
	lighting_colour+=lighting_diffuse_colour;
		#if USE_SPECULAR
	float lighting_specular_factor=calcBlinnPhongSpecularFactor(vertex_to_light_direction,world_normal,iWorldPosition,getCameraPosition());
	float3 lighting_specular_colour=lighting_diffuse_factor > 0.0?pow(lighting_specular_factor,gSpecularPower) * light_specular_colour:0.0;
	lighting_colour+=lighting_specular_colour;
		#endif
    oColour.rgb+=lighting_colour*lighting_falloff_factor*colour_diffuse_factor;
	#else
	oColour.rgb+=gAmbientColour*colour_diffuse_factor;
	oColour.rgb+=colour_emissive;
	#endif
#else
	oColour.rgb += colour_emissive;
#endif
	oColour.a = alpha;