#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLSL4_5;
NSDevilX::NSRenderSystem::NSGLSL4_5::CDefinitionShader::CDefinitionShader()
{
cbLight="#define float2 vec2\r\n\
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
cbuffer cbDirectionLight\r\n\
{\r\n\
    float3 gDirectionLightDiffuseColour;\r\n\
    float3 gDirectionLightSpecularColour;\r\n\
    float3 gDirectionLightDirection;\r\n\
};\r\n\
cbuffer cbPointLight\r\n\
{\r\n\
    float3 gPointLightDiffuseColour;\r\n\
    float3 gPointLightSpecularColour;\r\n\
    float3 gPointLightPosition;\r\n\
    float gPointLightReciprocalRange;\r\n\
    float gPointLightStartFallOffDistance;\r\n\
};\r\n\
cbuffer cbSpotLight\r\n\
{\r\n\
    float3 gSpotLightDiffuseColour;\r\n\
    float3 gSpotLightSpecularColour;\r\n\
    float3 gSpotLightDirection;\r\n\
    float3 gSpotLightPosition;\r\n\
    float gSpotLightReciprocalRange;\r\n\
    float gSpotLightStartFallOffDistance;\r\n\
    float gSpotLightCosInnerCornerHalfAngle;\r\n\
    float gSpotLightReciprocalDeltaCosHalfAngle;\r\n\
};\r\n\
";
cbObject="#define float2 vec2\r\n\
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
cbuffer cbObjectTransform\r\n\
{\r\n\
    float4x4 gWorldMatrix;\r\n\
};\r\n\
cbuffer cbObjectMaterial\r\n\
{\r\n\
    float3 gMainColour;\r\n\
    float gAlpha;\r\n\
    float3 gSpecularColour;\r\n\
    float gSpecularPower;\r\n\
    float3 gEmissiveColour;\r\n\
    float gAlphaTestValue;\r\n\
};";
cbShadow="#define float2 vec2\r\n\
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
cbuffer cbShadowMap0\r\n\
{\r\n\
    float4x4 gShadowMap0ViewProjectionMatrix;\r\n\
    float gShadowMap0FarDistance;\r\n\
    float gShadowMap0InverseFarDistance;\r\n\
};\r\n\
cbuffer cbShadowMap1\r\n\
{\r\n\
    float4x4 gShadowMap1ViewProjectionMatrix;\r\n\
    float gShadowMap1FarDistance;\r\n\
    float gShadowMap1InverseFarDistance;\r\n\
};\r\n\
cbuffer cbShadowMap2\r\n\
{\r\n\
    float4x4 gShadowMap2ViewProjectionMatrix;\r\n\
    float gShadowMap2FarDistance;\r\n\
    float gShadowMap2InverseFarDistance;\r\n\
};\r\n\
cbuffer cbShadowMap3\r\n\
{\r\n\
    float4x4 gShadowMap3ViewProjectionMatrix;\r\n\
    float gShadowMap3FarDistance;\r\n\
    float gShadowMap3InverseFarDistance;\r\n\
};\r\n\
";
ClearViewportPixel="#define float2 vec2\r\n\
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
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector=normalize(normalize(cameraPosition-worldPosition)+vertexToLightDirection);\r\n\
	float specular_factor=saturate(dot(half_vector,worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
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
cbuffer cbClearViewport\r\n\
{\r\n\
    float4 gClearColour0;\r\n\
    float4 gClearColour1;\r\n\
    float4 gClearColour2;\r\n\
    float4 gClearColour3;\r\n\
    float4 gClearColour4;\r\n\
    float4 gClearColour5;\r\n\
    float4 gClearColour6;\r\n\
    float4 gClearColour7;\r\n\
    float gClearDepth;\r\n\
};\r\n\
layout(location=0) out float4 outColour0;\r\n\
layout(location=1) out float4 outColour1;\r\n\
layout(location=2) out float4 outColour2;\r\n\
layout(location=3) out float4 outColour3;\r\n\
layout(location=4) out float4 outColour4;\r\n\
layout(location=5) out float4 outColour5;\r\n\
layout(location=6) out float4 outColour6;\r\n\
layout(location=7) out float4 outColour7;\r\n\
void main()\r\n\
{\r\n\
    outColour0 = gClearColour0;\r\n\
    outColour1 = gClearColour1;\r\n\
    outColour2 = gClearColour2;\r\n\
    outColour3 = gClearColour3;\r\n\
    outColour4 = gClearColour4;\r\n\
    outColour5 = gClearColour5;\r\n\
    outColour6 = gClearColour6;\r\n\
    outColour7 = gClearColour7;\r\n\
}";
ClearViewportVertex="#define float2 vec2\r\n\
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
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector=normalize(normalize(cameraPosition-worldPosition)+vertexToLightDirection);\r\n\
	float specular_factor=saturate(dot(half_vector,worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
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
cbuffer cbClearViewport\r\n\
{\r\n\
    float4 gClearColour0;\r\n\
    float4 gClearColour1;\r\n\
    float4 gClearColour2;\r\n\
    float4 gClearColour3;\r\n\
    float4 gClearColour4;\r\n\
    float4 gClearColour5;\r\n\
    float4 gClearColour6;\r\n\
    float4 gClearColour7;\r\n\
    float gClearDepth;\r\n\
};\r\n\
void main()\r\n\
{\r\n\
    float depth = gClearDepth;\r\n\
    gl_Position = float4(getQuadPosition(gl_VertexID), depth, 1.0);\r\n\
}\r\n\
";
ConstantBuffer="#define float2 vec2\r\n\
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
cbuffer cbSystem\r\n\
{\r\n\
    float gFrameTimeInSeconds;\r\n\
    float gInverseFrameTimeInSeconds;\r\n\
};\r\n\
cbuffer cbRenderTarget\r\n\
{\r\n\
    float2 gRenderTargetSizeInPixel;\r\n\
    float2 gInverseRenderTargetSizeInPixel;\r\n\
};\r\n\
cbuffer cbViewport\r\n\
{\r\n\
    float2 gViewportSizeInPixel;\r\n\
    float2 gInverseViewportSizeInPixel;\r\n\
};\r\n\
cbuffer cbCamera\r\n\
{\r\n\
    float4x4 gViewMatrix;\r\n\
    float4x4 gInverseViewMatrix;\r\n\
    float4x4 gProjectionMatrix;\r\n\
    float4x4 gInverseProjectionMatrix;\r\n\
    float4x4 gViewProjectionMatrix;\r\n\
    float4x4 gInverseViewProjectionMatrix;\r\n\
    float gFarDistance;\r\n\
    float gInverseFarDistance;\r\n\
};\r\n\
cbuffer cbScene\r\n\
{\r\n\
    float3 gAmbientColour;\r\n\
};";
DeferredLightingGBufferShader="#define float2 vec2\r\n\
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
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector=normalize(normalize(cameraPosition-worldPosition)+vertexToLightDirection);\r\n\
	float specular_factor=saturate(dot(half_vector,worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
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
#ifndef OUTPUT_WORLD_TANGENT\r\n\
#define OUTPUT_WORLD_TANGENT 0\r\n\
#endif\r\n\
#ifndef OUTPUT_MAIN_UV\r\n\
#define OUTPUT_MAIN_UV 0\r\n\
#endif\r\n\
struct SVertexShaderInput\r\n\
{\r\n\
	float3 mPosition : SV_Position;\r\n\
	float3 mNormal : NORMAL;\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mTangent : TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
};\r\n\
struct SVertexShaderOutput\r\n\
{\r\n\
	float4 mPosition : SV_Position;\r\n\
	float3 mWorldNormal : WORLD_NORMAL;\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mWorldTangent : WORLD_TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
};\r\n\
SVertexShaderOutput vsMain(SVertexShaderInput input)\r\n\
{\r\n\
	SVertexShaderOutput output;\r\n\
	output.mPosition = mul(gViewProjectionMatrix, mul(gWorldMatrix, float4(input.mPosition, 1.0)));\r\n\
	output.mWorldNormal = mul((float3x3)gWorldMatrix, input.mNormal);\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	output.mWorldTangent = mul((float3x3)gWorldMatrix, input.mTangent);\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	output.mMainUV = input.mMainUV;\r\n\
#endif\r\n\
	return output;\r\n\
}\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_NORMAL_TEXTURE\r\n\
#define USE_NORMAL_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_ALPHA_TEST\r\n\
#define USE_ALPHA_TEST 0\r\n\
#endif\r\n\
SamplerState gDiffuseSamplerState;\r\n\
SamplerState gNormalSamplerState;\r\n\
Texture2D<float4> gDiffuseTexture;\r\n\
Texture2D<float4> gNormalTexture;\r\n\
struct SPixelShaderOutput\r\n\
{\r\n\
	float4 mNormal : SV_Target0;\r\n\
	float4 mDepth : SV_Target1;\r\n\
};\r\n\
SPixelShaderOutput psMain(SVertexShaderOutput input)\r\n\
{\r\n\
	SPixelShaderOutput output;\r\n\
	float alpha = gAlpha;\r\n\
	float3 world_normal = normalize(input.mWorldNormal);\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);\r\n\
	float diffuse_texture_alpha = diffuse_texture_colour.a;\r\n\
	alpha *= diffuse_texture_alpha;\r\n\
#endif\r\n\
#if USE_ALPHA_TEST\r\n\
	clip(alpha - gAlphaTestValue);\r\n\
#endif\r\n\
#if USE_NORMAL_TEXTURE\r\n\
	float4 normal_texture_sampler = gNormalTexture.Sample(gNormalSamplerState, input.mMainUV);\r\n\
	float3 normal_texture_normal = normal_texture_sampler.xyz * 2.0 - 1.0;\r\n\
	float3 world_tangent = normalize(input.mWorldTangent);\r\n\
	float3 world_binormal = cross(world_normal, world_tangent);\r\n\
	float3x3 tbn = float3x3(world_tangent, world_binormal, world_normal);\r\n\
	world_normal = mul(tbn, normal_texture_normal);\r\n\
#endif\r\n\
	output.mNormal.xyz = encodeNormal(world_normal);\r\n\
	output.mNormal.w = 0;\r\n\
	output.mDepth = input.mPosition.w * gInverseFarDistance;\r\n\
	return output;\r\n\
}";
DeferredShadingGBufferShader="#define float2 vec2\r\n\
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
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector=normalize(normalize(cameraPosition-worldPosition)+vertexToLightDirection);\r\n\
	float specular_factor=saturate(dot(half_vector,worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
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
#ifndef OUTPUT_WORLD_TANGENT\r\n\
#define OUTPUT_WORLD_TANGENT 0\r\n\
#endif\r\n\
#ifndef OUTPUT_MAIN_UV\r\n\
#define OUTPUT_MAIN_UV 0\r\n\
#endif\r\n\
struct SVertexShaderInput\r\n\
{\r\n\
	float3 mPosition : SV_Position;\r\n\
	float3 mNormal : NORMAL;\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mTangent : TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
};\r\n\
struct SVertexShaderOutput\r\n\
{\r\n\
	float4 mPosition : SV_Position;\r\n\
	float3 mWorldNormal : WORLD_NORMAL;\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	float3 mWorldTangent : WORLD_TANGENT;\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	float2 mMainUV : TEXCOORD0;\r\n\
#endif\r\n\
};\r\n\
SVertexShaderOutput vsMain(SVertexShaderInput input)\r\n\
{\r\n\
	SVertexShaderOutput output;\r\n\
	output.mPosition = mul(gViewProjectionMatrix, mul(gWorldMatrix, float4(input.mPosition, 1.0)));\r\n\
	output.mWorldNormal = mul((float3x3)gWorldMatrix, input.mNormal);\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	output.mWorldTangent = mul((float3x3)gWorldMatrix, input.mTangent);\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	output.mMainUV = input.mMainUV;\r\n\
#endif\r\n\
	return output;\r\n\
}\r\n\
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_NORMAL_TEXTURE\r\n\
#define USE_NORMAL_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_ALPHA_TEST\r\n\
#define USE_ALPHA_TEST 0\r\n\
#endif\r\n\
SamplerState gDiffuseSamplerState;\r\n\
SamplerState gNormalSamplerState;\r\n\
Texture2D<float4> gDiffuseTexture;\r\n\
Texture2D<float4> gNormalTexture;\r\n\
struct SPixelShaderOutput\r\n\
{\r\n\
	float4 mColour : SV_Target0;\r\n\
	float4 mSpecular : SV_Target1;\r\n\
	float4 mNormal : SV_Target2;\r\n\
	float4 mDepth : SV_Target3;\r\n\
};\r\n\
SPixelShaderOutput psMain(SVertexShaderOutput input)\r\n\
{\r\n\
	SPixelShaderOutput output;\r\n\
	float3 colour_main = gMainColour;\r\n\
	float3 colour_specular = gSpecularColour;\r\n\
	float alpha = gAlpha;\r\n\
	float3 world_normal = normalize(input.mWorldNormal);\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, input.mMainUV);\r\n\
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;\r\n\
	float diffuse_texture_alpha = diffuse_texture_colour.a;\r\n\
	alpha *= diffuse_texture_alpha;\r\n\
	colour_main *= diffuse_texture_colour;\r\n\
#endif\r\n\
#if USE_ALPHA_TEST\r\n\
	clip(alpha - gAlphaTestValue);\r\n\
#endif\r\n\
#if USE_NORMAL_TEXTURE\r\n\
	float4 normal_texture_sampler = gNormalTexture.Sample(gNormalSamplerState, input.mMainUV);\r\n\
	float3 normal_texture_normal = normal_texture_sampler.xyz * 2.0 - 1.0;\r\n\
	float3 world_tangent = normalize(input.mWorldTangent);\r\n\
	float3 world_binormal = cross(world_normal, world_tangent);\r\n\
	float3x3 tbn = float3x3(world_tangent, world_binormal, world_normal);\r\n\
	world_normal = mul(tbn, normal_texture_normal);\r\n\
#endif\r\n\
	output.mColour.a = alpha;\r\n\
	output.mColour.rgb = colour_main;\r\n\
	output.mSpecular.rgb = colour_specular;\r\n\
	output.mSpecular.a = gSpecularPower;\r\n\
	output.mNormal.xyz = encodeNormal(world_normal);\r\n\
	output.mNormal.w = 0;\r\n\
	output.mDepth = input.mPosition.w * gInverseFarDistance;\r\n\
	return output;\r\n\
}";
Defines="#define float2 vec2\r\n\
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
#define cbuffer layout(shared) uniform";
ForwardShaderCommon="#define float2 vec2\r\n\
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
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector=normalize(normalize(cameraPosition-worldPosition)+vertexToLightDirection);\r\n\
	float specular_factor=saturate(dot(half_vector,worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
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
#endif";
ForwardShaderPixel="#define float2 vec2\r\n\
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
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector=normalize(normalize(cameraPosition-worldPosition)+vertexToLightDirection);\r\n\
	float specular_factor=saturate(dot(half_vector,worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
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
SamplerState gDiffuseSamplerState;\r\n\
SamplerState gNormalSamplerState;\r\n\
Texture2D<float4> gDiffuseTexture;\r\n\
Texture2D<float4> gNormalTexture;\r\n\
out float4 gFragColour;\r\n\
void main()\r\n\
{\r\n\
	float3 colour_emissive = gEmissiveColour;\r\n\
	float3 colour_diffuse_factor = gMainColour;\r\n\
    float3 colour_specular_factor = gSpecularColour;\r\n\
    float alpha = gAlpha;\r\n\
#if OUTPUT_DIFFUSE\r\n\
    colour_emissive *= gDiffusePS.rgb;\r\n\
    colour_diffuse_factor *= gDiffusePS.rgb;\r\n\
    alpha *= gDiffusePS.a;\r\n\
#endif\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler = gDiffuseTexture.Sample(gDiffuseSamplerState, gMainUVPS);\r\n\
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;\r\n\
	float diffuse_texture_alpha = diffuse_texture_sampler.a;\r\n\
	alpha *= diffuse_texture_alpha;\r\n\
	colour_diffuse_factor *= diffuse_texture_colour;\r\n\
	colour_emissive *= diffuse_texture_colour;\r\n\
#endif\r\n\
#if USE_ALPHA_TEST\r\n\
	if(alpha - gAlphaTestValue<=0.0)\r\n\
		discard;\r\n\
#endif\r\n\
#if USE_LIGHTING\r\n\
    #if USE_DIRECTION_LIGHT||USE_POINT_LIGHT||USE_SPOT_LIGHT\r\n\
    float3 lighting_colour=0;\r\n\
    float lighting_falloff_factor=1.0;\r\n\
	float3 world_normal=normalize(gWorldNormalPS);\r\n\
		#if USE_NORMAL_TEXTURE\r\n\
	float4 normal_texture_sampler=gNormalTexture.Sample(gNormalSamplerState,gMainUVPS);\r\n\
	float3 normal_texture_normal=normal_texture_sampler.xyz * 2.0-1.0;\r\n\
	float3 world_tangent=normalize(gWorldTangentPS);\r\n\
	float3 world_binormal=cross(world_normal,world_tangent);\r\n\
	float3x3 tbn=float3x3(world_tangent,world_binormal,world_normal);\r\n\
	world_normal=mul(tbn,normal_texture_normal);\r\n\
		#endif\r\n\
		#if USE_DIRECTION_LIGHT\r\n\
	float3 vertex_to_light_direction = -gDirectionLightDirection;\r\n\
    float3 light_diffuse_colour = gDirectionLightDiffuseColour;\r\n\
    float3 light_specular_colour = gDirectionLightSpecularColour;\r\n\
	    #elif USE_POINT_LIGHT\r\n\
    float3 vertex_to_light = gPointLightPosition - gWorldPositionPS;\r\n\
    lighting_falloff_factor=calcFalloffFactor(length(vertex_to_light),gPointLightStartFallOffDistance,gPointLightReciprocalRange);\r\n\
	float3 vertex_to_light_direction = normalize(vertex_to_light);\r\n\
    float3 light_diffuse_colour = gPointLightDiffuseColour;\r\n\
    float3 light_specular_colour = gPointLightSpecularColour;\r\n\
	    #elif USE_SPOT_LIGHT\r\n\
    float3 vertex_to_light = gSpotLightPosition - gWorldPositionPS;\r\n\
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
	float lighting_specular_factor=calcSpecularFactor(vertex_to_light_direction,world_normal,gWorldPositionPS,getCameraPosition());\r\n\
	float3 lighting_specular_colour=lighting_diffuse_factor > 0.0?pow(lighting_specular_factor,gSpecularPower) * light_specular_colour:0.0;\r\n\
	lighting_colour+=lighting_specular_colour;\r\n\
		#endif\r\n\
    gFragColour.rgb+=lighting_colour*lighting_falloff_factor*colour_diffuse_factor;\r\n\
	#else\r\n\
	gFragColour.rgb+=gAmbientColour*colour_diffuse_factor;\r\n\
	gFragColour.rgb+=colour_emissive;\r\n\
	#endif\r\n\
#else\r\n\
	gFragColour.rgb += colour_emissive;\r\n\
#endif\r\n\
	gFragColour.a = alpha;\r\n\
}";
ForwardShaderVertex="#define float2 vec2\r\n\
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
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector=normalize(normalize(cameraPosition-worldPosition)+vertexToLightDirection);\r\n\
	float specular_factor=saturate(dot(half_vector,worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
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
    float4 world_position = mul(gWorldMatrix, float4(gPositionVS, 1.0));\r\n\
    gl_Position = mul(gViewProjectionMatrix, world_position);\r\n\
#if OUTPUT_WORLD_POSITION\r\n\
	gWorldPositionPS = world_position.xyz;\r\n\
#endif\r\n\
#if OUTPUT_WORLD_NORMAL\r\n\
	gWorldNormalPS = mul(float3x3(gWorldMatrix), gNormalVS);\r\n\
#endif\r\n\
#if OUTPUT_WORLD_TANGENT\r\n\
	gWorldTangentPS = mul(float3x3(gWorldMatrix), gTangentVS);\r\n\
#endif\r\n\
#if OUTPUT_MAIN_UV\r\n\
	gMainUVPS = gMainUVVS;\r\n\
#endif\r\n\
#if OUTPUT_DIFFUSE\r\n\
	gDiffusePS = gDiffuseVS;\r\n\
#endif\r\n\
}\r\n\
";
Function="#define float2 vec2\r\n\
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
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector=normalize(normalize(cameraPosition-worldPosition)+vertexToLightDirection);\r\n\
	float specular_factor=saturate(dot(half_vector,worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
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
}";
FunctionEx="#define float2 vec2\r\n\
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
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector=normalize(normalize(cameraPosition-worldPosition)+vertexToLightDirection);\r\n\
	float specular_factor=saturate(dot(half_vector,worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
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
";
OverlayShaderPixel="#define float2 vec2\r\n\
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
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector=normalize(normalize(cameraPosition-worldPosition)+vertexToLightDirection);\r\n\
	float specular_factor=saturate(dot(half_vector,worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
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
#ifndef USE_DIFFUSE_TEXTURE\r\n\
#define USE_DIFFUSE_TEXTURE 0\r\n\
#endif\r\n\
#ifndef USE_FONT_TEXTURE\r\n\
#define USE_FONT_TEXTURE 0\r\n\
#endif\r\n\
in float4 gPositionPS;\r\n\
in float2 gMainUVPS;\r\n\
in float4 gDiffusePS;\r\n\
#if USE_DIFFUSE_TEXTURE || USE_FONT_TEXTURE\r\n\
uniform sampler2D gDiffuseTexture;\r\n\
#endif\r\n\
out float4 gFragColour;\r\n\
void main()\r\n\
{\r\n\
    float3 colour_emissive = gDiffusePS.rgb;\r\n\
    float alpha = gDiffusePS.a;\r\n\
#if USE_DIFFUSE_TEXTURE\r\n\
	float4 diffuse_texture_sampler =texture(gDiffuseTexture, gMainUVPS);\r\n\
	float3 diffuse_texture_colour = diffuse_texture_sampler.rgb;\r\n\
	float diffuse_texture_alpha = diffuse_texture_sampler.a;\r\n\
	alpha *= diffuse_texture_alpha;\r\n\
	colour_emissive *= diffuse_texture_colour;\r\n\
#endif\r\n\
#if USE_FONT_TEXTURE\r\n\
	alpha*=texture(gDiffuseTexture,gMainUVPS).r;\r\n\
#endif\r\n\
    gFragColour.rgb = colour_emissive;\r\n\
    gFragColour.a = alpha;\r\n\
}";
OverlayShaderVertex="#define float2 vec2\r\n\
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
float getMaxComponment(float2 v)\r\n\
{\r\n\
	return max(v.x, v.y);\r\n\
}\r\n\
float getMaxComponment(float3 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yz));\r\n\
}\r\n\
float getMaxComponment(float4 v)\r\n\
{\r\n\
	return max(v.x, getMaxComponment(v.yzw));\r\n\
}\r\n\
float getMinComponment(float2 v)\r\n\
{\r\n\
	return min(v.x, v.y);\r\n\
}\r\n\
float getMinComponment(float3 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yz));\r\n\
}\r\n\
float getMinComponment(float4 v)\r\n\
{\r\n\
	return min(v.x, getMinComponment(v.yzw));\r\n\
}\r\n\
float3 getCameraPosition(float4x4 viewMatrix)\r\n\
{\r\n\
	return -viewMatrix[3].xyz;\r\n\
}\r\n\
float3 getCameraDirection(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[2];\r\n\
}\r\n\
float3 getCameraUp(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[1];\r\n\
}\r\n\
float3 getCameraRight(float4x4 viewMatrix)\r\n\
{\r\n\
	float3x3 rot=float3x3(viewMatrix);\r\n\
	return rot[0];\r\n\
}\r\n\
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)\r\n\
{\r\n\
	return saturate(dot(vertexToLightDirection,worldNormal));\r\n\
}\r\n\
float calcSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 cameraPosition)\r\n\
{\r\n\
	float3 half_vector=normalize(normalize(cameraPosition-worldPosition)+vertexToLightDirection);\r\n\
	float specular_factor=saturate(dot(half_vector,worldNormal));\r\n\
	return specular_factor;\r\n\
}\r\n\
//return 1意味着无衰减，return 0意味着完全衰减\r\n\
float calcFalloffFactor(float current, float begin, float reciprocalRange)\r\n\
{\r\n\
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);\r\n\
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
in float3 gPositionVS;\r\n\
in float2 gMainUVVS;\r\n\
in float4 gDiffuseVS;\r\n\
out float2 gMainUVPS;\r\n\
out float4 gDiffusePS;\r\n\
void main()\r\n\
{\r\n\
    gl_Position = float4(gPositionVS, 1.0);\r\n\
	gMainUVPS = gMainUVVS;\r\n\
	gDiffusePS = gDiffuseVS;\r\n\
}\r\n\
";
}