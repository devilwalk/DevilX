	oColour=iDiffuse;
#if USE_DIFFUSE_TEXTURE
#if USE_FONT_TEXTURE
	float4 diffuse_texture_colour=float4(float3(1.0),diffuse_texture_sampler.r);
#else
	diffuse_texture_colour=diffuse_texture_sampler;
#endif
	oColour*=diffuse_texture_colour;
#endif