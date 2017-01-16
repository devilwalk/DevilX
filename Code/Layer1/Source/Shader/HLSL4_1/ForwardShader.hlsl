#include "Function.hlsl"
#ifndef OUTPUT_WORLD_POSITION
#define OUTPUT_WORLD_POSITION 0
#endif
#ifndef OUTPUT_WORLD_NORMAL
#define OUTPUT_WORLD_NORMAL 0
#endif
#ifndef OUTPUT_WORLD_TANGENT
#define OUTPUT_WORLD_TANGENT 0
#endif
#ifndef OUTPUT_MAIN_UV
#define OUTPUT_MAIN_UV 0
#endif
#ifndef OUTPUT_DIFFUSE
#define OUTPU_DIFFUSE 0
#endif
struct SVertexShaderInput
{
	float3 mPosition : SV_Position;
#if OUTPUT_WORLD_NORMAL
	float3 mNormal : NORMAL;
#endif
#if OUTPUT_WORLD_TANGENT
	float3 mTangent : TANGENT;
#endif
#if OUTPUT_MAIN_UV
	float2 mMainUV : TEXCOORD0;
#endif
#if OUTPUT_DIFFUSE
    float4 mDiffuse : DIFFUSE;
#endif
};
struct SVertexShaderOutput
{
	float4 mPosition : SV_Position;
#if OUTPUT_WORLD_POSITION
	float3 mWorldPosition : WORLD_POSITION;
#endif
#if OUTPUT_WORLD_NORMAL
	float3 mWorldNormal : WORLD_NORMAL;
#endif
#if OUTPUT_WORLD_TANGENT
	float3 mWorldTangent : WORLD_TANGENT;
#endif
#if OUTPUT_MAIN_UV
	float2 mMainUV : TEXCOORD0;
#endif
#if OUTPUT_DIFFUSE
    float4 mDiffuse : DIFFUSE;
#endif
};
SVertexShaderOutput vsMain(SVertexShaderInput input)
{
	SVertexShaderOutput output;
    float4 world_position = mul(gWorldMatrix, float4(input.mPosition, 1.0));
    output.mPosition = mul(gViewProjectionMatrix, world_position);
#if OUTPUT_WORLD_POSITION
	output.mWorldPosition = world_position.xyz;
#endif
#if OUTPUT_WORLD_NORMAL
	output.mWorldNormal = mul((float3x3)gWorldMatrix, input.mNormal);
#endif
#if OUTPUT_WORLD_TANGENT
	output.mWorldTangent = mul((float3x3)gWorldMatrix, input.mTangent);
#endif
#if OUTPUT_MAIN_UV
	output.mMainUV = input.mMainUV;
#endif
#if OUTPUT_DIFFUSE
	output.mDiffuse = input.mDiffuse;
#endif
	return output;
}
#ifndef USE_LIGHTING
#define USE_LIGHTING 0
#endif
#ifndef USE_DIRECTION_LIGHT
#define USE_DIRECTION_LIGHT 0
#endif
#ifndef USE_POINT_LIGHT
#define USE_POINT_LIGHT 0
#endif
#ifndef USE_SPOT_LIGHT
#define USE_SPOT_LIGHT 0
#endif
#ifndef USE_DIFFUSE_TEXTURE
#define USE_DIFFUSE_TEXTURE 0
#endif
#ifndef USE_NORMAL_TEXTURE
#define USE_NORMAL_TEXTURE 0
#endif
#ifndef USE_ALPHA_TEST
#define USE_ALPHA_TEST 0
#endif
#ifndef USE_SPECULAR
#define USE_SPECULAR 0
#endif
SamplerState gDiffuseSamplerState;
SamplerState gNormalSamplerState;
Texture2D<float4> gDiffuseTexture;
Texture2D<float4> gNormalTexture;
struct SPixelShaderOutput
{
	float4 mColour : SV_Target;
};
SPixelShaderOutput psMain(SVertexShaderOutput input)
{
    SPixelShaderOutput output = (SPixelShaderOutput)0;
	float3 colour_emissive = gEmissiveColour;
	float3 colour_diffuse_factor = gMainColour;
    float3 colour_specular_factor = gSpecularColour;
    float alpha = gAlpha;
#if OUTPUT_DIFFUSE
    colour_emissive *= input.mDiffuse.rgb;
    colour_diffuse_factor *= input.mDiffuse.rgb;
    alpha *= input.mDiffuse.a;
#endif
#if USE_DIFFUSE_TEXTURE
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;
	float diffuse_texture_alpha = diffuse_texture_colour.a;
	alpha *= diffuse_texture_alpha;
	colour_diffuse_factor *= diffuse_texture_colour;
	colour_emissive *= diffuse_texture_colour;
#endif
#if USE_ALPHA_TEST
	clip(alpha - gAlphaTestValue);
#endif
#if USE_LIGHTING
    #if USE_DIRECTION_LIGHT||USE_POINT_LIGHT||USE_SPOT_LIGHT
    float3 lighting_colour=0;
    float lighting_falloff_factor=1.0;
	float3 world_normal=normalize(input.mWorldNormal);
		#if USE_NORMAL_TEXTURE
	float4 normal_texture_sampler=gNormalTexture.Sample(gNormalSamplerState,input.mMainUV);
	float3 normal_texture_normal=normal_texture_sampler.xyz * 2.0-1.0;
	float3 world_tangent=normalize(input.mWorldTangent);
	float3 world_binormal=cross(world_normal,world_tangent);
	float3x3 tbn=float3x3(world_tangent,world_binormal,world_normal);
	world_normal=mul(tbn,normal_texture_normal);
		#endif
		#if USE_DIRECTION_LIGHT
	float3 vertex_to_light_direction = -gDirectionLightDirection;
    float3 light_diffuse_colour = gDirectionLightDiffuseColour;
    float3 light_specular_colour = gDirectionLightSpecularColour;
	    #elif USE_POINT_LIGHT
    float3 vertex_to_light = gPointLightPosition - input.mWorldPosition;
    lighting_falloff_factor=calcFalloffFactor(length(vertex_to_light),gPointLightStartFallOffDistance,gPointLightReciprocalRange);
	float3 vertex_to_light_direction = normalize(vertex_to_light);
    float3 light_diffuse_colour = gPointLightDiffuseColour;
    float3 light_specular_colour = gPointLightSpecularColour;
	    #elif USE_SPOT_LIGHT
    float3 vertex_to_light = gSpotLightPosition - input.mWorldPosition;
    float falloff_distance_factor=calcFalloffFactor(length(vertex_to_light),gSpotLightStartFallOffDistance,gSpotLightReciprocalRange);
	float3 vertex_to_light_direction = normalize(vertex_to_light);
    float falloff_angle_factor=calcFalloffFactor(dot(vertex_to_light_direction,gSpotLightDirection),gSpotLightCosInnerCornerHalfAngle,gSpotLightReciprocalDeltaCosHalfAngle);
    lighting_falloff_factor=falloff_distance_factor*falloff_angle_factor;
    float3 light_diffuse_colour = gSpotLightDiffuseColour;
    float3 light_specular_colour = gSpotLightSpecularColour;
	    #endif
	float lighting_diffuse_factor = calcDiffuseFactor(vertex_to_light_direction, world_normal);
    float3 lighting_diffuse_colour = light_diffuse_colour * lighting_diffuse_factor;
	lighting_colour+=lighting_diffuse_colour;
		#if USE_SPECULAR
	float lighting_specular_factor=calcSpecularFactor(vertex_to_light_direction,world_normal,input.mWorldPosition,getCameraPosition());
	float3 lighting_specular_colour=lighting_diffuse_factor > 0.0?pow(lighting_specular_factor,gSpecularPower) * light_specular_colour:0.0;
	lighting_colour+=lighting_specular_colour;
		#endif
    output.mColour.rgb+=lighting_colour*lighting_falloff_factor*colour_diffuse_factor;
	#else
	output.mColour.rgb += gAmbientColour * colour_diffuse_factor;
	output.mColour.rgb += colour_emissive;
	#endif
#else
	output.mColour.rgb += colour_emissive;
#endif
	output.mColour.a = alpha;
	return output;
}