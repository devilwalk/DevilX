#include "Defines.sl"
#if HLSL_VERSION==0
float2 mul(float2 v,float2x2 m){return v*m;}
float3 mul(float2 v,float3x2 m){return v*m;}
float4 mul(float2 v,float4x2 m){return v*m;}
float2 mul(float3 v,float2x3 m){return v*m;}
float3 mul(float3 v,float3x3 m){return v*m;}
float4 mul(float3 v,float4x3 m){return v*m;}
float2 mul(float4 v,float2x4 m){return v*m;}
float3 mul(float4 v,float3x4 m){return v*m;}
float4 mul(float4 v,float4x4 m){return v*m;}
float2 mul(float2x2 m,float2 v){return m*v;}
float2 mul(float3x2 m,float3 v){return m*v;}
float2 mul(float4x2 m,float4 v){return m*v;}
float3 mul(float2x3 m,float2 v){return m*v;}
float3 mul(float3x3 m,float3 v){return m*v;}
float3 mul(float4x3 m,float4 v){return m*v;}
float4 mul(float2x4 m,float2 v){return m*v;}
float4 mul(float3x4 m,float3 v){return m*v;}
float4 mul(float4x4 m,float4 v){return m*v;}
float2x2 mul(float2x2 m0,float2x2 m1){return m0*m1;}
float3x3 mul(float3x3 m0,float3x3 m1){return m0*m1;}
float4x4 mul(float4x4 m0,float4x4 m1){return m0*m1;}
float saturate(float v){return clamp(v,0.0,1.0);}
float2 saturate(float2 v){return clamp(v,float2(0.0),float2(1.0));}
float3 saturate(float3 v){return clamp(v,float3(0.0),float3(1.0));}
float4 saturate(float4 v){return clamp(v,float4(0.0),float4(1.0));}
#endif
float3x3 convert(float4x4 v)
{
#if HLSL_VERSION
	return (float3x3)v;
#else
	return float3x3(v);
#endif
}
float getMaxComponment(float2 v)
{
	return max(v.x,v.y);
}
float getMaxComponment(float3 v)
{
	return max(v.x,getMaxComponment(v.yz));
}
float getMaxComponment(float4 v)
{
	return max(v.x,getMaxComponment(v.yzw));
}
float getMinComponment(float2 v)
{
	return min(v.x,v.y);
}
float getMinComponment(float3 v)
{
	return min(v.x,getMinComponment(v.yz));
}
float getMinComponment(float4 v)
{
	return min(v.x,getMinComponment(v.yzw));
}
float3 getCameraPosition(float4x4 viewMatrix)
{
	return -viewMatrix[3].xyz;
}
float3 getCameraDirection(float4x4 viewMatrix)
{
	float3x3 rot=convert(viewMatrix);
	return rot[2];
}
float3 getCameraUp(float4x4 viewMatrix)
{
	float3x3 rot=convert(viewMatrix);
	return rot[1];
}
float3 getCameraRight(float4x4 viewMatrix)
{
	float3x3 rot=convert(viewMatrix);
	return rot[0];
}
float calcHemisphereLightFactor(float3 vertexToLightDirection,float3 worldNormal)
{
	float cos_the=dot(vertexToLightDirection,worldNormal);
	return cos_the*0.5+0.5;
}
float calcLambertDiffuseFactor(float3 vertexToLightDirection,float3 worldNormal)
{
	return saturate(dot(vertexToLightDirection,worldNormal));
}
float calcPhongSpecularFactor(float3 lightToVertexDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)
{
	float3 reflect_dir=reflect(lightToVertexDirection,worldNormal);
	float factor=saturate(dot(reflect_dir,vertexToCameraDirection));
	return factor;
}
float calcBlinnPhongSpecularFactor(float3 vertexToLightDirection,float3 worldNormal,float3 worldPosition,float3 vertexToCameraDirection)
{
	float3 half_vector = normalize(vertexToCameraDirection + vertexToLightDirection);
	float specular_factor = saturate(dot(half_vector, worldNormal));
	return specular_factor;
}
float3 calcSphericalHarmonicsLightFactor(float3 worldNormal)
{
	const float c1=0.429043;
	const float c2=0.511664;
	const float c3=0.743125;
	const float c4=0.886227;
	const float c5=0.247708;
	const float3 l00=float3(0.871297,0.875222,0.864470);
	const float3 l1m1=float3(0.175058,0.245335,0.312891);
	const float3 l10=float3(0.034675,0.036107,0.037362);
	const float3 l11=float3(-0.004629,-0.029448,-0.048028);
	const float3 l2m2=float3(-0.120535,-0.121160,-0.117507);
	const float3 l2m1=float3(0.003242,0.003624,0.007511);
	const float3 l20=float3(-0.028667,-0.024926,-0.020998);
	const float3 l21=float3(-0.077539,-0.086325,-0.091591);
	const float3 l22=float3(-0.161784,-0.191783,0.219152);
	float3 factor=c1*l22*(worldNormal.x*worldNormal.x-worldNormal.y*worldNormal.y)
	+c3*l20*worldNormal.z*worldNormal.z
	+c4*l00
	-c5*l20
	+2.0*c1*l2m2*worldNormal.x*worldNormal.y
	+2.0*c1*l21*worldNormal.x*worldNormal.z
	+2.0*c1*l2m1*worldNormal.y*worldNormal.z
	+2.0*c2*l11*worldNormal.x
	+2.0*c2*l1m1*worldNormal.y
	+2.0*c2*l10*worldNormal.z;
	return factor;
}
//return 1意味着无衰减，return 0意味着完全衰减
float calcFalloffFactor(float current, float begin, float reciprocalRange)
{
	float factor=saturate((current - begin) * reciprocalRange);
    return 1.0 - factor*factor;
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