#ifndef GLSL_VERSION
	#define GLSL_VERSION 0
#endif
#ifndef GLSLES_VERSION
	#define GLSLES_VERSION 0
#endif
#ifndef DEVILX_HLSL_VERSION
	#define DEVILX_HLSL_VERSION 0
#endif
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)
	#define float2 vec2
	#define float3 vec3
	#define float4 vec4
	#define int2 ivec2
	#define int3 ivec3
	#define int4 ivec4
	#define uint2 int2
	#define uint3 int3
	#define uint4 int4
	#define float2x2 mat2
	#define float2x3 mat2x3
	#define float2x4 mat2x4
	#define float3x2 mat3x2
	#define float3x3 mat3
	#define float3x4 mat3x4
	#define float4x2 mat4x2
	#define float4x3 mat4x3
	#define float4x4 mat4
	#define cbuffer layout(shared) uniform
	#define lerp mix
#endif
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)||(DEVILX_HLSL_VERSION>=400)
	#define DECL_CB(cb) cbuffer cb{
	#define END_DECL };
	#define CB_MEMBER uniform
#else
	#define DECL_CB(cb)
	#define END_DECL
	#define CB_MEMBER
#endif
#if DEVILX_HLSL_VERSION
	#define SAMPLE_TEXTURE(tex_name,uv) g##tex_name##Texture.Sample(g##tex_name##SamplerState,uv)
#else
	#define SAMPLE_TEXTURE(tex_name,uv) texture(g##tex_name##Texture,uv)
#endif
