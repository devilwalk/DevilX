#include "ConstantBuffer.hlsl"
float getMaxComponment(float2 v)
{
	return max(v.x, v.y);
}
float getMaxComponment(float3 v)
{
	return max(v.x, getMaxComponment(v.yz));
}
float getMaxComponment(float4 v)
{
	return max(v.x, getMaxComponment(v.yzw));
}
float getMinComponment(float2 v)
{
	return min(v.x, v.y);
}
float getMinComponment(float3 v)
{
	return min(v.x, getMinComponment(v.yz));
}
float getMinComponment(float4 v)
{
	return min(v.x, getMinComponment(v.yzw));
}
float3 getCameraPosition(float4x4 viewMatrix)
{
	return -viewMatrix[3].xyz;
}
float3 getCameraPosition()
{
	return getCameraPosition(gViewMatrix);
}
float3 getCameraDirection(float4x4 viewMatrix)
{
	float3x3 rot = (float3x3) viewMatrix;
	return rot[2];
}
float3 getCameraDirection()
{
	return getCameraDirection(gViewMatrix);
}
float3 getCameraUp(float4x4 viewMatrix)
{
	float3x3 rot = (float3x3) viewMatrix;
	return rot[1];
}
float3 getCameraUp()
{
	return getCameraUp(gViewMatrix);
}
float3 getCameraRight(float4x4 viewMatrix)
{
	float3x3 rot = (float3x3) viewMatrix;
	return rot[0];
}
float3 getCameraRight()
{
	return getCameraRight(gViewMatrix);
}
float calcDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)
{
	return saturate(dot(vertexToLightDirection, worldNormal));
}
float calcSpecularFactor(float3 vertexToLightDirection, float3 worldNormal, float3 worldPosition, float3 cameraPosition)
{
	float3 half_vector = normalize(normalize(cameraPosition - worldPosition) + vertexToLightDirection);
	float specular_factor = saturate(dot(half_vector, worldNormal));
	return specular_factor;
}
//return 1意味着无衰减，return 0意味着完全衰减
float calcFalloffFactor(float current, float begin, float reciprocalRange)
{
    return 1.0 - pow(saturate((current - begin) * reciprocalRange), 2);
}
float3 encodeNormal(float3 normal)
{
	return normal / getMaxComponment(normal);
}
float2 getQuadPosition(int vertexID)
{
    float2 ret;
    if(0==vertexID)
        ret = float2(-1.0, 1.0);
    else if(1==vertexID)
        ret = float2(1.0, 1.0);
    else if(2==vertexID)
        ret = float2(-1.0, -1.0);
    else
        ret = float2(1.0, -1.0);
    return ret;
}