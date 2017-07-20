#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::CDefinitionShader::CDefinitionShader()
{
ClearViewport_hlsl="#ifndef GLSL_VERSION\r\n\
	#define GLSL_VERSION 0\r\n\
#endif\r\n\
#ifndef GLSLES_VERSION\r\n\
	#define GLSLES_VERSION 0\r\n\
#endif\r\n\
#ifndef DEVILX_HLSL_VERSION\r\n\
	#define DEVILX_HLSL_VERSION 0\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)\r\n\
	#define float2 vec2\r\n\
	#define float3 vec3\r\n\
	#define float4 vec4\r\n\
	#define int2 ivec2\r\n\
	#define int3 ivec3\r\n\
	#define int4 ivec4\r\n\
	#define uint2 int2\r\n\
	#define uint3 int3\r\n\
	#define uint4 int4\r\n\
	#define float2x2 mat2\r\n\
	#define float2x3 mat2x3\r\n\
	#define float2x4 mat2x4\r\n\
	#define float3x2 mat3x2\r\n\
	#define float3x3 mat3\r\n\
	#define float3x4 mat3x4\r\n\
	#define float4x2 mat4x2\r\n\
	#define float4x3 mat4x3\r\n\
	#define float4x4 mat4\r\n\
	#define cbuffer layout(shared) uniform\r\n\
	#define lerp mix\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)||(DEVILX_HLSL_VERSION>=400)\r\n\
	#define DECL_CB(cb) cbuffer cb{\r\n\
	#define END_DECL };\r\n\
	#define CB_MEMBER uniform\r\n\
#else\r\n\
	#define DECL_CB(cb)\r\n\
	#define END_DECL\r\n\
	#define CB_MEMBER\r\n\
#endif\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) g##tex_name##Texture.Sample(g##tex_name##SamplerState,uv)\r\n\
#else\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) texture(g##tex_name##Texture,uv)\r\n\
#endif\r\n\
\r\n\
#if DEVILX_HLSL_VERSION==0\r\n\
float2 mul(float2 v,float2x2 m){return v*m;}\r\n\
float3 mul(float2 v,float3x2 m){return v*m;}\r\n\
float4 mul(float2 v,float4x2 m){return v*m;}\r\n\
float2 mul(float3 v,float2x3 m){return v*m;}\r\n\
float3 mul(float3 v,float3x3 m){return v*m;}\r\n\
float4 mul(float3 v,float4x3 m){return v*m;}\r\n\
float2 mul(float4 v,float2x4 m){return v*m;}\r\n\
float3 mul(float4 v,float3x4 m){return v*m;}\r\n\
float4 mul(float4 v,float4x4 m){return v*m;}\r\n\
float2 mul(float2x2 m,float2 v){return m*v;}\r\n\
float2 mul(float3x2 m,float3 v){return m*v;}\r\n\
float2 mul(float4x2 m,float4 v){return m*v;}\r\n\
float3 mul(float2x3 m,float2 v){return m*v;}\r\n\
float3 mul(float3x3 m,float3 v){return m*v;}\r\n\
float3 mul(float4x3 m,float4 v){return m*v;}\r\n\
float4 mul(float2x4 m,float2 v){return m*v;}\r\n\
float4 mul(float3x4 m,float3 v){return m*v;}\r\n\
float4 mul(float4x4 m,float4 v){return m*v;}\r\n\
float2x2 mul(float2x2 m0,float2x2 m1){return m0*m1;}\r\n\
float3x3 mul(float3x3 m0,float3x3 m1){return m0*m1;}\r\n\
float4x4 mul(float4x4 m0,float4x4 m1){return m0*m1;}\r\n\
float saturate(float v){return clamp(v,0.0,1.0);}\r\n\
float2 saturate(float2 v){return clamp(v,float2(0.0),float2(1.0));}\r\n\
float3 saturate(float3 v){return clamp(v,float3(0.0),float3(1.0));}\r\n\
float4 saturate(float4 v){return clamp(v,float4(0.0),float4(1.0));}\r\n\
#endif\r\n\
float3x3 convert(float4x4 v)\r\n\
{\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	return (float3x3)v;\r\n\
#else\r\n\
	return float3x3(v);\r\n\
#endif\r\n\
}\r\n\
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x,v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x,v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcHemisphereLightFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	float cos_the=dot(vertexToLightDirection,worldNormal);\r\n\
	return cos_the*0.5+0.5;\r\n\
}\r\n\
float calcLambertDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcPhongSpecularFactor(float3 lightToVertexDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 reflect_dir=reflect(lightToVertexDirection,worldNormal);\r\n\
	float factor=saturate(dot(reflect_dir,vertexToCameraDirection));\r\n\
	return factor;\r\n\
}\r\n\
float calcBlinnPhongSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 half_vector = normalize(vertexToCameraDirection + vertexToLightDirection);\r\n\
	float specular_factor = saturate(dot(half_vector, worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
float3 calcSphericalHarmonicsLightFactor(float3 worldNormal)\r\n\
{\r\n\
	const float c1=0.429043;\r\n\
	const float c2=0.511664;\r\n\
	const float c3=0.743125;\r\n\
	const float c4=0.886227;\r\n\
	const float c5=0.247708;\r\n\
	const float3 l00=float3(0.871297,0.875222,0.864470);\r\n\
	const float3 l1m1=float3(0.175058,0.245335,0.312891);\r\n\
	const float3 l10=float3(0.034675,0.036107,0.037362);\r\n\
	const float3 l11=float3(-0.004629,-0.029448,-0.048028);\r\n\
	const float3 l2m2=float3(-0.120535,-0.121160,-0.117507);\r\n\
	const float3 l2m1=float3(0.003242,0.003624,0.007511);\r\n\
	const float3 l20=float3(-0.028667,-0.024926,-0.020998);\r\n\
	const float3 l21=float3(-0.077539,-0.086325,-0.091591);\r\n\
	const float3 l22=float3(-0.161784,-0.191783,0.219152);\r\n\
	float3 factor=c1*l22*(worldNormal.x*worldNormal.x-worldNormal.y*worldNormal.y)\r\n\
	+c3*l20*worldNormal.z*worldNormal.z\r\n\
	+c4*l00\r\n\
	-c5*l20\r\n\
	+2.0*c1*l2m2*worldNormal.x*worldNormal.y\r\n\
	+2.0*c1*l21*worldNormal.x*worldNormal.z\r\n\
	+2.0*c1*l2m1*worldNormal.y*worldNormal.z\r\n\
	+2.0*c2*l11*worldNormal.x\r\n\
	+2.0*c2*l1m1*worldNormal.y\r\n\
	+2.0*c2*l10*worldNormal.z;\r\n\
	return factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
	float factor=saturate((current - begin) * reciprocalRange);\r\n\
    return 1.0 - factor*factor;\r\n\
}\r\n\
float3 encodeNormal(float3 normal)\r\n\
{\r\n\
	return normal / getMaxComponment(normal);\r\n\
}\r\n\
float2 getQuadPosition(int vertexID)\r\n\
{\r\n\
    float2 ret;\r\n\
    if(0==vertexID)\r\n\
        ret = float2(-1.0, 1.0);\r\n\
    else if(1==vertexID)\r\n\
        ret = float2(1.0, 1.0);\r\n\
    else if(2==vertexID)\r\n\
        ret = float2(-1.0, -1.0);\r\n\
    else\r\n\
        ret = float2(1.0, -1.0);\r\n\
    return ret;\r\n\
}\r\n\
\r\n\
\r\n\
DECL_CB(cbClearViewport)\r\n\
CB_MEMBER float4 gClearColour0;\r\n\
CB_MEMBER float4 gClearColour1;\r\n\
CB_MEMBER float4 gClearColour2;\r\n\
CB_MEMBER float4 gClearColour3;\r\n\
CB_MEMBER float4 gClearColour4;\r\n\
CB_MEMBER float4 gClearColour5;\r\n\
CB_MEMBER float4 gClearColour6;\r\n\
CB_MEMBER float4 gClearColour7;\r\n\
CB_MEMBER float gClearDepth;\r\n\
END_DECL\r\n\
\r\n\
void vsMain(uint vertexID : SV_VertexID\r\n\
, out float4 outPosition : SV_Position\r\n\
)\r\n\
{\r\n\
    float depth = gClearDepth;\r\n\
    outPosition = float4(getQuadPosition(vertexID), depth, 1.0);\r\n\
}\r\n\
void psMain(float4 position : SV_Position\r\n\
, out float4 outColour0 : SV_Target0\r\n\
, out float4 outColour1 : SV_Target1\r\n\
, out float4 outColour2 : SV_Target2\r\n\
, out float4 outColour3 : SV_Target3\r\n\
, out float4 outColour4 : SV_Target4\r\n\
, out float4 outColour5 : SV_Target5\r\n\
, out float4 outColour6 : SV_Target6\r\n\
, out float4 outColour7 : SV_Target7\r\n\
)\r\n\
{\r\n\
    outColour0 = gClearColour0;\r\n\
    outColour1 = gClearColour1;\r\n\
    outColour2 = gClearColour2;\r\n\
    outColour3 = gClearColour3;\r\n\
    outColour4 = gClearColour4;\r\n\
    outColour5 = gClearColour5;\r\n\
    outColour6 = gClearColour6;\r\n\
    outColour7 = gClearColour7;\r\n\
}\r\n\
\r\n\
";
ClearViewportPixel_glsl="#ifndef GLSL_VERSION\r\n\
	#define GLSL_VERSION 0\r\n\
#endif\r\n\
#ifndef GLSLES_VERSION\r\n\
	#define GLSLES_VERSION 0\r\n\
#endif\r\n\
#ifndef DEVILX_HLSL_VERSION\r\n\
	#define DEVILX_HLSL_VERSION 0\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)\r\n\
	#define float2 vec2\r\n\
	#define float3 vec3\r\n\
	#define float4 vec4\r\n\
	#define int2 ivec2\r\n\
	#define int3 ivec3\r\n\
	#define int4 ivec4\r\n\
	#define uint2 int2\r\n\
	#define uint3 int3\r\n\
	#define uint4 int4\r\n\
	#define float2x2 mat2\r\n\
	#define float2x3 mat2x3\r\n\
	#define float2x4 mat2x4\r\n\
	#define float3x2 mat3x2\r\n\
	#define float3x3 mat3\r\n\
	#define float3x4 mat3x4\r\n\
	#define float4x2 mat4x2\r\n\
	#define float4x3 mat4x3\r\n\
	#define float4x4 mat4\r\n\
	#define cbuffer layout(shared) uniform\r\n\
	#define lerp mix\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)||(DEVILX_HLSL_VERSION>=400)\r\n\
	#define DECL_CB(cb) cbuffer cb{\r\n\
	#define END_DECL };\r\n\
	#define CB_MEMBER uniform\r\n\
#else\r\n\
	#define DECL_CB(cb)\r\n\
	#define END_DECL\r\n\
	#define CB_MEMBER\r\n\
#endif\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) g##tex_name##Texture.Sample(g##tex_name##SamplerState,uv)\r\n\
#else\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) texture(g##tex_name##Texture,uv)\r\n\
#endif\r\n\
\r\n\
DECL_CB(cbClearViewport)\r\n\
CB_MEMBER float4 gClearColour0;\r\n\
CB_MEMBER float4 gClearColour1;\r\n\
CB_MEMBER float4 gClearColour2;\r\n\
CB_MEMBER float4 gClearColour3;\r\n\
CB_MEMBER float4 gClearColour4;\r\n\
CB_MEMBER float4 gClearColour5;\r\n\
CB_MEMBER float4 gClearColour6;\r\n\
CB_MEMBER float4 gClearColour7;\r\n\
CB_MEMBER float gClearDepth;\r\n\
END_DECL\r\n\
\r\n\
\r\n\
#if DEVILX_HLSL_VERSION==0\r\n\
float2 mul(float2 v,float2x2 m){return v*m;}\r\n\
float3 mul(float2 v,float3x2 m){return v*m;}\r\n\
float4 mul(float2 v,float4x2 m){return v*m;}\r\n\
float2 mul(float3 v,float2x3 m){return v*m;}\r\n\
float3 mul(float3 v,float3x3 m){return v*m;}\r\n\
float4 mul(float3 v,float4x3 m){return v*m;}\r\n\
float2 mul(float4 v,float2x4 m){return v*m;}\r\n\
float3 mul(float4 v,float3x4 m){return v*m;}\r\n\
float4 mul(float4 v,float4x4 m){return v*m;}\r\n\
float2 mul(float2x2 m,float2 v){return m*v;}\r\n\
float2 mul(float3x2 m,float3 v){return m*v;}\r\n\
float2 mul(float4x2 m,float4 v){return m*v;}\r\n\
float3 mul(float2x3 m,float2 v){return m*v;}\r\n\
float3 mul(float3x3 m,float3 v){return m*v;}\r\n\
float3 mul(float4x3 m,float4 v){return m*v;}\r\n\
float4 mul(float2x4 m,float2 v){return m*v;}\r\n\
float4 mul(float3x4 m,float3 v){return m*v;}\r\n\
float4 mul(float4x4 m,float4 v){return m*v;}\r\n\
float2x2 mul(float2x2 m0,float2x2 m1){return m0*m1;}\r\n\
float3x3 mul(float3x3 m0,float3x3 m1){return m0*m1;}\r\n\
float4x4 mul(float4x4 m0,float4x4 m1){return m0*m1;}\r\n\
float saturate(float v){return clamp(v,0.0,1.0);}\r\n\
float2 saturate(float2 v){return clamp(v,float2(0.0),float2(1.0));}\r\n\
float3 saturate(float3 v){return clamp(v,float3(0.0),float3(1.0));}\r\n\
float4 saturate(float4 v){return clamp(v,float4(0.0),float4(1.0));}\r\n\
#endif\r\n\
float3x3 convert(float4x4 v)\r\n\
{\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	return (float3x3)v;\r\n\
#else\r\n\
	return float3x3(v);\r\n\
#endif\r\n\
}\r\n\
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x,v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x,v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcHemisphereLightFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	float cos_the=dot(vertexToLightDirection,worldNormal);\r\n\
	return cos_the*0.5+0.5;\r\n\
}\r\n\
float calcLambertDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcPhongSpecularFactor(float3 lightToVertexDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 reflect_dir=reflect(lightToVertexDirection,worldNormal);\r\n\
	float factor=saturate(dot(reflect_dir,vertexToCameraDirection));\r\n\
	return factor;\r\n\
}\r\n\
float calcBlinnPhongSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 half_vector = normalize(vertexToCameraDirection + vertexToLightDirection);\r\n\
	float specular_factor = saturate(dot(half_vector, worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
float3 calcSphericalHarmonicsLightFactor(float3 worldNormal)\r\n\
{\r\n\
	const float c1=0.429043;\r\n\
	const float c2=0.511664;\r\n\
	const float c3=0.743125;\r\n\
	const float c4=0.886227;\r\n\
	const float c5=0.247708;\r\n\
	const float3 l00=float3(0.871297,0.875222,0.864470);\r\n\
	const float3 l1m1=float3(0.175058,0.245335,0.312891);\r\n\
	const float3 l10=float3(0.034675,0.036107,0.037362);\r\n\
	const float3 l11=float3(-0.004629,-0.029448,-0.048028);\r\n\
	const float3 l2m2=float3(-0.120535,-0.121160,-0.117507);\r\n\
	const float3 l2m1=float3(0.003242,0.003624,0.007511);\r\n\
	const float3 l20=float3(-0.028667,-0.024926,-0.020998);\r\n\
	const float3 l21=float3(-0.077539,-0.086325,-0.091591);\r\n\
	const float3 l22=float3(-0.161784,-0.191783,0.219152);\r\n\
	float3 factor=c1*l22*(worldNormal.x*worldNormal.x-worldNormal.y*worldNormal.y)\r\n\
	+c3*l20*worldNormal.z*worldNormal.z\r\n\
	+c4*l00\r\n\
	-c5*l20\r\n\
	+2.0*c1*l2m2*worldNormal.x*worldNormal.y\r\n\
	+2.0*c1*l21*worldNormal.x*worldNormal.z\r\n\
	+2.0*c1*l2m1*worldNormal.y*worldNormal.z\r\n\
	+2.0*c2*l11*worldNormal.x\r\n\
	+2.0*c2*l1m1*worldNormal.y\r\n\
	+2.0*c2*l10*worldNormal.z;\r\n\
	return factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
	float factor=saturate((current - begin) * reciprocalRange);\r\n\
    return 1.0 - factor*factor;\r\n\
}\r\n\
float3 encodeNormal(float3 normal)\r\n\
{\r\n\
	return normal / getMaxComponment(normal);\r\n\
}\r\n\
float2 getQuadPosition(int vertexID)\r\n\
{\r\n\
    float2 ret;\r\n\
    if(0==vertexID)\r\n\
        ret = float2(-1.0, 1.0);\r\n\
    else if(1==vertexID)\r\n\
        ret = float2(1.0, 1.0);\r\n\
    else if(2==vertexID)\r\n\
        ret = float2(-1.0, -1.0);\r\n\
    else\r\n\
        ret = float2(1.0, -1.0);\r\n\
    return ret;\r\n\
}\r\n\
\r\n\
layout(location=0) out float4 outColour0;\r\n\
layout(location=1) out float4 outColour1;\r\n\
layout(location=2) out float4 outColour2;\r\n\
layout(location=3) out float4 outColour3;\r\n\
#if GLSL_VERSION>400\r\n\
layout(location=4) out float4 outColour4;\r\n\
layout(location=5) out float4 outColour5;\r\n\
layout(location=6) out float4 outColour6;\r\n\
layout(location=7) out float4 outColour7;\r\n\
#endif\r\n\
void main()\r\n\
{\r\n\
    outColour0 = gClearColour0;\r\n\
    outColour1 = gClearColour1;\r\n\
    outColour2 = gClearColour2;\r\n\
    outColour3 = gClearColour3;\r\n\
#if GLSL_VERSION>400\r\n\
    outColour4 = gClearColour4;\r\n\
    outColour5 = gClearColour5;\r\n\
    outColour6 = gClearColour6;\r\n\
    outColour7 = gClearColour7;\r\n\
#endif\r\n\
}\r\n\
\r\n\
";
ClearViewportVertex_glsl="#ifndef GLSL_VERSION\r\n\
	#define GLSL_VERSION 0\r\n\
#endif\r\n\
#ifndef GLSLES_VERSION\r\n\
	#define GLSLES_VERSION 0\r\n\
#endif\r\n\
#ifndef DEVILX_HLSL_VERSION\r\n\
	#define DEVILX_HLSL_VERSION 0\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)\r\n\
	#define float2 vec2\r\n\
	#define float3 vec3\r\n\
	#define float4 vec4\r\n\
	#define int2 ivec2\r\n\
	#define int3 ivec3\r\n\
	#define int4 ivec4\r\n\
	#define uint2 int2\r\n\
	#define uint3 int3\r\n\
	#define uint4 int4\r\n\
	#define float2x2 mat2\r\n\
	#define float2x3 mat2x3\r\n\
	#define float2x4 mat2x4\r\n\
	#define float3x2 mat3x2\r\n\
	#define float3x3 mat3\r\n\
	#define float3x4 mat3x4\r\n\
	#define float4x2 mat4x2\r\n\
	#define float4x3 mat4x3\r\n\
	#define float4x4 mat4\r\n\
	#define cbuffer layout(shared) uniform\r\n\
	#define lerp mix\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)||(DEVILX_HLSL_VERSION>=400)\r\n\
	#define DECL_CB(cb) cbuffer cb{\r\n\
	#define END_DECL };\r\n\
	#define CB_MEMBER uniform\r\n\
#else\r\n\
	#define DECL_CB(cb)\r\n\
	#define END_DECL\r\n\
	#define CB_MEMBER\r\n\
#endif\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) g##tex_name##Texture.Sample(g##tex_name##SamplerState,uv)\r\n\
#else\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) texture(g##tex_name##Texture,uv)\r\n\
#endif\r\n\
\r\n\
DECL_CB(cbClearViewport)\r\n\
CB_MEMBER float4 gClearColour0;\r\n\
CB_MEMBER float4 gClearColour1;\r\n\
CB_MEMBER float4 gClearColour2;\r\n\
CB_MEMBER float4 gClearColour3;\r\n\
CB_MEMBER float4 gClearColour4;\r\n\
CB_MEMBER float4 gClearColour5;\r\n\
CB_MEMBER float4 gClearColour6;\r\n\
CB_MEMBER float4 gClearColour7;\r\n\
CB_MEMBER float gClearDepth;\r\n\
END_DECL\r\n\
\r\n\
\r\n\
#if DEVILX_HLSL_VERSION==0\r\n\
float2 mul(float2 v,float2x2 m){return v*m;}\r\n\
float3 mul(float2 v,float3x2 m){return v*m;}\r\n\
float4 mul(float2 v,float4x2 m){return v*m;}\r\n\
float2 mul(float3 v,float2x3 m){return v*m;}\r\n\
float3 mul(float3 v,float3x3 m){return v*m;}\r\n\
float4 mul(float3 v,float4x3 m){return v*m;}\r\n\
float2 mul(float4 v,float2x4 m){return v*m;}\r\n\
float3 mul(float4 v,float3x4 m){return v*m;}\r\n\
float4 mul(float4 v,float4x4 m){return v*m;}\r\n\
float2 mul(float2x2 m,float2 v){return m*v;}\r\n\
float2 mul(float3x2 m,float3 v){return m*v;}\r\n\
float2 mul(float4x2 m,float4 v){return m*v;}\r\n\
float3 mul(float2x3 m,float2 v){return m*v;}\r\n\
float3 mul(float3x3 m,float3 v){return m*v;}\r\n\
float3 mul(float4x3 m,float4 v){return m*v;}\r\n\
float4 mul(float2x4 m,float2 v){return m*v;}\r\n\
float4 mul(float3x4 m,float3 v){return m*v;}\r\n\
float4 mul(float4x4 m,float4 v){return m*v;}\r\n\
float2x2 mul(float2x2 m0,float2x2 m1){return m0*m1;}\r\n\
float3x3 mul(float3x3 m0,float3x3 m1){return m0*m1;}\r\n\
float4x4 mul(float4x4 m0,float4x4 m1){return m0*m1;}\r\n\
float saturate(float v){return clamp(v,0.0,1.0);}\r\n\
float2 saturate(float2 v){return clamp(v,float2(0.0),float2(1.0));}\r\n\
float3 saturate(float3 v){return clamp(v,float3(0.0),float3(1.0));}\r\n\
float4 saturate(float4 v){return clamp(v,float4(0.0),float4(1.0));}\r\n\
#endif\r\n\
float3x3 convert(float4x4 v)\r\n\
{\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	return (float3x3)v;\r\n\
#else\r\n\
	return float3x3(v);\r\n\
#endif\r\n\
}\r\n\
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x,v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x,v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcHemisphereLightFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	float cos_the=dot(vertexToLightDirection,worldNormal);\r\n\
	return cos_the*0.5+0.5;\r\n\
}\r\n\
float calcLambertDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcPhongSpecularFactor(float3 lightToVertexDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 reflect_dir=reflect(lightToVertexDirection,worldNormal);\r\n\
	float factor=saturate(dot(reflect_dir,vertexToCameraDirection));\r\n\
	return factor;\r\n\
}\r\n\
float calcBlinnPhongSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 half_vector = normalize(vertexToCameraDirection + vertexToLightDirection);\r\n\
	float specular_factor = saturate(dot(half_vector, worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
float3 calcSphericalHarmonicsLightFactor(float3 worldNormal)\r\n\
{\r\n\
	const float c1=0.429043;\r\n\
	const float c2=0.511664;\r\n\
	const float c3=0.743125;\r\n\
	const float c4=0.886227;\r\n\
	const float c5=0.247708;\r\n\
	const float3 l00=float3(0.871297,0.875222,0.864470);\r\n\
	const float3 l1m1=float3(0.175058,0.245335,0.312891);\r\n\
	const float3 l10=float3(0.034675,0.036107,0.037362);\r\n\
	const float3 l11=float3(-0.004629,-0.029448,-0.048028);\r\n\
	const float3 l2m2=float3(-0.120535,-0.121160,-0.117507);\r\n\
	const float3 l2m1=float3(0.003242,0.003624,0.007511);\r\n\
	const float3 l20=float3(-0.028667,-0.024926,-0.020998);\r\n\
	const float3 l21=float3(-0.077539,-0.086325,-0.091591);\r\n\
	const float3 l22=float3(-0.161784,-0.191783,0.219152);\r\n\
	float3 factor=c1*l22*(worldNormal.x*worldNormal.x-worldNormal.y*worldNormal.y)\r\n\
	+c3*l20*worldNormal.z*worldNormal.z\r\n\
	+c4*l00\r\n\
	-c5*l20\r\n\
	+2.0*c1*l2m2*worldNormal.x*worldNormal.y\r\n\
	+2.0*c1*l21*worldNormal.x*worldNormal.z\r\n\
	+2.0*c1*l2m1*worldNormal.y*worldNormal.z\r\n\
	+2.0*c2*l11*worldNormal.x\r\n\
	+2.0*c2*l1m1*worldNormal.y\r\n\
	+2.0*c2*l10*worldNormal.z;\r\n\
	return factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
	float factor=saturate((current - begin) * reciprocalRange);\r\n\
    return 1.0 - factor*factor;\r\n\
}\r\n\
float3 encodeNormal(float3 normal)\r\n\
{\r\n\
	return normal / getMaxComponment(normal);\r\n\
}\r\n\
float2 getQuadPosition(int vertexID)\r\n\
{\r\n\
    float2 ret;\r\n\
    if(0==vertexID)\r\n\
        ret = float2(-1.0, 1.0);\r\n\
    else if(1==vertexID)\r\n\
        ret = float2(1.0, 1.0);\r\n\
    else if(2==vertexID)\r\n\
        ret = float2(-1.0, -1.0);\r\n\
    else\r\n\
        ret = float2(1.0, -1.0);\r\n\
    return ret;\r\n\
}\r\n\
\r\n\
void main()\r\n\
{\r\n\
    float depth = gClearDepth;\r\n\
	gl_Position= float4(getQuadPosition(gl_VertexID), depth, 1.0);\r\n\
}\r\n\
\r\n\
\r\n\
";
ForwardPixelShader_glsl="#ifndef GLSL_VERSION\r\n\
	#define GLSL_VERSION 0\r\n\
#endif\r\n\
#ifndef GLSLES_VERSION\r\n\
	#define GLSLES_VERSION 0\r\n\
#endif\r\n\
#ifndef DEVILX_HLSL_VERSION\r\n\
	#define DEVILX_HLSL_VERSION 0\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)\r\n\
	#define float2 vec2\r\n\
	#define float3 vec3\r\n\
	#define float4 vec4\r\n\
	#define int2 ivec2\r\n\
	#define int3 ivec3\r\n\
	#define int4 ivec4\r\n\
	#define uint2 int2\r\n\
	#define uint3 int3\r\n\
	#define uint4 int4\r\n\
	#define float2x2 mat2\r\n\
	#define float2x3 mat2x3\r\n\
	#define float2x4 mat2x4\r\n\
	#define float3x2 mat3x2\r\n\
	#define float3x3 mat3\r\n\
	#define float3x4 mat3x4\r\n\
	#define float4x2 mat4x2\r\n\
	#define float4x3 mat4x3\r\n\
	#define float4x4 mat4\r\n\
	#define cbuffer layout(shared) uniform\r\n\
	#define lerp mix\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)||(DEVILX_HLSL_VERSION>=400)\r\n\
	#define DECL_CB(cb) cbuffer cb{\r\n\
	#define END_DECL };\r\n\
	#define CB_MEMBER uniform\r\n\
#else\r\n\
	#define DECL_CB(cb)\r\n\
	#define END_DECL\r\n\
	#define CB_MEMBER\r\n\
#endif\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) g##tex_name##Texture.Sample(g##tex_name##SamplerState,uv)\r\n\
#else\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) texture(g##tex_name##Texture,uv)\r\n\
#endif\r\n\
\r\n\
#if DEVILX_HLSL_VERSION==0\r\n\
float2 mul(float2 v,float2x2 m){return v*m;}\r\n\
float3 mul(float2 v,float3x2 m){return v*m;}\r\n\
float4 mul(float2 v,float4x2 m){return v*m;}\r\n\
float2 mul(float3 v,float2x3 m){return v*m;}\r\n\
float3 mul(float3 v,float3x3 m){return v*m;}\r\n\
float4 mul(float3 v,float4x3 m){return v*m;}\r\n\
float2 mul(float4 v,float2x4 m){return v*m;}\r\n\
float3 mul(float4 v,float3x4 m){return v*m;}\r\n\
float4 mul(float4 v,float4x4 m){return v*m;}\r\n\
float2 mul(float2x2 m,float2 v){return m*v;}\r\n\
float2 mul(float3x2 m,float3 v){return m*v;}\r\n\
float2 mul(float4x2 m,float4 v){return m*v;}\r\n\
float3 mul(float2x3 m,float2 v){return m*v;}\r\n\
float3 mul(float3x3 m,float3 v){return m*v;}\r\n\
float3 mul(float4x3 m,float4 v){return m*v;}\r\n\
float4 mul(float2x4 m,float2 v){return m*v;}\r\n\
float4 mul(float3x4 m,float3 v){return m*v;}\r\n\
float4 mul(float4x4 m,float4 v){return m*v;}\r\n\
float2x2 mul(float2x2 m0,float2x2 m1){return m0*m1;}\r\n\
float3x3 mul(float3x3 m0,float3x3 m1){return m0*m1;}\r\n\
float4x4 mul(float4x4 m0,float4x4 m1){return m0*m1;}\r\n\
float saturate(float v){return clamp(v,0.0,1.0);}\r\n\
float2 saturate(float2 v){return clamp(v,float2(0.0),float2(1.0));}\r\n\
float3 saturate(float3 v){return clamp(v,float3(0.0),float3(1.0));}\r\n\
float4 saturate(float4 v){return clamp(v,float4(0.0),float4(1.0));}\r\n\
#endif\r\n\
float3x3 convert(float4x4 v)\r\n\
{\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	return (float3x3)v;\r\n\
#else\r\n\
	return float3x3(v);\r\n\
#endif\r\n\
}\r\n\
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x,v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x,v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcHemisphereLightFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	float cos_the=dot(vertexToLightDirection,worldNormal);\r\n\
	return cos_the*0.5+0.5;\r\n\
}\r\n\
float calcLambertDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcPhongSpecularFactor(float3 lightToVertexDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 reflect_dir=reflect(lightToVertexDirection,worldNormal);\r\n\
	float factor=saturate(dot(reflect_dir,vertexToCameraDirection));\r\n\
	return factor;\r\n\
}\r\n\
float calcBlinnPhongSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 half_vector = normalize(vertexToCameraDirection + vertexToLightDirection);\r\n\
	float specular_factor = saturate(dot(half_vector, worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
float3 calcSphericalHarmonicsLightFactor(float3 worldNormal)\r\n\
{\r\n\
	const float c1=0.429043;\r\n\
	const float c2=0.511664;\r\n\
	const float c3=0.743125;\r\n\
	const float c4=0.886227;\r\n\
	const float c5=0.247708;\r\n\
	const float3 l00=float3(0.871297,0.875222,0.864470);\r\n\
	const float3 l1m1=float3(0.175058,0.245335,0.312891);\r\n\
	const float3 l10=float3(0.034675,0.036107,0.037362);\r\n\
	const float3 l11=float3(-0.004629,-0.029448,-0.048028);\r\n\
	const float3 l2m2=float3(-0.120535,-0.121160,-0.117507);\r\n\
	const float3 l2m1=float3(0.003242,0.003624,0.007511);\r\n\
	const float3 l20=float3(-0.028667,-0.024926,-0.020998);\r\n\
	const float3 l21=float3(-0.077539,-0.086325,-0.091591);\r\n\
	const float3 l22=float3(-0.161784,-0.191783,0.219152);\r\n\
	float3 factor=c1*l22*(worldNormal.x*worldNormal.x-worldNormal.y*worldNormal.y)\r\n\
	+c3*l20*worldNormal.z*worldNormal.z\r\n\
	+c4*l00\r\n\
	-c5*l20\r\n\
	+2.0*c1*l2m2*worldNormal.x*worldNormal.y\r\n\
	+2.0*c1*l21*worldNormal.x*worldNormal.z\r\n\
	+2.0*c1*l2m1*worldNormal.y*worldNormal.z\r\n\
	+2.0*c2*l11*worldNormal.x\r\n\
	+2.0*c2*l1m1*worldNormal.y\r\n\
	+2.0*c2*l10*worldNormal.z;\r\n\
	return factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
	float factor=saturate((current - begin) * reciprocalRange);\r\n\
    return 1.0 - factor*factor;\r\n\
}\r\n\
float3 encodeNormal(float3 normal)\r\n\
{\r\n\
	return normal / getMaxComponment(normal);\r\n\
}\r\n\
float2 getQuadPosition(int vertexID)\r\n\
{\r\n\
    float2 ret;\r\n\
    if(0==vertexID)\r\n\
        ret = float2(-1.0, 1.0);\r\n\
    else if(1==vertexID)\r\n\
        ret = float2(1.0, 1.0);\r\n\
    else if(2==vertexID)\r\n\
        ret = float2(-1.0, -1.0);\r\n\
    else\r\n\
        ret = float2(1.0, -1.0);\r\n\
    return ret;\r\n\
}\r\n\
\r\n\
\r\n\
\r\n\
DECL_CB(cbSystem)\r\n\
CB_MEMBER float gFrameTimeInSeconds;\r\n\
CB_MEMBER float gInverseFrameTimeInSeconds;\r\n\
END_DECL\r\n\
DECL_CB(cbRenderTarget)\r\n\
CB_MEMBER float2 gRenderTargetSizeInPixel;\r\n\
CB_MEMBER float2 gInverseRenderTargetSizeInPixel;\r\n\
END_DECL\r\n\
DECL_CB(cbViewport)\r\n\
CB_MEMBER float2 gViewportSizeInPixel;\r\n\
CB_MEMBER float2 gInverseViewportSizeInPixel;\r\n\
END_DECL\r\n\
DECL_CB(cbCamera)\r\n\
CB_MEMBER float4x4 gViewMatrix;\r\n\
CB_MEMBER float4x4 gInverseViewMatrix;\r\n\
CB_MEMBER float4x4 gProjectionMatrix;\r\n\
CB_MEMBER float4x4 gInverseProjectionMatrix;\r\n\
CB_MEMBER float4x4 gViewProjectionMatrix;\r\n\
CB_MEMBER float4x4 gInverseViewProjectionMatrix;\r\n\
CB_MEMBER float gFarDistance;\r\n\
CB_MEMBER float gInverseFarDistance;\r\n\
END_DECL\r\n\
DECL_CB(cbScene)\r\n\
CB_MEMBER float3 gAmbientColour;\r\n\
CB_MEMBER float3 gSkyColour;\r\n\
CB_MEMBER float3 gGroundColour;\r\n\
CB_MEMBER float3 gSkyLightDirection;\r\n\
END_DECL\r\n\
\r\n\
\r\n\
float3 getCameraPosition()\r\n\
{\r\n\
	return getCameraPosition(gViewMatrix);\r\n\
}\r\n\
float3 getCameraDirection()\r\n\
{\r\n\
	return getCameraDirection(gViewMatrix);\r\n\
}\r\n\
float3 getCameraUp()\r\n\
{\r\n\
	return getCameraUp(gViewMatrix);\r\n\
}\r\n\
float3 getCameraRight()\r\n\
{\r\n\
	return getCameraRight(gViewMatrix);\r\n\
}\r\n\
float3 calcHemisphereLightColour(float3 worldNormal)\r\n\
{\r\n\
	float3 factor=calcHemisphereLightFactor(-gSkyLightDirection,worldNormal);\r\n\
	return lerp(gGroundColour,gSkyColour,factor);\r\n\
}\r\n\
\r\n\
\r\n\
\r\n\
\r\n\
DECL_CB(cbObjectTransform)\r\n\
CB_MEMBER float4x4 gWorldMatrix;\r\n\
END_DECL\r\n\
DECL_CB(cbObjectMaterial)\r\n\
CB_MEMBER float3 gMainColour;\r\n\
CB_MEMBER float gAlpha;\r\n\
CB_MEMBER float3 gSpecularColour;\r\n\
CB_MEMBER float gSpecularPower;\r\n\
CB_MEMBER float3 gEmissiveColour;\r\n\
CB_MEMBER float gAlphaTestValue;\r\n\
END_DECL\r\n\
\r\n\
\r\n\
DECL_CB(cbDirectionLight)\r\n\
CB_MEMBER float3 gDirectionLightDiffuseColour;\r\n\
CB_MEMBER float3 gDirectionLightSpecularColour;\r\n\
CB_MEMBER float3 gDirectionLightDirection;\r\n\
END_DECL\r\n\
DECL_CB(cbPointLight)\r\n\
CB_MEMBER float3 gPointLightDiffuseColour;\r\n\
CB_MEMBER float3 gPointLightSpecularColour;\r\n\
CB_MEMBER float3 gPointLightPosition;\r\n\
CB_MEMBER float gPointLightReciprocalRange;\r\n\
CB_MEMBER float gPointLightStartFallOffDistance;\r\n\
END_DECL\r\n\
DECL_CB(cbSpotLight)\r\n\
CB_MEMBER float3 gSpotLightDiffuseColour;\r\n\
CB_MEMBER float3 gSpotLightSpecularColour;\r\n\
CB_MEMBER float3 gSpotLightDirection;\r\n\
CB_MEMBER float3 gSpotLightPosition;\r\n\
CB_MEMBER float gSpotLightReciprocalRange;\r\n\
CB_MEMBER float gSpotLightStartFallOffDistance;\r\n\
CB_MEMBER float gSpotLightCosInnerCornerHalfAngle;\r\n\
CB_MEMBER float gSpotLightReciprocalDeltaCosHalfAngle;\r\n\
END_DECL\r\n\
\r\n\
\r\n\
#ifndef OUTPUT_WORLD_POSITION\r\n\
#define OUTPUT_WORLD_POSITION 0\r\n\
#endif\r\n\
#ifndef OUTPUT_WORLD_NORMAL\r\n\
#define OUTPUT_WORLD_NORMAL 0\r\n\
#endif\r\n\
#ifndef OUTPUT_WORLD_TANGENT\r\n\
#define OUTPUT_WORLD_TANGENT 0\r\n\
#endif\r\n\
#ifndef OUTPUT_MAIN_UV\r\n\
#define OUTPUT_MAIN_UV 0\r\n\
#endif\r\n\
#ifndef OUTPUT_DIFFUSE\r\n\
#define OUTPU_DIFFUSE 0\r\n\
#endif\r\n\
#ifndef USE_LIGHTING\r\n\
#define USE_LIGHTING 0\r\n\
#endif\r\n\
#ifndef USE_DIRECTION_LIGHT\r\n\
#define USE_DIRECTION_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_POINT_LIGHT\r\n\
#define USE_POINT_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_SPOT_LIGHT\r\n\
#define USE_SPOT_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_NORMAL_TEXTURE\r\n\
#define USE_NORMAL_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_ALPHA_TEST\r\n\
#define USE_ALPHA_TEST 0\r\n\
#endif\r\n\
#ifndef USE_SPECULAR\r\n\
#define USE_SPECULAR 0\r\n\
#endif\r\n\
\r\n\
\r\n\
\r\n\
\r\n\
#if OUTPUT_WORLD_POSITION\r\n\
in float3 gWorldPositionPS;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_NORMAL\r\n\
in float3 gWorldNormalPS;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
in float3 gWorldTangentPS;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
in float2 gMainUVPS;\r\n\
#endif\r\n\
#if OUTPUT_DIFFUSE\r\n\
in float4 gDiffusePS;\r\n\
#endif\r\n\
sampler2D gDiffuseTexture;\r\n\
sampler2D gNormalTexture;\r\n\
out float4 gFragColour;\r\n\
void main()\r\n\
{\r\n\
#define iWorldPosition gWorldPositionPS\r\n\
#define iWorldNormal gWorldNormalPS\r\n\
#define iWorldTangent gWorldTangentPS\r\n\
#define iMainUV gMainUVPS\r\n\
#define iDiffuse gDiffusePS\r\n\
#define oColour gFragColour\r\n\
	float3 colour_emissive = gEmissiveColour;\r\n\
	float3 colour_diffuse_factor = gMainColour;\r\n\
    float3 colour_specular_factor = gSpecularColour;\r\n\
    float alpha = gAlpha;\r\n\
#if OUTPUT_DIFFUSE\r\n\
    colour_emissive *= iDiffuse.rgb;\r\n\
    colour_diffuse_factor *= iDiffuse.rgb;\r\n\
    alpha *= iDiffuse.a;\r\n\
#endif\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler=SAMPLE_TEXTURE(Diffuse,iMainUV);\r\n\
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;\r\n\
	float diffuse_texture_alpha = diffuse_texture_sampler.a;\r\n\
	alpha *= diffuse_texture_alpha;\r\n\
	colour_diffuse_factor *= diffuse_texture_colour;\r\n\
	colour_emissive *= diffuse_texture_colour;\r\n\
#endif\r\n\
#if USE_ALPHA_TEST\r\n\
	if(alpha - gAlphaTestValue<0)discard;\r\n\
#endif\r\n\
#if USE_LIGHTING\r\n\
    #if USE_DIRECTION_LIGHT||USE_POINT_LIGHT||USE_SPOT_LIGHT\r\n\
    float3 lighting_colour=0;\r\n\
    float lighting_falloff_factor=1.0;\r\n\
	float3 world_normal=normalize(iWorldNormal);\r\n\
		#if USE_NORMAL_TEXTURE\r\n\
	float4 normal_texture_sampler=SAMPLE_TEXTURE(Normal,iMainUV);\r\n\
	float3 normal_texture_normal=normal_texture_sampler.xyz * 2.0-1.0;\r\n\
	float3 world_tangent=normalize(iWorldTangent);\r\n\
	float3 world_binormal=cross(world_normal,world_tangent);\r\n\
	float3x3 tbn=float3x3(world_tangent,world_binormal,world_normal);\r\n\
	world_normal=mul(tbn,normal_texture_normal);\r\n\
		#endif\r\n\
		#if USE_DIRECTION_LIGHT\r\n\
	float3 vertex_to_light_direction = -gDirectionLightDirection;\r\n\
    float3 light_diffuse_colour = gDirectionLightDiffuseColour;\r\n\
    float3 light_specular_colour = gDirectionLightSpecularColour;\r\n\
	    #elif USE_POINT_LIGHT\r\n\
    float3 vertex_to_light = gPointLightPosition - iWorldPosition;\r\n\
    lighting_falloff_factor=calcFalloffFactor(length(vertex_to_light),gPointLightStartFallOffDistance,gPointLightReciprocalRange);\r\n\
	float3 vertex_to_light_direction = normalize(vertex_to_light);\r\n\
    float3 light_diffuse_colour = gPointLightDiffuseColour;\r\n\
    float3 light_specular_colour = gPointLightSpecularColour;\r\n\
	    #elif USE_SPOT_LIGHT\r\n\
    float3 vertex_to_light = gSpotLightPosition - iWorldPosition;\r\n\
    float falloff_distance_factor=calcFalloffFactor(length(vertex_to_light),gSpotLightStartFallOffDistance,gSpotLightReciprocalRange);\r\n\
	float3 vertex_to_light_direction = normalize(vertex_to_light);\r\n\
    float falloff_angle_factor=calcFalloffFactor(dot(vertex_to_light_direction,gSpotLightDirection),gSpotLightCosInnerCornerHalfAngle,gSpotLightReciprocalDeltaCosHalfAngle);\r\n\
    lighting_falloff_factor=falloff_distance_factor*falloff_angle_factor;\r\n\
    float3 light_diffuse_colour = gSpotLightDiffuseColour;\r\n\
    float3 light_specular_colour = gSpotLightSpecularColour;\r\n\
	    #endif\r\n\
	float lighting_diffuse_factor = calcDiffuseFactor(vertex_to_light_direction, world_normal);\r\n\
    float3 lighting_diffuse_colour = light_diffuse_colour * lighting_diffuse_factor;\r\n\
	lighting_colour+=lighting_diffuse_colour;\r\n\
		#if USE_SPECULAR\r\n\
	float lighting_specular_factor=calcSpecularFactor(vertex_to_light_direction,world_normal,iWorldPosition,getCameraPosition());\r\n\
	float3 lighting_specular_colour=lighting_diffuse_factor > 0.0?pow(lighting_specular_factor,gSpecularPower) * light_specular_colour:0.0;\r\n\
	lighting_colour+=lighting_specular_colour;\r\n\
		#endif\r\n\
    oColour.rgb+=lighting_colour*lighting_falloff_factor*colour_diffuse_factor;\r\n\
	#else\r\n\
	oColour.rgb+=gAmbientColour*colour_diffuse_factor;\r\n\
	oColour.rgb+=colour_emissive;\r\n\
	#endif\r\n\
#else\r\n\
	oColour.rgb += colour_emissive;\r\n\
#endif\r\n\
	oColour.a = alpha;\r\n\
}\r\n\
\r\n\
";
ForwardShader_hlsl="#ifndef GLSL_VERSION\r\n\
	#define GLSL_VERSION 0\r\n\
#endif\r\n\
#ifndef GLSLES_VERSION\r\n\
	#define GLSLES_VERSION 0\r\n\
#endif\r\n\
#ifndef DEVILX_HLSL_VERSION\r\n\
	#define DEVILX_HLSL_VERSION 0\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)\r\n\
	#define float2 vec2\r\n\
	#define float3 vec3\r\n\
	#define float4 vec4\r\n\
	#define int2 ivec2\r\n\
	#define int3 ivec3\r\n\
	#define int4 ivec4\r\n\
	#define uint2 int2\r\n\
	#define uint3 int3\r\n\
	#define uint4 int4\r\n\
	#define float2x2 mat2\r\n\
	#define float2x3 mat2x3\r\n\
	#define float2x4 mat2x4\r\n\
	#define float3x2 mat3x2\r\n\
	#define float3x3 mat3\r\n\
	#define float3x4 mat3x4\r\n\
	#define float4x2 mat4x2\r\n\
	#define float4x3 mat4x3\r\n\
	#define float4x4 mat4\r\n\
	#define cbuffer layout(shared) uniform\r\n\
	#define lerp mix\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)||(DEVILX_HLSL_VERSION>=400)\r\n\
	#define DECL_CB(cb) cbuffer cb{\r\n\
	#define END_DECL };\r\n\
	#define CB_MEMBER uniform\r\n\
#else\r\n\
	#define DECL_CB(cb)\r\n\
	#define END_DECL\r\n\
	#define CB_MEMBER\r\n\
#endif\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) g##tex_name##Texture.Sample(g##tex_name##SamplerState,uv)\r\n\
#else\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) texture(g##tex_name##Texture,uv)\r\n\
#endif\r\n\
\r\n\
#if DEVILX_HLSL_VERSION==0\r\n\
float2 mul(float2 v,float2x2 m){return v*m;}\r\n\
float3 mul(float2 v,float3x2 m){return v*m;}\r\n\
float4 mul(float2 v,float4x2 m){return v*m;}\r\n\
float2 mul(float3 v,float2x3 m){return v*m;}\r\n\
float3 mul(float3 v,float3x3 m){return v*m;}\r\n\
float4 mul(float3 v,float4x3 m){return v*m;}\r\n\
float2 mul(float4 v,float2x4 m){return v*m;}\r\n\
float3 mul(float4 v,float3x4 m){return v*m;}\r\n\
float4 mul(float4 v,float4x4 m){return v*m;}\r\n\
float2 mul(float2x2 m,float2 v){return m*v;}\r\n\
float2 mul(float3x2 m,float3 v){return m*v;}\r\n\
float2 mul(float4x2 m,float4 v){return m*v;}\r\n\
float3 mul(float2x3 m,float2 v){return m*v;}\r\n\
float3 mul(float3x3 m,float3 v){return m*v;}\r\n\
float3 mul(float4x3 m,float4 v){return m*v;}\r\n\
float4 mul(float2x4 m,float2 v){return m*v;}\r\n\
float4 mul(float3x4 m,float3 v){return m*v;}\r\n\
float4 mul(float4x4 m,float4 v){return m*v;}\r\n\
float2x2 mul(float2x2 m0,float2x2 m1){return m0*m1;}\r\n\
float3x3 mul(float3x3 m0,float3x3 m1){return m0*m1;}\r\n\
float4x4 mul(float4x4 m0,float4x4 m1){return m0*m1;}\r\n\
float saturate(float v){return clamp(v,0.0,1.0);}\r\n\
float2 saturate(float2 v){return clamp(v,float2(0.0),float2(1.0));}\r\n\
float3 saturate(float3 v){return clamp(v,float3(0.0),float3(1.0));}\r\n\
float4 saturate(float4 v){return clamp(v,float4(0.0),float4(1.0));}\r\n\
#endif\r\n\
float3x3 convert(float4x4 v)\r\n\
{\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	return (float3x3)v;\r\n\
#else\r\n\
	return float3x3(v);\r\n\
#endif\r\n\
}\r\n\
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x,v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x,v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcHemisphereLightFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	float cos_the=dot(vertexToLightDirection,worldNormal);\r\n\
	return cos_the*0.5+0.5;\r\n\
}\r\n\
float calcLambertDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcPhongSpecularFactor(float3 lightToVertexDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 reflect_dir=reflect(lightToVertexDirection,worldNormal);\r\n\
	float factor=saturate(dot(reflect_dir,vertexToCameraDirection));\r\n\
	return factor;\r\n\
}\r\n\
float calcBlinnPhongSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 half_vector = normalize(vertexToCameraDirection + vertexToLightDirection);\r\n\
	float specular_factor = saturate(dot(half_vector, worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
float3 calcSphericalHarmonicsLightFactor(float3 worldNormal)\r\n\
{\r\n\
	const float c1=0.429043;\r\n\
	const float c2=0.511664;\r\n\
	const float c3=0.743125;\r\n\
	const float c4=0.886227;\r\n\
	const float c5=0.247708;\r\n\
	const float3 l00=float3(0.871297,0.875222,0.864470);\r\n\
	const float3 l1m1=float3(0.175058,0.245335,0.312891);\r\n\
	const float3 l10=float3(0.034675,0.036107,0.037362);\r\n\
	const float3 l11=float3(-0.004629,-0.029448,-0.048028);\r\n\
	const float3 l2m2=float3(-0.120535,-0.121160,-0.117507);\r\n\
	const float3 l2m1=float3(0.003242,0.003624,0.007511);\r\n\
	const float3 l20=float3(-0.028667,-0.024926,-0.020998);\r\n\
	const float3 l21=float3(-0.077539,-0.086325,-0.091591);\r\n\
	const float3 l22=float3(-0.161784,-0.191783,0.219152);\r\n\
	float3 factor=c1*l22*(worldNormal.x*worldNormal.x-worldNormal.y*worldNormal.y)\r\n\
	+c3*l20*worldNormal.z*worldNormal.z\r\n\
	+c4*l00\r\n\
	-c5*l20\r\n\
	+2.0*c1*l2m2*worldNormal.x*worldNormal.y\r\n\
	+2.0*c1*l21*worldNormal.x*worldNormal.z\r\n\
	+2.0*c1*l2m1*worldNormal.y*worldNormal.z\r\n\
	+2.0*c2*l11*worldNormal.x\r\n\
	+2.0*c2*l1m1*worldNormal.y\r\n\
	+2.0*c2*l10*worldNormal.z;\r\n\
	return factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
	float factor=saturate((current - begin) * reciprocalRange);\r\n\
    return 1.0 - factor*factor;\r\n\
}\r\n\
float3 encodeNormal(float3 normal)\r\n\
{\r\n\
	return normal / getMaxComponment(normal);\r\n\
}\r\n\
float2 getQuadPosition(int vertexID)\r\n\
{\r\n\
    float2 ret;\r\n\
    if(0==vertexID)\r\n\
        ret = float2(-1.0, 1.0);\r\n\
    else if(1==vertexID)\r\n\
        ret = float2(1.0, 1.0);\r\n\
    else if(2==vertexID)\r\n\
        ret = float2(-1.0, -1.0);\r\n\
    else\r\n\
        ret = float2(1.0, -1.0);\r\n\
    return ret;\r\n\
}\r\n\
\r\n\
\r\n\
\r\n\
DECL_CB(cbSystem)\r\n\
CB_MEMBER float gFrameTimeInSeconds;\r\n\
CB_MEMBER float gInverseFrameTimeInSeconds;\r\n\
END_DECL\r\n\
DECL_CB(cbRenderTarget)\r\n\
CB_MEMBER float2 gRenderTargetSizeInPixel;\r\n\
CB_MEMBER float2 gInverseRenderTargetSizeInPixel;\r\n\
END_DECL\r\n\
DECL_CB(cbViewport)\r\n\
CB_MEMBER float2 gViewportSizeInPixel;\r\n\
CB_MEMBER float2 gInverseViewportSizeInPixel;\r\n\
END_DECL\r\n\
DECL_CB(cbCamera)\r\n\
CB_MEMBER float4x4 gViewMatrix;\r\n\
CB_MEMBER float4x4 gInverseViewMatrix;\r\n\
CB_MEMBER float4x4 gProjectionMatrix;\r\n\
CB_MEMBER float4x4 gInverseProjectionMatrix;\r\n\
CB_MEMBER float4x4 gViewProjectionMatrix;\r\n\
CB_MEMBER float4x4 gInverseViewProjectionMatrix;\r\n\
CB_MEMBER float gFarDistance;\r\n\
CB_MEMBER float gInverseFarDistance;\r\n\
END_DECL\r\n\
DECL_CB(cbScene)\r\n\
CB_MEMBER float3 gAmbientColour;\r\n\
CB_MEMBER float3 gSkyColour;\r\n\
CB_MEMBER float3 gGroundColour;\r\n\
CB_MEMBER float3 gSkyLightDirection;\r\n\
END_DECL\r\n\
\r\n\
\r\n\
float3 getCameraPosition()\r\n\
{\r\n\
	return getCameraPosition(gViewMatrix);\r\n\
}\r\n\
float3 getCameraDirection()\r\n\
{\r\n\
	return getCameraDirection(gViewMatrix);\r\n\
}\r\n\
float3 getCameraUp()\r\n\
{\r\n\
	return getCameraUp(gViewMatrix);\r\n\
}\r\n\
float3 getCameraRight()\r\n\
{\r\n\
	return getCameraRight(gViewMatrix);\r\n\
}\r\n\
float3 calcHemisphereLightColour(float3 worldNormal)\r\n\
{\r\n\
	float3 factor=calcHemisphereLightFactor(-gSkyLightDirection,worldNormal);\r\n\
	return lerp(gGroundColour,gSkyColour,factor);\r\n\
}\r\n\
\r\n\
\r\n\
\r\n\
\r\n\
DECL_CB(cbObjectTransform)\r\n\
CB_MEMBER float4x4 gWorldMatrix;\r\n\
END_DECL\r\n\
DECL_CB(cbObjectMaterial)\r\n\
CB_MEMBER float3 gMainColour;\r\n\
CB_MEMBER float gAlpha;\r\n\
CB_MEMBER float3 gSpecularColour;\r\n\
CB_MEMBER float gSpecularPower;\r\n\
CB_MEMBER float3 gEmissiveColour;\r\n\
CB_MEMBER float gAlphaTestValue;\r\n\
END_DECL\r\n\
\r\n\
\r\n\
DECL_CB(cbDirectionLight)\r\n\
CB_MEMBER float3 gDirectionLightDiffuseColour;\r\n\
CB_MEMBER float3 gDirectionLightSpecularColour;\r\n\
CB_MEMBER float3 gDirectionLightDirection;\r\n\
END_DECL\r\n\
DECL_CB(cbPointLight)\r\n\
CB_MEMBER float3 gPointLightDiffuseColour;\r\n\
CB_MEMBER float3 gPointLightSpecularColour;\r\n\
CB_MEMBER float3 gPointLightPosition;\r\n\
CB_MEMBER float gPointLightReciprocalRange;\r\n\
CB_MEMBER float gPointLightStartFallOffDistance;\r\n\
END_DECL\r\n\
DECL_CB(cbSpotLight)\r\n\
CB_MEMBER float3 gSpotLightDiffuseColour;\r\n\
CB_MEMBER float3 gSpotLightSpecularColour;\r\n\
CB_MEMBER float3 gSpotLightDirection;\r\n\
CB_MEMBER float3 gSpotLightPosition;\r\n\
CB_MEMBER float gSpotLightReciprocalRange;\r\n\
CB_MEMBER float gSpotLightStartFallOffDistance;\r\n\
CB_MEMBER float gSpotLightCosInnerCornerHalfAngle;\r\n\
CB_MEMBER float gSpotLightReciprocalDeltaCosHalfAngle;\r\n\
END_DECL\r\n\
\r\n\
\r\n\
#ifndef OUTPUT_WORLD_POSITION\r\n\
#define OUTPUT_WORLD_POSITION 0\r\n\
#endif\r\n\
#ifndef OUTPUT_WORLD_NORMAL\r\n\
#define OUTPUT_WORLD_NORMAL 0\r\n\
#endif\r\n\
#ifndef OUTPUT_WORLD_TANGENT\r\n\
#define OUTPUT_WORLD_TANGENT 0\r\n\
#endif\r\n\
#ifndef OUTPUT_MAIN_UV\r\n\
#define OUTPUT_MAIN_UV 0\r\n\
#endif\r\n\
#ifndef OUTPUT_DIFFUSE\r\n\
#define OUTPU_DIFFUSE 0\r\n\
#endif\r\n\
#ifndef USE_LIGHTING\r\n\
#define USE_LIGHTING 0\r\n\
#endif\r\n\
#ifndef USE_DIRECTION_LIGHT\r\n\
#define USE_DIRECTION_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_POINT_LIGHT\r\n\
#define USE_POINT_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_SPOT_LIGHT\r\n\
#define USE_SPOT_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_NORMAL_TEXTURE\r\n\
#define USE_NORMAL_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_ALPHA_TEST\r\n\
#define USE_ALPHA_TEST 0\r\n\
#endif\r\n\
#ifndef USE_SPECULAR\r\n\
#define USE_SPECULAR 0\r\n\
#endif\r\n\
\r\n\
\r\n\
\r\n\
\r\n\
struct SVertexShaderInput\r\n\
{\r\n\
	float3 mPosition : SV_Position;\r\n\
#if OUTPUT_WORLD_NORMAL\r\n\
	float3 mNormal : NORMAL;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mTangent : TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
#if OUTPUT_DIFFUSE\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
#endif\r\n\
};\r\n\
struct SVertexShaderOutput\r\n\
{\r\n\
	float4 mPosition : SV_Position;\r\n\
#if OUTPUT_WORLD_POSITION\r\n\
	float3 mWorldPosition : WORLD_POSITION;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_NORMAL\r\n\
	float3 mWorldNormal : WORLD_NORMAL;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mWorldTangent : WORLD_TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
#if OUTPUT_DIFFUSE\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
#endif\r\n\
};\r\n\
SVertexShaderOutput vsMain(SVertexShaderInput input)\r\n\
{\r\n\
    SVertexShaderOutput output = (SVertexShaderOutput) 0;\r\n\
#define iPosition input.mPosition\r\n\
#define iNormal input.mNormal\r\n\
#define iTangent input.mTangent\r\n\
#define iMainUV input.mMainUV\r\n\
#define iDiffuse input.mDiffuse\r\n\
#define oPosition output.mPosition\r\n\
#define oWorldPosition output.mWorldPosition\r\n\
#define oWorldNormal output.mWorldNormal\r\n\
#define oWorldTangent output.mWorldTangent\r\n\
#define oMainUV output.mMainUV\r\n\
#define oDiffuse output.mDiffuse\r\n\
    float4 world_position = mul(gWorldMatrix, float4(iPosition, 1.0));\r\n\
    oPosition = mul(gViewProjectionMatrix, world_position);\r\n\
#if OUTPUT_WORLD_POSITION\r\n\
	oWorldPosition = world_position.xyz;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_NORMAL\r\n\
	oWorldNormal = mul(convert(gWorldMatrix), iNormal);\r\n\
#endif\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	oWorldTangent = mul(convert(gWorldMatrix), iTangent);\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	oMainUV = iMainUV;\r\n\
#endif\r\n\
#if OUTPUT_DIFFUSE\r\n\
	oDiffuse = iDiffuse;\r\n\
#endif\r\n\
    return output;\r\n\
}\r\n\
SamplerState gDiffuseSamplerState;\r\n\
SamplerState gNormalSamplerState;\r\n\
Texture2D<float4> gDiffuseTexture;\r\n\
Texture2D<float4> gNormalTexture;\r\n\
struct SPixelShaderOutput\r\n\
{\r\n\
	float4 mColour : SV_Target;\r\n\
};\r\n\
SPixelShaderOutput psMain(SVertexShaderOutput input)\r\n\
{\r\n\
    SPixelShaderOutput output = (SPixelShaderOutput)0;\r\n\
#define iWorldPosition input.mWorldPosition\r\n\
#define iWorldNormal input.mWorldNormal\r\n\
#define iWorldTangent input.mWorldTangent\r\n\
#define iMainUV input.mMainUV\r\n\
#define iDiffuse input.mDiffuse\r\n\
#define oColour output.mColour\r\n\
	float3 colour_emissive = gEmissiveColour;\r\n\
	float3 colour_diffuse_factor = gMainColour;\r\n\
    float3 colour_specular_factor = gSpecularColour;\r\n\
    float alpha = gAlpha;\r\n\
#if OUTPUT_DIFFUSE\r\n\
    colour_emissive *= iDiffuse.rgb;\r\n\
    colour_diffuse_factor *= iDiffuse.rgb;\r\n\
    alpha *= iDiffuse.a;\r\n\
#endif\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler=SAMPLE_TEXTURE(Diffuse,iMainUV);\r\n\
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;\r\n\
	float diffuse_texture_alpha = diffuse_texture_sampler.a;\r\n\
	alpha *= diffuse_texture_alpha;\r\n\
	colour_diffuse_factor *= diffuse_texture_colour;\r\n\
	colour_emissive *= diffuse_texture_colour;\r\n\
#endif\r\n\
#if USE_ALPHA_TEST\r\n\
	if(alpha - gAlphaTestValue<0)discard;\r\n\
#endif\r\n\
#if USE_LIGHTING\r\n\
    #if USE_DIRECTION_LIGHT||USE_POINT_LIGHT||USE_SPOT_LIGHT\r\n\
    float3 lighting_colour=0;\r\n\
    float lighting_falloff_factor=1.0;\r\n\
	float3 world_normal=normalize(iWorldNormal);\r\n\
		#if USE_NORMAL_TEXTURE\r\n\
	float4 normal_texture_sampler=SAMPLE_TEXTURE(Normal,iMainUV);\r\n\
	float3 normal_texture_normal=normal_texture_sampler.xyz * 2.0-1.0;\r\n\
	float3 world_tangent=normalize(iWorldTangent);\r\n\
	float3 world_binormal=cross(world_normal,world_tangent);\r\n\
	float3x3 tbn=float3x3(world_tangent,world_binormal,world_normal);\r\n\
	world_normal=mul(tbn,normal_texture_normal);\r\n\
		#endif\r\n\
		#if USE_DIRECTION_LIGHT\r\n\
	float3 vertex_to_light_direction = -gDirectionLightDirection;\r\n\
    float3 light_diffuse_colour = gDirectionLightDiffuseColour;\r\n\
    float3 light_specular_colour = gDirectionLightSpecularColour;\r\n\
	    #elif USE_POINT_LIGHT\r\n\
    float3 vertex_to_light = gPointLightPosition - iWorldPosition;\r\n\
    lighting_falloff_factor=calcFalloffFactor(length(vertex_to_light),gPointLightStartFallOffDistance,gPointLightReciprocalRange);\r\n\
	float3 vertex_to_light_direction = normalize(vertex_to_light);\r\n\
    float3 light_diffuse_colour = gPointLightDiffuseColour;\r\n\
    float3 light_specular_colour = gPointLightSpecularColour;\r\n\
	    #elif USE_SPOT_LIGHT\r\n\
    float3 vertex_to_light = gSpotLightPosition - iWorldPosition;\r\n\
    float falloff_distance_factor=calcFalloffFactor(length(vertex_to_light),gSpotLightStartFallOffDistance,gSpotLightReciprocalRange);\r\n\
	float3 vertex_to_light_direction = normalize(vertex_to_light);\r\n\
    float falloff_angle_factor=calcFalloffFactor(dot(vertex_to_light_direction,gSpotLightDirection),gSpotLightCosInnerCornerHalfAngle,gSpotLightReciprocalDeltaCosHalfAngle);\r\n\
    lighting_falloff_factor=falloff_distance_factor*falloff_angle_factor;\r\n\
    float3 light_diffuse_colour = gSpotLightDiffuseColour;\r\n\
    float3 light_specular_colour = gSpotLightSpecularColour;\r\n\
	    #endif\r\n\
	float lighting_diffuse_factor = calcDiffuseFactor(vertex_to_light_direction, world_normal);\r\n\
    float3 lighting_diffuse_colour = light_diffuse_colour * lighting_diffuse_factor;\r\n\
	lighting_colour+=lighting_diffuse_colour;\r\n\
		#if USE_SPECULAR\r\n\
	float lighting_specular_factor=calcSpecularFactor(vertex_to_light_direction,world_normal,iWorldPosition,getCameraPosition());\r\n\
	float3 lighting_specular_colour=lighting_diffuse_factor > 0.0?pow(lighting_specular_factor,gSpecularPower) * light_specular_colour:0.0;\r\n\
	lighting_colour+=lighting_specular_colour;\r\n\
		#endif\r\n\
    oColour.rgb+=lighting_colour*lighting_falloff_factor*colour_diffuse_factor;\r\n\
	#else\r\n\
	oColour.rgb+=gAmbientColour*colour_diffuse_factor;\r\n\
	oColour.rgb+=colour_emissive;\r\n\
	#endif\r\n\
#else\r\n\
	oColour.rgb += colour_emissive;\r\n\
#endif\r\n\
	oColour.a = alpha;\r\n\
	return output;\r\n\
}\r\n\
\r\n\
\r\n\
";
ForwardVertexShader_glsl="#ifndef GLSL_VERSION\r\n\
	#define GLSL_VERSION 0\r\n\
#endif\r\n\
#ifndef GLSLES_VERSION\r\n\
	#define GLSLES_VERSION 0\r\n\
#endif\r\n\
#ifndef DEVILX_HLSL_VERSION\r\n\
	#define DEVILX_HLSL_VERSION 0\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)\r\n\
	#define float2 vec2\r\n\
	#define float3 vec3\r\n\
	#define float4 vec4\r\n\
	#define int2 ivec2\r\n\
	#define int3 ivec3\r\n\
	#define int4 ivec4\r\n\
	#define uint2 int2\r\n\
	#define uint3 int3\r\n\
	#define uint4 int4\r\n\
	#define float2x2 mat2\r\n\
	#define float2x3 mat2x3\r\n\
	#define float2x4 mat2x4\r\n\
	#define float3x2 mat3x2\r\n\
	#define float3x3 mat3\r\n\
	#define float3x4 mat3x4\r\n\
	#define float4x2 mat4x2\r\n\
	#define float4x3 mat4x3\r\n\
	#define float4x4 mat4\r\n\
	#define cbuffer layout(shared) uniform\r\n\
	#define lerp mix\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)||(DEVILX_HLSL_VERSION>=400)\r\n\
	#define DECL_CB(cb) cbuffer cb{\r\n\
	#define END_DECL };\r\n\
	#define CB_MEMBER uniform\r\n\
#else\r\n\
	#define DECL_CB(cb)\r\n\
	#define END_DECL\r\n\
	#define CB_MEMBER\r\n\
#endif\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) g##tex_name##Texture.Sample(g##tex_name##SamplerState,uv)\r\n\
#else\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) texture(g##tex_name##Texture,uv)\r\n\
#endif\r\n\
\r\n\
#if DEVILX_HLSL_VERSION==0\r\n\
float2 mul(float2 v,float2x2 m){return v*m;}\r\n\
float3 mul(float2 v,float3x2 m){return v*m;}\r\n\
float4 mul(float2 v,float4x2 m){return v*m;}\r\n\
float2 mul(float3 v,float2x3 m){return v*m;}\r\n\
float3 mul(float3 v,float3x3 m){return v*m;}\r\n\
float4 mul(float3 v,float4x3 m){return v*m;}\r\n\
float2 mul(float4 v,float2x4 m){return v*m;}\r\n\
float3 mul(float4 v,float3x4 m){return v*m;}\r\n\
float4 mul(float4 v,float4x4 m){return v*m;}\r\n\
float2 mul(float2x2 m,float2 v){return m*v;}\r\n\
float2 mul(float3x2 m,float3 v){return m*v;}\r\n\
float2 mul(float4x2 m,float4 v){return m*v;}\r\n\
float3 mul(float2x3 m,float2 v){return m*v;}\r\n\
float3 mul(float3x3 m,float3 v){return m*v;}\r\n\
float3 mul(float4x3 m,float4 v){return m*v;}\r\n\
float4 mul(float2x4 m,float2 v){return m*v;}\r\n\
float4 mul(float3x4 m,float3 v){return m*v;}\r\n\
float4 mul(float4x4 m,float4 v){return m*v;}\r\n\
float2x2 mul(float2x2 m0,float2x2 m1){return m0*m1;}\r\n\
float3x3 mul(float3x3 m0,float3x3 m1){return m0*m1;}\r\n\
float4x4 mul(float4x4 m0,float4x4 m1){return m0*m1;}\r\n\
float saturate(float v){return clamp(v,0.0,1.0);}\r\n\
float2 saturate(float2 v){return clamp(v,float2(0.0),float2(1.0));}\r\n\
float3 saturate(float3 v){return clamp(v,float3(0.0),float3(1.0));}\r\n\
float4 saturate(float4 v){return clamp(v,float4(0.0),float4(1.0));}\r\n\
#endif\r\n\
float3x3 convert(float4x4 v)\r\n\
{\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	return (float3x3)v;\r\n\
#else\r\n\
	return float3x3(v);\r\n\
#endif\r\n\
}\r\n\
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x,v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x,v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcHemisphereLightFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	float cos_the=dot(vertexToLightDirection,worldNormal);\r\n\
	return cos_the*0.5+0.5;\r\n\
}\r\n\
float calcLambertDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcPhongSpecularFactor(float3 lightToVertexDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 reflect_dir=reflect(lightToVertexDirection,worldNormal);\r\n\
	float factor=saturate(dot(reflect_dir,vertexToCameraDirection));\r\n\
	return factor;\r\n\
}\r\n\
float calcBlinnPhongSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 half_vector = normalize(vertexToCameraDirection + vertexToLightDirection);\r\n\
	float specular_factor = saturate(dot(half_vector, worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
float3 calcSphericalHarmonicsLightFactor(float3 worldNormal)\r\n\
{\r\n\
	const float c1=0.429043;\r\n\
	const float c2=0.511664;\r\n\
	const float c3=0.743125;\r\n\
	const float c4=0.886227;\r\n\
	const float c5=0.247708;\r\n\
	const float3 l00=float3(0.871297,0.875222,0.864470);\r\n\
	const float3 l1m1=float3(0.175058,0.245335,0.312891);\r\n\
	const float3 l10=float3(0.034675,0.036107,0.037362);\r\n\
	const float3 l11=float3(-0.004629,-0.029448,-0.048028);\r\n\
	const float3 l2m2=float3(-0.120535,-0.121160,-0.117507);\r\n\
	const float3 l2m1=float3(0.003242,0.003624,0.007511);\r\n\
	const float3 l20=float3(-0.028667,-0.024926,-0.020998);\r\n\
	const float3 l21=float3(-0.077539,-0.086325,-0.091591);\r\n\
	const float3 l22=float3(-0.161784,-0.191783,0.219152);\r\n\
	float3 factor=c1*l22*(worldNormal.x*worldNormal.x-worldNormal.y*worldNormal.y)\r\n\
	+c3*l20*worldNormal.z*worldNormal.z\r\n\
	+c4*l00\r\n\
	-c5*l20\r\n\
	+2.0*c1*l2m2*worldNormal.x*worldNormal.y\r\n\
	+2.0*c1*l21*worldNormal.x*worldNormal.z\r\n\
	+2.0*c1*l2m1*worldNormal.y*worldNormal.z\r\n\
	+2.0*c2*l11*worldNormal.x\r\n\
	+2.0*c2*l1m1*worldNormal.y\r\n\
	+2.0*c2*l10*worldNormal.z;\r\n\
	return factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
	float factor=saturate((current - begin) * reciprocalRange);\r\n\
    return 1.0 - factor*factor;\r\n\
}\r\n\
float3 encodeNormal(float3 normal)\r\n\
{\r\n\
	return normal / getMaxComponment(normal);\r\n\
}\r\n\
float2 getQuadPosition(int vertexID)\r\n\
{\r\n\
    float2 ret;\r\n\
    if(0==vertexID)\r\n\
        ret = float2(-1.0, 1.0);\r\n\
    else if(1==vertexID)\r\n\
        ret = float2(1.0, 1.0);\r\n\
    else if(2==vertexID)\r\n\
        ret = float2(-1.0, -1.0);\r\n\
    else\r\n\
        ret = float2(1.0, -1.0);\r\n\
    return ret;\r\n\
}\r\n\
\r\n\
\r\n\
\r\n\
DECL_CB(cbSystem)\r\n\
CB_MEMBER float gFrameTimeInSeconds;\r\n\
CB_MEMBER float gInverseFrameTimeInSeconds;\r\n\
END_DECL\r\n\
DECL_CB(cbRenderTarget)\r\n\
CB_MEMBER float2 gRenderTargetSizeInPixel;\r\n\
CB_MEMBER float2 gInverseRenderTargetSizeInPixel;\r\n\
END_DECL\r\n\
DECL_CB(cbViewport)\r\n\
CB_MEMBER float2 gViewportSizeInPixel;\r\n\
CB_MEMBER float2 gInverseViewportSizeInPixel;\r\n\
END_DECL\r\n\
DECL_CB(cbCamera)\r\n\
CB_MEMBER float4x4 gViewMatrix;\r\n\
CB_MEMBER float4x4 gInverseViewMatrix;\r\n\
CB_MEMBER float4x4 gProjectionMatrix;\r\n\
CB_MEMBER float4x4 gInverseProjectionMatrix;\r\n\
CB_MEMBER float4x4 gViewProjectionMatrix;\r\n\
CB_MEMBER float4x4 gInverseViewProjectionMatrix;\r\n\
CB_MEMBER float gFarDistance;\r\n\
CB_MEMBER float gInverseFarDistance;\r\n\
END_DECL\r\n\
DECL_CB(cbScene)\r\n\
CB_MEMBER float3 gAmbientColour;\r\n\
CB_MEMBER float3 gSkyColour;\r\n\
CB_MEMBER float3 gGroundColour;\r\n\
CB_MEMBER float3 gSkyLightDirection;\r\n\
END_DECL\r\n\
\r\n\
\r\n\
float3 getCameraPosition()\r\n\
{\r\n\
	return getCameraPosition(gViewMatrix);\r\n\
}\r\n\
float3 getCameraDirection()\r\n\
{\r\n\
	return getCameraDirection(gViewMatrix);\r\n\
}\r\n\
float3 getCameraUp()\r\n\
{\r\n\
	return getCameraUp(gViewMatrix);\r\n\
}\r\n\
float3 getCameraRight()\r\n\
{\r\n\
	return getCameraRight(gViewMatrix);\r\n\
}\r\n\
float3 calcHemisphereLightColour(float3 worldNormal)\r\n\
{\r\n\
	float3 factor=calcHemisphereLightFactor(-gSkyLightDirection,worldNormal);\r\n\
	return lerp(gGroundColour,gSkyColour,factor);\r\n\
}\r\n\
\r\n\
\r\n\
\r\n\
\r\n\
DECL_CB(cbObjectTransform)\r\n\
CB_MEMBER float4x4 gWorldMatrix;\r\n\
END_DECL\r\n\
DECL_CB(cbObjectMaterial)\r\n\
CB_MEMBER float3 gMainColour;\r\n\
CB_MEMBER float gAlpha;\r\n\
CB_MEMBER float3 gSpecularColour;\r\n\
CB_MEMBER float gSpecularPower;\r\n\
CB_MEMBER float3 gEmissiveColour;\r\n\
CB_MEMBER float gAlphaTestValue;\r\n\
END_DECL\r\n\
\r\n\
\r\n\
DECL_CB(cbDirectionLight)\r\n\
CB_MEMBER float3 gDirectionLightDiffuseColour;\r\n\
CB_MEMBER float3 gDirectionLightSpecularColour;\r\n\
CB_MEMBER float3 gDirectionLightDirection;\r\n\
END_DECL\r\n\
DECL_CB(cbPointLight)\r\n\
CB_MEMBER float3 gPointLightDiffuseColour;\r\n\
CB_MEMBER float3 gPointLightSpecularColour;\r\n\
CB_MEMBER float3 gPointLightPosition;\r\n\
CB_MEMBER float gPointLightReciprocalRange;\r\n\
CB_MEMBER float gPointLightStartFallOffDistance;\r\n\
END_DECL\r\n\
DECL_CB(cbSpotLight)\r\n\
CB_MEMBER float3 gSpotLightDiffuseColour;\r\n\
CB_MEMBER float3 gSpotLightSpecularColour;\r\n\
CB_MEMBER float3 gSpotLightDirection;\r\n\
CB_MEMBER float3 gSpotLightPosition;\r\n\
CB_MEMBER float gSpotLightReciprocalRange;\r\n\
CB_MEMBER float gSpotLightStartFallOffDistance;\r\n\
CB_MEMBER float gSpotLightCosInnerCornerHalfAngle;\r\n\
CB_MEMBER float gSpotLightReciprocalDeltaCosHalfAngle;\r\n\
END_DECL\r\n\
\r\n\
\r\n\
#ifndef OUTPUT_WORLD_POSITION\r\n\
#define OUTPUT_WORLD_POSITION 0\r\n\
#endif\r\n\
#ifndef OUTPUT_WORLD_NORMAL\r\n\
#define OUTPUT_WORLD_NORMAL 0\r\n\
#endif\r\n\
#ifndef OUTPUT_WORLD_TANGENT\r\n\
#define OUTPUT_WORLD_TANGENT 0\r\n\
#endif\r\n\
#ifndef OUTPUT_MAIN_UV\r\n\
#define OUTPUT_MAIN_UV 0\r\n\
#endif\r\n\
#ifndef OUTPUT_DIFFUSE\r\n\
#define OUTPU_DIFFUSE 0\r\n\
#endif\r\n\
#ifndef USE_LIGHTING\r\n\
#define USE_LIGHTING 0\r\n\
#endif\r\n\
#ifndef USE_DIRECTION_LIGHT\r\n\
#define USE_DIRECTION_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_POINT_LIGHT\r\n\
#define USE_POINT_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_SPOT_LIGHT\r\n\
#define USE_SPOT_LIGHT 0\r\n\
#endif\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_NORMAL_TEXTURE\r\n\
#define USE_NORMAL_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_ALPHA_TEST\r\n\
#define USE_ALPHA_TEST 0\r\n\
#endif\r\n\
#ifndef USE_SPECULAR\r\n\
#define USE_SPECULAR 0\r\n\
#endif\r\n\
\r\n\
\r\n\
\r\n\
\r\n\
in float3 gPositionVS;\r\n\
#if OUTPUT_WORLD_POSITION\r\n\
out float3 gWorldPositionPS;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_NORMAL\r\n\
in float3 gNormalVS;\r\n\
out float3 gWorldNormalPS;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
in float3 gTangentVS;\r\n\
out float3 gWorldTangentPS;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
in float2 gMainUVVS;\r\n\
out float2 gMainUVPS;\r\n\
#endif\r\n\
#if OUTPUT_DIFFUSE\r\n\
in float4 gDiffuseVS;\r\n\
out float4 gDiffusePS;\r\n\
#endif\r\n\
void main()\r\n\
{\r\n\
#define iPosition gPositionVS\r\n\
#define iNormal gNormalVS\r\n\
#define iTangent gTangentVS\r\n\
#define iMainUV gMainUVVS\r\n\
#define iDiffuse gDiffuseVS\r\n\
#define oPosition gl_Position\r\n\
#define oWorldPosition gWorldPositionPS\r\n\
#define oWorldNormal gWorldNormalPS\r\n\
#define oWorldTangent gWorldTangentPS\r\n\
#define oMainUV gMainUVPS\r\n\
#define oDiffuse gDiffusePS\r\n\
    float4 world_position = mul(gWorldMatrix, float4(iPosition, 1.0));\r\n\
    oPosition = mul(gViewProjectionMatrix, world_position);\r\n\
#if OUTPUT_WORLD_POSITION\r\n\
	oWorldPosition = world_position.xyz;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_NORMAL\r\n\
	oWorldNormal = mul(convert(gWorldMatrix), iNormal);\r\n\
#endif\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	oWorldTangent = mul(convert(gWorldMatrix), iTangent);\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	oMainUV = iMainUV;\r\n\
#endif\r\n\
#if OUTPUT_DIFFUSE\r\n\
	oDiffuse = iDiffuse;\r\n\
#endif\r\n\
}\r\n\
\r\n\
\r\n\
";
OverlayPixelShader_glsl="#ifndef GLSL_VERSION\r\n\
	#define GLSL_VERSION 0\r\n\
#endif\r\n\
#ifndef GLSLES_VERSION\r\n\
	#define GLSLES_VERSION 0\r\n\
#endif\r\n\
#ifndef DEVILX_HLSL_VERSION\r\n\
	#define DEVILX_HLSL_VERSION 0\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)\r\n\
	#define float2 vec2\r\n\
	#define float3 vec3\r\n\
	#define float4 vec4\r\n\
	#define int2 ivec2\r\n\
	#define int3 ivec3\r\n\
	#define int4 ivec4\r\n\
	#define uint2 int2\r\n\
	#define uint3 int3\r\n\
	#define uint4 int4\r\n\
	#define float2x2 mat2\r\n\
	#define float2x3 mat2x3\r\n\
	#define float2x4 mat2x4\r\n\
	#define float3x2 mat3x2\r\n\
	#define float3x3 mat3\r\n\
	#define float3x4 mat3x4\r\n\
	#define float4x2 mat4x2\r\n\
	#define float4x3 mat4x3\r\n\
	#define float4x4 mat4\r\n\
	#define cbuffer layout(shared) uniform\r\n\
	#define lerp mix\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)||(DEVILX_HLSL_VERSION>=400)\r\n\
	#define DECL_CB(cb) cbuffer cb{\r\n\
	#define END_DECL };\r\n\
	#define CB_MEMBER uniform\r\n\
#else\r\n\
	#define DECL_CB(cb)\r\n\
	#define END_DECL\r\n\
	#define CB_MEMBER\r\n\
#endif\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) g##tex_name##Texture.Sample(g##tex_name##SamplerState,uv)\r\n\
#else\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) texture(g##tex_name##Texture,uv)\r\n\
#endif\r\n\
\r\n\
#if DEVILX_HLSL_VERSION==0\r\n\
float2 mul(float2 v,float2x2 m){return v*m;}\r\n\
float3 mul(float2 v,float3x2 m){return v*m;}\r\n\
float4 mul(float2 v,float4x2 m){return v*m;}\r\n\
float2 mul(float3 v,float2x3 m){return v*m;}\r\n\
float3 mul(float3 v,float3x3 m){return v*m;}\r\n\
float4 mul(float3 v,float4x3 m){return v*m;}\r\n\
float2 mul(float4 v,float2x4 m){return v*m;}\r\n\
float3 mul(float4 v,float3x4 m){return v*m;}\r\n\
float4 mul(float4 v,float4x4 m){return v*m;}\r\n\
float2 mul(float2x2 m,float2 v){return m*v;}\r\n\
float2 mul(float3x2 m,float3 v){return m*v;}\r\n\
float2 mul(float4x2 m,float4 v){return m*v;}\r\n\
float3 mul(float2x3 m,float2 v){return m*v;}\r\n\
float3 mul(float3x3 m,float3 v){return m*v;}\r\n\
float3 mul(float4x3 m,float4 v){return m*v;}\r\n\
float4 mul(float2x4 m,float2 v){return m*v;}\r\n\
float4 mul(float3x4 m,float3 v){return m*v;}\r\n\
float4 mul(float4x4 m,float4 v){return m*v;}\r\n\
float2x2 mul(float2x2 m0,float2x2 m1){return m0*m1;}\r\n\
float3x3 mul(float3x3 m0,float3x3 m1){return m0*m1;}\r\n\
float4x4 mul(float4x4 m0,float4x4 m1){return m0*m1;}\r\n\
float saturate(float v){return clamp(v,0.0,1.0);}\r\n\
float2 saturate(float2 v){return clamp(v,float2(0.0),float2(1.0));}\r\n\
float3 saturate(float3 v){return clamp(v,float3(0.0),float3(1.0));}\r\n\
float4 saturate(float4 v){return clamp(v,float4(0.0),float4(1.0));}\r\n\
#endif\r\n\
float3x3 convert(float4x4 v)\r\n\
{\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	return (float3x3)v;\r\n\
#else\r\n\
	return float3x3(v);\r\n\
#endif\r\n\
}\r\n\
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x,v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x,v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcHemisphereLightFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	float cos_the=dot(vertexToLightDirection,worldNormal);\r\n\
	return cos_the*0.5+0.5;\r\n\
}\r\n\
float calcLambertDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcPhongSpecularFactor(float3 lightToVertexDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 reflect_dir=reflect(lightToVertexDirection,worldNormal);\r\n\
	float factor=saturate(dot(reflect_dir,vertexToCameraDirection));\r\n\
	return factor;\r\n\
}\r\n\
float calcBlinnPhongSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 half_vector = normalize(vertexToCameraDirection + vertexToLightDirection);\r\n\
	float specular_factor = saturate(dot(half_vector, worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
float3 calcSphericalHarmonicsLightFactor(float3 worldNormal)\r\n\
{\r\n\
	const float c1=0.429043;\r\n\
	const float c2=0.511664;\r\n\
	const float c3=0.743125;\r\n\
	const float c4=0.886227;\r\n\
	const float c5=0.247708;\r\n\
	const float3 l00=float3(0.871297,0.875222,0.864470);\r\n\
	const float3 l1m1=float3(0.175058,0.245335,0.312891);\r\n\
	const float3 l10=float3(0.034675,0.036107,0.037362);\r\n\
	const float3 l11=float3(-0.004629,-0.029448,-0.048028);\r\n\
	const float3 l2m2=float3(-0.120535,-0.121160,-0.117507);\r\n\
	const float3 l2m1=float3(0.003242,0.003624,0.007511);\r\n\
	const float3 l20=float3(-0.028667,-0.024926,-0.020998);\r\n\
	const float3 l21=float3(-0.077539,-0.086325,-0.091591);\r\n\
	const float3 l22=float3(-0.161784,-0.191783,0.219152);\r\n\
	float3 factor=c1*l22*(worldNormal.x*worldNormal.x-worldNormal.y*worldNormal.y)\r\n\
	+c3*l20*worldNormal.z*worldNormal.z\r\n\
	+c4*l00\r\n\
	-c5*l20\r\n\
	+2.0*c1*l2m2*worldNormal.x*worldNormal.y\r\n\
	+2.0*c1*l21*worldNormal.x*worldNormal.z\r\n\
	+2.0*c1*l2m1*worldNormal.y*worldNormal.z\r\n\
	+2.0*c2*l11*worldNormal.x\r\n\
	+2.0*c2*l1m1*worldNormal.y\r\n\
	+2.0*c2*l10*worldNormal.z;\r\n\
	return factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
	float factor=saturate((current - begin) * reciprocalRange);\r\n\
    return 1.0 - factor*factor;\r\n\
}\r\n\
float3 encodeNormal(float3 normal)\r\n\
{\r\n\
	return normal / getMaxComponment(normal);\r\n\
}\r\n\
float2 getQuadPosition(int vertexID)\r\n\
{\r\n\
    float2 ret;\r\n\
    if(0==vertexID)\r\n\
        ret = float2(-1.0, 1.0);\r\n\
    else if(1==vertexID)\r\n\
        ret = float2(1.0, 1.0);\r\n\
    else if(2==vertexID)\r\n\
        ret = float2(-1.0, -1.0);\r\n\
    else\r\n\
        ret = float2(1.0, -1.0);\r\n\
    return ret;\r\n\
}\r\n\
\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
\r\n\
in float4 gPositionPS;\r\n\
in float2 gMainUVPS;\r\n\
in float4 gDiffusePS;\r\n\
#ifndef USE_FONT_TEXTURE\r\n\
#define USE_FONT_TEXTURE 0\r\n\
#endif\r\n\
#if USE_DIFFUSE_TEXTURE || USE_FONT_TEXTURE\r\n\
uniform sampler2D gDiffuseTexture;\r\n\
#endif\r\n\
out float4 gFragColour;\r\n\
void main()\r\n\
{\r\n\
#if USE_FONT_TEXTURE||USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler=texture(gDiffuseTexture,gMainUVPS);\r\n\
#endif\r\n\
#define iDiffuse gDiffusePS\r\n\
#define oColour gFragColour\r\n\
	oColour=iDiffuse;\r\n\
#if USE_DIFFUSE_TEXTURE||USE_FONT_TEXTURE\r\n\
	#if USE_FONT_TEXTURE\r\n\
	float4 diffuse_texture_colour=float4(float3(1.0),diffuse_texture_sampler.r);\r\n\
	#else\r\n\
	float4 diffuse_texture_colour=diffuse_texture_sampler;\r\n\
	#endif\r\n\
	oColour*=diffuse_texture_colour;\r\n\
#endif\r\n\
}\r\n\
\r\n\
";
OverlayShader_hlsl="#ifndef GLSL_VERSION\r\n\
	#define GLSL_VERSION 0\r\n\
#endif\r\n\
#ifndef GLSLES_VERSION\r\n\
	#define GLSLES_VERSION 0\r\n\
#endif\r\n\
#ifndef DEVILX_HLSL_VERSION\r\n\
	#define DEVILX_HLSL_VERSION 0\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)\r\n\
	#define float2 vec2\r\n\
	#define float3 vec3\r\n\
	#define float4 vec4\r\n\
	#define int2 ivec2\r\n\
	#define int3 ivec3\r\n\
	#define int4 ivec4\r\n\
	#define uint2 int2\r\n\
	#define uint3 int3\r\n\
	#define uint4 int4\r\n\
	#define float2x2 mat2\r\n\
	#define float2x3 mat2x3\r\n\
	#define float2x4 mat2x4\r\n\
	#define float3x2 mat3x2\r\n\
	#define float3x3 mat3\r\n\
	#define float3x4 mat3x4\r\n\
	#define float4x2 mat4x2\r\n\
	#define float4x3 mat4x3\r\n\
	#define float4x4 mat4\r\n\
	#define cbuffer layout(shared) uniform\r\n\
	#define lerp mix\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)||(DEVILX_HLSL_VERSION>=400)\r\n\
	#define DECL_CB(cb) cbuffer cb{\r\n\
	#define END_DECL };\r\n\
	#define CB_MEMBER uniform\r\n\
#else\r\n\
	#define DECL_CB(cb)\r\n\
	#define END_DECL\r\n\
	#define CB_MEMBER\r\n\
#endif\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) g##tex_name##Texture.Sample(g##tex_name##SamplerState,uv)\r\n\
#else\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) texture(g##tex_name##Texture,uv)\r\n\
#endif\r\n\
\r\n\
#if DEVILX_HLSL_VERSION==0\r\n\
float2 mul(float2 v,float2x2 m){return v*m;}\r\n\
float3 mul(float2 v,float3x2 m){return v*m;}\r\n\
float4 mul(float2 v,float4x2 m){return v*m;}\r\n\
float2 mul(float3 v,float2x3 m){return v*m;}\r\n\
float3 mul(float3 v,float3x3 m){return v*m;}\r\n\
float4 mul(float3 v,float4x3 m){return v*m;}\r\n\
float2 mul(float4 v,float2x4 m){return v*m;}\r\n\
float3 mul(float4 v,float3x4 m){return v*m;}\r\n\
float4 mul(float4 v,float4x4 m){return v*m;}\r\n\
float2 mul(float2x2 m,float2 v){return m*v;}\r\n\
float2 mul(float3x2 m,float3 v){return m*v;}\r\n\
float2 mul(float4x2 m,float4 v){return m*v;}\r\n\
float3 mul(float2x3 m,float2 v){return m*v;}\r\n\
float3 mul(float3x3 m,float3 v){return m*v;}\r\n\
float3 mul(float4x3 m,float4 v){return m*v;}\r\n\
float4 mul(float2x4 m,float2 v){return m*v;}\r\n\
float4 mul(float3x4 m,float3 v){return m*v;}\r\n\
float4 mul(float4x4 m,float4 v){return m*v;}\r\n\
float2x2 mul(float2x2 m0,float2x2 m1){return m0*m1;}\r\n\
float3x3 mul(float3x3 m0,float3x3 m1){return m0*m1;}\r\n\
float4x4 mul(float4x4 m0,float4x4 m1){return m0*m1;}\r\n\
float saturate(float v){return clamp(v,0.0,1.0);}\r\n\
float2 saturate(float2 v){return clamp(v,float2(0.0),float2(1.0));}\r\n\
float3 saturate(float3 v){return clamp(v,float3(0.0),float3(1.0));}\r\n\
float4 saturate(float4 v){return clamp(v,float4(0.0),float4(1.0));}\r\n\
#endif\r\n\
float3x3 convert(float4x4 v)\r\n\
{\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	return (float3x3)v;\r\n\
#else\r\n\
	return float3x3(v);\r\n\
#endif\r\n\
}\r\n\
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x,v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x,v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcHemisphereLightFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	float cos_the=dot(vertexToLightDirection,worldNormal);\r\n\
	return cos_the*0.5+0.5;\r\n\
}\r\n\
float calcLambertDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcPhongSpecularFactor(float3 lightToVertexDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 reflect_dir=reflect(lightToVertexDirection,worldNormal);\r\n\
	float factor=saturate(dot(reflect_dir,vertexToCameraDirection));\r\n\
	return factor;\r\n\
}\r\n\
float calcBlinnPhongSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 half_vector = normalize(vertexToCameraDirection + vertexToLightDirection);\r\n\
	float specular_factor = saturate(dot(half_vector, worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
float3 calcSphericalHarmonicsLightFactor(float3 worldNormal)\r\n\
{\r\n\
	const float c1=0.429043;\r\n\
	const float c2=0.511664;\r\n\
	const float c3=0.743125;\r\n\
	const float c4=0.886227;\r\n\
	const float c5=0.247708;\r\n\
	const float3 l00=float3(0.871297,0.875222,0.864470);\r\n\
	const float3 l1m1=float3(0.175058,0.245335,0.312891);\r\n\
	const float3 l10=float3(0.034675,0.036107,0.037362);\r\n\
	const float3 l11=float3(-0.004629,-0.029448,-0.048028);\r\n\
	const float3 l2m2=float3(-0.120535,-0.121160,-0.117507);\r\n\
	const float3 l2m1=float3(0.003242,0.003624,0.007511);\r\n\
	const float3 l20=float3(-0.028667,-0.024926,-0.020998);\r\n\
	const float3 l21=float3(-0.077539,-0.086325,-0.091591);\r\n\
	const float3 l22=float3(-0.161784,-0.191783,0.219152);\r\n\
	float3 factor=c1*l22*(worldNormal.x*worldNormal.x-worldNormal.y*worldNormal.y)\r\n\
	+c3*l20*worldNormal.z*worldNormal.z\r\n\
	+c4*l00\r\n\
	-c5*l20\r\n\
	+2.0*c1*l2m2*worldNormal.x*worldNormal.y\r\n\
	+2.0*c1*l21*worldNormal.x*worldNormal.z\r\n\
	+2.0*c1*l2m1*worldNormal.y*worldNormal.z\r\n\
	+2.0*c2*l11*worldNormal.x\r\n\
	+2.0*c2*l1m1*worldNormal.y\r\n\
	+2.0*c2*l10*worldNormal.z;\r\n\
	return factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
	float factor=saturate((current - begin) * reciprocalRange);\r\n\
    return 1.0 - factor*factor;\r\n\
}\r\n\
float3 encodeNormal(float3 normal)\r\n\
{\r\n\
	return normal / getMaxComponment(normal);\r\n\
}\r\n\
float2 getQuadPosition(int vertexID)\r\n\
{\r\n\
    float2 ret;\r\n\
    if(0==vertexID)\r\n\
        ret = float2(-1.0, 1.0);\r\n\
    else if(1==vertexID)\r\n\
        ret = float2(1.0, 1.0);\r\n\
    else if(2==vertexID)\r\n\
        ret = float2(-1.0, -1.0);\r\n\
    else\r\n\
        ret = float2(1.0, -1.0);\r\n\
    return ret;\r\n\
}\r\n\
\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
\r\n\
struct SVertexShaderInput\r\n\
{\r\n\
    float3 mPosition : SV_Position;\r\n\
    float2 mMainUV : TEXCOORD0;\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
};\r\n\
struct SVertexShaderOutput\r\n\
{\r\n\
    float4 mPosition : SV_Position;\r\n\
    float2 mMainUV : TEXCOORD0;\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
};\r\n\
SVertexShaderOutput vsMain(SVertexShaderInput input)\r\n\
{\r\n\
    SVertexShaderOutput output = (SVertexShaderOutput) 0;\r\n\
#define iPosition input.mPosition\r\n\
#define iMainUV input.mMainUV\r\n\
#define iDiffuse input.mDiffuse\r\n\
#define oPosition output.mPosition\r\n\
#define oMainUV output.mMainUV\r\n\
#define oDiffuse output.mDiffuse\r\n\
	oPosition=float4(iPosition,1.0);\r\n\
	oMainUV=iMainUV;\r\n\
	oDiffuse=iDiffuse;\r\n\
    return output;\r\n\
}\r\n\
SamplerState gDiffuseSamplerState;\r\n\
Texture2D<float4> gDiffuseTexture;\r\n\
struct SPixelShaderOutput\r\n\
{\r\n\
    float4 mColour : SV_Target;\r\n\
};\r\n\
SPixelShaderOutput psMain(SVertexShaderOutput input)\r\n\
{\r\n\
    SPixelShaderOutput output = (SPixelShaderOutput) 0;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);\r\n\
#endif\r\n\
#define iDiffuse input.mDiffuse\r\n\
#define oColour output.mColour\r\n\
	oColour=iDiffuse;\r\n\
#if USE_DIFFUSE_TEXTURE||USE_FONT_TEXTURE\r\n\
	#if USE_FONT_TEXTURE\r\n\
	float4 diffuse_texture_colour=float4(float3(1.0),diffuse_texture_sampler.r);\r\n\
	#else\r\n\
	float4 diffuse_texture_colour=diffuse_texture_sampler;\r\n\
	#endif\r\n\
	oColour*=diffuse_texture_colour;\r\n\
#endif\r\n\
    return output;\r\n\
}\r\n\
\r\n\
\r\n\
";
OverlayVertexShader_glsl="#ifndef GLSL_VERSION\r\n\
	#define GLSL_VERSION 0\r\n\
#endif\r\n\
#ifndef GLSLES_VERSION\r\n\
	#define GLSLES_VERSION 0\r\n\
#endif\r\n\
#ifndef DEVILX_HLSL_VERSION\r\n\
	#define DEVILX_HLSL_VERSION 0\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)\r\n\
	#define float2 vec2\r\n\
	#define float3 vec3\r\n\
	#define float4 vec4\r\n\
	#define int2 ivec2\r\n\
	#define int3 ivec3\r\n\
	#define int4 ivec4\r\n\
	#define uint2 int2\r\n\
	#define uint3 int3\r\n\
	#define uint4 int4\r\n\
	#define float2x2 mat2\r\n\
	#define float2x3 mat2x3\r\n\
	#define float2x4 mat2x4\r\n\
	#define float3x2 mat3x2\r\n\
	#define float3x3 mat3\r\n\
	#define float3x4 mat3x4\r\n\
	#define float4x2 mat4x2\r\n\
	#define float4x3 mat4x3\r\n\
	#define float4x4 mat4\r\n\
	#define cbuffer layout(shared) uniform\r\n\
	#define lerp mix\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)||(DEVILX_HLSL_VERSION>=400)\r\n\
	#define DECL_CB(cb) cbuffer cb{\r\n\
	#define END_DECL };\r\n\
	#define CB_MEMBER uniform\r\n\
#else\r\n\
	#define DECL_CB(cb)\r\n\
	#define END_DECL\r\n\
	#define CB_MEMBER\r\n\
#endif\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) g##tex_name##Texture.Sample(g##tex_name##SamplerState,uv)\r\n\
#else\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) texture(g##tex_name##Texture,uv)\r\n\
#endif\r\n\
\r\n\
#if DEVILX_HLSL_VERSION==0\r\n\
float2 mul(float2 v,float2x2 m){return v*m;}\r\n\
float3 mul(float2 v,float3x2 m){return v*m;}\r\n\
float4 mul(float2 v,float4x2 m){return v*m;}\r\n\
float2 mul(float3 v,float2x3 m){return v*m;}\r\n\
float3 mul(float3 v,float3x3 m){return v*m;}\r\n\
float4 mul(float3 v,float4x3 m){return v*m;}\r\n\
float2 mul(float4 v,float2x4 m){return v*m;}\r\n\
float3 mul(float4 v,float3x4 m){return v*m;}\r\n\
float4 mul(float4 v,float4x4 m){return v*m;}\r\n\
float2 mul(float2x2 m,float2 v){return m*v;}\r\n\
float2 mul(float3x2 m,float3 v){return m*v;}\r\n\
float2 mul(float4x2 m,float4 v){return m*v;}\r\n\
float3 mul(float2x3 m,float2 v){return m*v;}\r\n\
float3 mul(float3x3 m,float3 v){return m*v;}\r\n\
float3 mul(float4x3 m,float4 v){return m*v;}\r\n\
float4 mul(float2x4 m,float2 v){return m*v;}\r\n\
float4 mul(float3x4 m,float3 v){return m*v;}\r\n\
float4 mul(float4x4 m,float4 v){return m*v;}\r\n\
float2x2 mul(float2x2 m0,float2x2 m1){return m0*m1;}\r\n\
float3x3 mul(float3x3 m0,float3x3 m1){return m0*m1;}\r\n\
float4x4 mul(float4x4 m0,float4x4 m1){return m0*m1;}\r\n\
float saturate(float v){return clamp(v,0.0,1.0);}\r\n\
float2 saturate(float2 v){return clamp(v,float2(0.0),float2(1.0));}\r\n\
float3 saturate(float3 v){return clamp(v,float3(0.0),float3(1.0));}\r\n\
float4 saturate(float4 v){return clamp(v,float4(0.0),float4(1.0));}\r\n\
#endif\r\n\
float3x3 convert(float4x4 v)\r\n\
{\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	return (float3x3)v;\r\n\
#else\r\n\
	return float3x3(v);\r\n\
#endif\r\n\
}\r\n\
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x,v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x,v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcHemisphereLightFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	float cos_the=dot(vertexToLightDirection,worldNormal);\r\n\
	return cos_the*0.5+0.5;\r\n\
}\r\n\
float calcLambertDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcPhongSpecularFactor(float3 lightToVertexDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 reflect_dir=reflect(lightToVertexDirection,worldNormal);\r\n\
	float factor=saturate(dot(reflect_dir,vertexToCameraDirection));\r\n\
	return factor;\r\n\
}\r\n\
float calcBlinnPhongSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 half_vector = normalize(vertexToCameraDirection + vertexToLightDirection);\r\n\
	float specular_factor = saturate(dot(half_vector, worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
float3 calcSphericalHarmonicsLightFactor(float3 worldNormal)\r\n\
{\r\n\
	const float c1=0.429043;\r\n\
	const float c2=0.511664;\r\n\
	const float c3=0.743125;\r\n\
	const float c4=0.886227;\r\n\
	const float c5=0.247708;\r\n\
	const float3 l00=float3(0.871297,0.875222,0.864470);\r\n\
	const float3 l1m1=float3(0.175058,0.245335,0.312891);\r\n\
	const float3 l10=float3(0.034675,0.036107,0.037362);\r\n\
	const float3 l11=float3(-0.004629,-0.029448,-0.048028);\r\n\
	const float3 l2m2=float3(-0.120535,-0.121160,-0.117507);\r\n\
	const float3 l2m1=float3(0.003242,0.003624,0.007511);\r\n\
	const float3 l20=float3(-0.028667,-0.024926,-0.020998);\r\n\
	const float3 l21=float3(-0.077539,-0.086325,-0.091591);\r\n\
	const float3 l22=float3(-0.161784,-0.191783,0.219152);\r\n\
	float3 factor=c1*l22*(worldNormal.x*worldNormal.x-worldNormal.y*worldNormal.y)\r\n\
	+c3*l20*worldNormal.z*worldNormal.z\r\n\
	+c4*l00\r\n\
	-c5*l20\r\n\
	+2.0*c1*l2m2*worldNormal.x*worldNormal.y\r\n\
	+2.0*c1*l21*worldNormal.x*worldNormal.z\r\n\
	+2.0*c1*l2m1*worldNormal.y*worldNormal.z\r\n\
	+2.0*c2*l11*worldNormal.x\r\n\
	+2.0*c2*l1m1*worldNormal.y\r\n\
	+2.0*c2*l10*worldNormal.z;\r\n\
	return factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
	float factor=saturate((current - begin) * reciprocalRange);\r\n\
    return 1.0 - factor*factor;\r\n\
}\r\n\
float3 encodeNormal(float3 normal)\r\n\
{\r\n\
	return normal / getMaxComponment(normal);\r\n\
}\r\n\
float2 getQuadPosition(int vertexID)\r\n\
{\r\n\
    float2 ret;\r\n\
    if(0==vertexID)\r\n\
        ret = float2(-1.0, 1.0);\r\n\
    else if(1==vertexID)\r\n\
        ret = float2(1.0, 1.0);\r\n\
    else if(2==vertexID)\r\n\
        ret = float2(-1.0, -1.0);\r\n\
    else\r\n\
        ret = float2(1.0, -1.0);\r\n\
    return ret;\r\n\
}\r\n\
\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
\r\n\
in float3 gPositionVS;\r\n\
in float2 gMainUVVS;\r\n\
in float4 gDiffuseVS;\r\n\
out float2 gMainUVPS;\r\n\
out float4 gDiffusePS;\r\n\
void main()\r\n\
{\r\n\
#define iPosition gPositionVS\r\n\
#define iMainUV gMainUVVS\r\n\
#define iDiffuse gDiffuseVS\r\n\
#define oPosition gl_Position\r\n\
#define oMainUV gMainUVPS\r\n\
#define oDiffuse gDiffusePS\r\n\
	oPosition=float4(iPosition,1.0);\r\n\
	oMainUV=iMainUV;\r\n\
	oDiffuse=iDiffuse;\r\n\
}\r\n\
\r\n\
\r\n\
";
QueryShader_hlsl="#ifndef GLSL_VERSION\r\n\
	#define GLSL_VERSION 0\r\n\
#endif\r\n\
#ifndef GLSLES_VERSION\r\n\
	#define GLSLES_VERSION 0\r\n\
#endif\r\n\
#ifndef DEVILX_HLSL_VERSION\r\n\
	#define DEVILX_HLSL_VERSION 0\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)\r\n\
	#define float2 vec2\r\n\
	#define float3 vec3\r\n\
	#define float4 vec4\r\n\
	#define int2 ivec2\r\n\
	#define int3 ivec3\r\n\
	#define int4 ivec4\r\n\
	#define uint2 int2\r\n\
	#define uint3 int3\r\n\
	#define uint4 int4\r\n\
	#define float2x2 mat2\r\n\
	#define float2x3 mat2x3\r\n\
	#define float2x4 mat2x4\r\n\
	#define float3x2 mat3x2\r\n\
	#define float3x3 mat3\r\n\
	#define float3x4 mat3x4\r\n\
	#define float4x2 mat4x2\r\n\
	#define float4x3 mat4x3\r\n\
	#define float4x4 mat4\r\n\
	#define cbuffer layout(shared) uniform\r\n\
	#define lerp mix\r\n\
#endif\r\n\
#if (GLSL_VERSION>=300)||(GLSLES_VERSION>=300)||(DEVILX_HLSL_VERSION>=400)\r\n\
	#define DECL_CB(cb) cbuffer cb{\r\n\
	#define END_DECL };\r\n\
	#define CB_MEMBER uniform\r\n\
#else\r\n\
	#define DECL_CB(cb)\r\n\
	#define END_DECL\r\n\
	#define CB_MEMBER\r\n\
#endif\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) g##tex_name##Texture.Sample(g##tex_name##SamplerState,uv)\r\n\
#else\r\n\
	#define SAMPLE_TEXTURE(tex_name,uv) texture(g##tex_name##Texture,uv)\r\n\
#endif\r\n\
\r\n\
#if DEVILX_HLSL_VERSION==0\r\n\
float2 mul(float2 v,float2x2 m){return v*m;}\r\n\
float3 mul(float2 v,float3x2 m){return v*m;}\r\n\
float4 mul(float2 v,float4x2 m){return v*m;}\r\n\
float2 mul(float3 v,float2x3 m){return v*m;}\r\n\
float3 mul(float3 v,float3x3 m){return v*m;}\r\n\
float4 mul(float3 v,float4x3 m){return v*m;}\r\n\
float2 mul(float4 v,float2x4 m){return v*m;}\r\n\
float3 mul(float4 v,float3x4 m){return v*m;}\r\n\
float4 mul(float4 v,float4x4 m){return v*m;}\r\n\
float2 mul(float2x2 m,float2 v){return m*v;}\r\n\
float2 mul(float3x2 m,float3 v){return m*v;}\r\n\
float2 mul(float4x2 m,float4 v){return m*v;}\r\n\
float3 mul(float2x3 m,float2 v){return m*v;}\r\n\
float3 mul(float3x3 m,float3 v){return m*v;}\r\n\
float3 mul(float4x3 m,float4 v){return m*v;}\r\n\
float4 mul(float2x4 m,float2 v){return m*v;}\r\n\
float4 mul(float3x4 m,float3 v){return m*v;}\r\n\
float4 mul(float4x4 m,float4 v){return m*v;}\r\n\
float2x2 mul(float2x2 m0,float2x2 m1){return m0*m1;}\r\n\
float3x3 mul(float3x3 m0,float3x3 m1){return m0*m1;}\r\n\
float4x4 mul(float4x4 m0,float4x4 m1){return m0*m1;}\r\n\
float saturate(float v){return clamp(v,0.0,1.0);}\r\n\
float2 saturate(float2 v){return clamp(v,float2(0.0),float2(1.0));}\r\n\
float3 saturate(float3 v){return clamp(v,float3(0.0),float3(1.0));}\r\n\
float4 saturate(float4 v){return clamp(v,float4(0.0),float4(1.0));}\r\n\
#endif\r\n\
float3x3 convert(float4x4 v)\r\n\
{\r\n\
#if DEVILX_HLSL_VERSION\r\n\
	return (float3x3)v;\r\n\
#else\r\n\
	return float3x3(v);\r\n\
#endif\r\n\
}\r\n\
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x,v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x,getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x,v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x,getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=convert(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcHemisphereLightFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	float cos_the=dot(vertexToLightDirection,worldNormal);\r\n\
	return cos_the*0.5+0.5;\r\n\
}\r\n\
float calcLambertDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcPhongSpecularFactor(float3 lightToVertexDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 reflect_dir=reflect(lightToVertexDirection,worldNormal);\r\n\
	float factor=saturate(dot(reflect_dir,vertexToCameraDirection));\r\n\
	return factor;\r\n\
}\r\n\
float calcBlinnPhongSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)\r\n\
{\r\n\
	float3 half_vector = normalize(vertexToCameraDirection + vertexToLightDirection);\r\n\
	float specular_factor = saturate(dot(half_vector, worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
float3 calcSphericalHarmonicsLightFactor(float3 worldNormal)\r\n\
{\r\n\
	const float c1=0.429043;\r\n\
	const float c2=0.511664;\r\n\
	const float c3=0.743125;\r\n\
	const float c4=0.886227;\r\n\
	const float c5=0.247708;\r\n\
	const float3 l00=float3(0.871297,0.875222,0.864470);\r\n\
	const float3 l1m1=float3(0.175058,0.245335,0.312891);\r\n\
	const float3 l10=float3(0.034675,0.036107,0.037362);\r\n\
	const float3 l11=float3(-0.004629,-0.029448,-0.048028);\r\n\
	const float3 l2m2=float3(-0.120535,-0.121160,-0.117507);\r\n\
	const float3 l2m1=float3(0.003242,0.003624,0.007511);\r\n\
	const float3 l20=float3(-0.028667,-0.024926,-0.020998);\r\n\
	const float3 l21=float3(-0.077539,-0.086325,-0.091591);\r\n\
	const float3 l22=float3(-0.161784,-0.191783,0.219152);\r\n\
	float3 factor=c1*l22*(worldNormal.x*worldNormal.x-worldNormal.y*worldNormal.y)\r\n\
	+c3*l20*worldNormal.z*worldNormal.z\r\n\
	+c4*l00\r\n\
	-c5*l20\r\n\
	+2.0*c1*l2m2*worldNormal.x*worldNormal.y\r\n\
	+2.0*c1*l21*worldNormal.x*worldNormal.z\r\n\
	+2.0*c1*l2m1*worldNormal.y*worldNormal.z\r\n\
	+2.0*c2*l11*worldNormal.x\r\n\
	+2.0*c2*l1m1*worldNormal.y\r\n\
	+2.0*c2*l10*worldNormal.z;\r\n\
	return factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
	float factor=saturate((current - begin) * reciprocalRange);\r\n\
    return 1.0 - factor*factor;\r\n\
}\r\n\
float3 encodeNormal(float3 normal)\r\n\
{\r\n\
	return normal / getMaxComponment(normal);\r\n\
}\r\n\
float2 getQuadPosition(int vertexID)\r\n\
{\r\n\
    float2 ret;\r\n\
    if(0==vertexID)\r\n\
        ret = float2(-1.0, 1.0);\r\n\
    else if(1==vertexID)\r\n\
        ret = float2(1.0, 1.0);\r\n\
    else if(2==vertexID)\r\n\
        ret = float2(-1.0, -1.0);\r\n\
    else\r\n\
        ret = float2(1.0, -1.0);\r\n\
    return ret;\r\n\
}\r\n\
\r\n\
\r\n\
\r\n\
struct SVertexShaderInput\r\n\
{\r\n\
    float3 mPosition : SV_Position;\r\n\
    float2 mMainUV : TEXCOORD0;\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
};\r\n\
struct SVertexShaderOutput\r\n\
{\r\n\
    float4 mPosition : SV_Position;\r\n\
    float2 mMainUV : TEXCOORD0;\r\n\
    float4 mDiffuse : DIFFUSE;\r\n\
};\r\n\
SVertexShaderOutput vsMain(SVertexShaderInput input)\r\n\
{\r\n\
    SVertexShaderOutput output = (SVertexShaderOutput) 0;\r\n\
#define iPosition input.mPosition\r\n\
#define iMainUV input.mMainUV\r\n\
#define iDiffuse input.mDiffuse\r\n\
#define oPosition output.mPosition\r\n\
#define oMainUV output.mMainUV\r\n\
#define oDiffuse output.mDiffuse\r\n\
	oPosition=float4(iPosition,1.0);\r\n\
	oMainUV=iMainUV;\r\n\
	oDiffuse=iDiffuse;\r\n\
    return output;\r\n\
}\r\n\
SamplerState gDiffuseSamplerState;\r\n\
Texture2D<float4> gDiffuseTexture;\r\n\
struct SPixelShaderOutput\r\n\
{\r\n\
    float4 mColour : SV_Target;\r\n\
};\r\n\
SPixelShaderOutput psMain(SVertexShaderOutput input)\r\n\
{\r\n\
    SPixelShaderOutput output = (SPixelShaderOutput) 0;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);\r\n\
#endif\r\n\
#define iDiffuse input.mDiffuse\r\n\
#define oColour output.mColour\r\n\
oColour=iDiffuse;\r\n\
    return output;\r\n\
}\r\n\
\r\n\
\r\n\
";
}