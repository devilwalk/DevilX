	float3 colour_emissive = gEmissiveColour;
	float3 colour_diffuse_factor = gMainColour;
    float3 colour_specular_factor = gSpecularColour;
    float alpha = gAlpha;
#if OUTPUT_DIFFUSE
    colour_emissive *= iDiffuse.rgb;
    colour_diffuse_factor *= iDiffuse.rgb;
    alpha *= iDiffuse.a;
#endif//OUTPUT_DIFFUSE
#if USE_DIFFUSE_TEXTURE
	float4 diffuse_texture_sampler=SAMPLE_TEXTURE(Diffuse,iMainUV);
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;
	float diffuse_texture_alpha = diffuse_texture_sampler.a;
	alpha *= diffuse_texture_alpha;
	colour_diffuse_factor *= diffuse_texture_colour;
	colour_emissive *= diffuse_texture_colour;
#endif//USE_DIFFUSE_TEXTURE
#if USE_ALPHA_TEST
	if(alpha - gAlphaTestValue<0)discard;
#endif//USE_ALPHA_TEST
#if USE_LIGHTING
    #if USE_DIRECTION_LIGHT||USE_POINT_LIGHT||USE_SPOT_LIGHT
    float3 lighting_colour=0;
    float lighting_falloff_factor=1.0;
	float3 world_normal=normalize(iWorldNormal);
		#if USE_NORMAL_TEXTURE
	float4 normal_texture_sampler=SAMPLE_TEXTURE(Normal,iMainUV);
	float3 normal_texture_normal=normal_texture_sampler.xyz*2.0-1.0;
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
#define VERTEX_TO_CAMERA float3 vertex_to_camera=getCameraPosition()-iWorldPosition
#define VERTEX_TO_CAMERA_DIR float3 vertex_to_camera_direction=normalize(vertex_to_camera)
#define HALFWAY float3 halfway_vector=normalize(VERTEX_TO_CAMERA_DIR+vertex_to_light_direction)
#define N_DOT_L float n_dot_l=saturate(dot(world_normal,vertex_to_light_direction))
#define N_DOT_H float n_dot_h=saturate(dot(world_normal,halfway_vector))
#define N_DOT_V float n_dot_v=saturate(dot(world_normal,vertex_to_camera_direction))
		#if USE_LAMBERT_DIFFUSE_MODEL
	N_DOT_L;
	float light_diffuse_factor=calcLambertDiffuseFactor(n_dot_l);
		#elif USE_OREN_NAYAR_DIFFUSE_MODEL
		#elif USE_MINNAERT_DIFFUSE_MODEL
		#elif USE_DISNEY_DIFFUSE_MODEL
		#endif
		#if USE_PHONG_SPECULAR_MODEL
	VERTEX_TO_CAMERA;
	VERTEX_TO_CAMERA_DIR;
	float light_specular_factor=calcPhongSpecularFactor(-vertex_to_light_direction,world_normal,iWorldPosition,vertex_to_camera_direction);
		#elif USE_BLINNPHONG_SPECULAR_MODEL
	HALFWAY;
	N_DOT_H;
	float light_specular_factor=calcBlinnPhongSpecularFactor(n_dot_h,10.0);
		#elif USE_UE4_SPECULAR_MODEL
		#elif USE_COOK_TORRANCE_SPECULAR_MODEL
		#endif
		#if USE_DIFFUSE_MODEL
    float3 lighting_diffuse_colour = light_diffuse_colour*light_diffuse_factor;
	lighting_colour+=lighting_diffuse_colour;
		#endif
		#if USE_SPECULAR_MODEL
	float3 lighting_specular_colour=light_specular_colour*light_specular_factor;
	lighting_colour+=lighting_specular_colour;
		#endif
    oColour.rgb+=lighting_colour*lighting_falloff_factor*colour_diffuse_factor;
	#else//USE_DIRECTION_LIGHT||USE_POINT_LIGHT||USE_SPOT_LIGHT
		#if USE_CONSTANT_AMBIENT_MODEL
	oColour.rgb+=gAmbientColour*colour_diffuse_factor;
		#elif USE_HEMISPHERE_AMBIENT_MODEL
	float3 world_normal=normalize(iWorldNormal);
	oColour.rgb+=calcHemisphereAmbientFactor(world_normal)*gAmbientColour*colour_diffuse_factor;
		#elif USE_SPHERICALHARMONICS_AMBIENT_MODEL
	float3 world_normal=normalize(iWorldNormal);
	oColour.rgb+=calcSphericalHarmonicsAmbientFactor(world_normal)*gAmbientColour*colour_diffuse_factor;
		#endif
	oColour.rgb+=colour_emissive;
	#endif//USE_DIRECTION_LIGHT||USE_POINT_LIGHT||USE_SPOT_LIGHT
#else//USE_LIGHTING
	oColour.rgb += colour_emissive;
#endif//USE_LIGHTING
	oColour.a = alpha;