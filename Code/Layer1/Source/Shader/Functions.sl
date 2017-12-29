#include "Defines.sl"
#if DEVILX_HLSL_VERSION==0
float2 mul(float2 v, float2x2 m)
{
    return v * m;
}
float3 mul(float2 v, float3x2 m)
{
    return v * m;
}
float4 mul(float2 v, float4x2 m)
{
    return v * m;
}
float2 mul(float3 v, float2x3 m)
{
    return v * m;
}
float3 mul(float3 v, float3x3 m)
{
    return v * m;
}
float4 mul(float3 v, float4x3 m)
{
    return v * m;
}
float2 mul(float4 v, float2x4 m)
{
    return v * m;
}
float3 mul(float4 v, float3x4 m)
{
    return v * m;
}
float4 mul(float4 v, float4x4 m)
{
    return v * m;
}
float2 mul(float2x2 m, float2 v)
{
    return m * v;
}
float2 mul(float3x2 m, float3 v)
{
    return m * v;
}
float2 mul(float4x2 m, float4 v)
{
    return m * v;
}
float3 mul(float2x3 m, float2 v)
{
    return m * v;
}
float3 mul(float3x3 m, float3 v)
{
    return m * v;
}
float3 mul(float4x3 m, float4 v)
{
    return m * v;
}
float4 mul(float2x4 m, float2 v)
{
    return m * v;
}
float4 mul(float3x4 m, float3 v)
{
    return m * v;
}
float4 mul(float4x4 m, float4 v)
{
    return m * v;
}
float2x2 mul(float2x2 m0, float2x2 m1)
{
    return m0 * m1;
}
float3x3 mul(float3x3 m0, float3x3 m1)
{
    return m0 * m1;
}
float4x4 mul(float4x4 m0, float4x4 m1)
{
    return m0 * m1;
}
float saturate(float v)
{
    return clamp(v, 0.0, 1.0);
}
float2 saturate(float2 v)
{
    return clamp(v, float2(0.0), float2(1.0));
}
float3 saturate(float3 v)
{
    return clamp(v, float3(0.0), float3(1.0));
}
float4 saturate(float4 v)
{
    return clamp(v, float4(0.0), float4(1.0));
}
#endif
float3x3 convert(float4x4 v)
{
#if DEVILX_HLSL_VERSION
	return (float3x3)v;
#else
    return float3x3(v);
#endif
}
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
float3 getCameraDirection(float4x4 viewMatrix)
{
    float3x3 rot = convert(viewMatrix);
    return rot[2];
}
float3 getCameraUp(float4x4 viewMatrix)
{
    float3x3 rot = convert(viewMatrix);
    return rot[1];
}
float3 getCameraRight(float4x4 viewMatrix)
{
    float3x3 rot = convert(viewMatrix);
    return rot[0];
}
//---------------------------------------ambient-----------------------------------------------
float calcHemisphereAmbientFactor(float3 vertexToLightDirection, float3 worldNormal)
{
    float cos_the = dot(vertexToLightDirection, worldNormal);
    return cos_the * 0.5 + 0.5;
}
float3 calcSphericalHarmonicsAmbientFactor(float3 worldNormal)
{
    const float c1 = 0.429043;
    const float c2 = 0.511664;
    const float c3 = 0.743125;
    const float c4 = 0.886227;
    const float c5 = 0.247708;
    const float3 l00 = float3(0.871297, 0.875222, 0.864470);
    const float3 l1m1 = float3(0.175058, 0.245335, 0.312891);
    const float3 l10 = float3(0.034675, 0.036107, 0.037362);
    const float3 l11 = float3(-0.004629, -0.029448, -0.048028);
    const float3 l2m2 = float3(-0.120535, -0.121160, -0.117507);
    const float3 l2m1 = float3(0.003242, 0.003624, 0.007511);
    const float3 l20 = float3(-0.028667, -0.024926, -0.020998);
    const float3 l21 = float3(-0.077539, -0.086325, -0.091591);
    const float3 l22 = float3(-0.161784, -0.191783, 0.219152);
    float3 factor = c1 * l22 * (worldNormal.x * worldNormal.x - worldNormal.y * worldNormal.y)
	+ c3 * l20 * worldNormal.z * worldNormal.z
	+ c4 * l00
	- c5 * l20
	+ 2.0 * c1 * l2m2 * worldNormal.x * worldNormal.y
	+ 2.0 * c1 * l21 * worldNormal.x * worldNormal.z
	+ 2.0 * c1 * l2m1 * worldNormal.y * worldNormal.z
	+ 2.0 * c2 * l11 * worldNormal.x
	+ 2.0 * c2 * l1m1 * worldNormal.y
	+ 2.0 * c2 * l10 * worldNormal.z;
    return factor;
}
//---------------------------------------diffuse---------------------------------------------------------
float calcLambertDiffuseFactor(float nDotL)
{
    return nDotL;
}
float calcOrenNayarDiffuseFactor(float a, float b, float nDotL, float nDotV, float3 vertexToLightDirection, float3 vertexToCameraDirection, float3 worldNormal)
{
    float cos_tha_i = nDotL;
    float cos_tha_o = nDotV;
    float cos_beita = max(cos_tha_i, cos_tha_o);
    if (cos_beita == 0)
        return 0.0;
    float3 world_tangent = worldNormal + float3(1.0,1.0,1.0);
    float3 world_binormal = normalize(cross(worldNormal, world_tangent));
    world_tangent = cross(world_binormal, worldNormal);
    float3 mat_to_tangent_space_colume_0 = world_tangent;
    float3 mat_to_tangent_space_colume_1 = world_binormal;
    float3 mat_to_tangent_space_colume_2 = worldNormal;

    float3 v;
    v.x = dot(vertexToCameraDirection, mat_to_tangent_space_colume_0);
    v.y = dot(vertexToCameraDirection, mat_to_tangent_space_colume_1);
    v.z = 0.0;
    v = normalize(v);

    float3 l;
    l.x = dot(vertexToLightDirection, mat_to_tangent_space_colume_0);
    l.y = dot(vertexToLightDirection, mat_to_tangent_space_colume_1);
    l.z = 0.0;
    l = normalize(l);

    float cos_fai = saturate(dot(v, l));

    float cos_afa = min(cos_tha_i, cos_tha_o);
    float sin_afa_mul_tan_beita = sqrt((1 - cos_afa * cos_afa) * (1 - cos_beita * cos_beita)) / cos_beita;
    return a + b * cos_fai * sin_afa_mul_tan_beita;
}
float calcMinnaertDiffuseFactor(float nDotL, float nDotV, float roughness)
{
    return pow(nDotL * nDotV, roughness - 1);
}
float calcDiffuseFactor_Disney(float roughness, float nDotL, float nDotV, float vDotH)
{
    float fd90 = 0.5 + 2.0 * roughness * vDotH * vDotH;
    float pow_temp1 = (1 - nDotL) * (1 - nDotL) * (1 - nDotL) * (1 - nDotL) * (1 - nDotL);
    float pow_temp2 = (1 - nDotV) * (1 - nDotV) * (1 - nDotV) * (1 - nDotV) * (1 - nDotV);
    return (1.0 + (fd90 - 1.0) * pow_temp1) * (1.0 + (fd90 - 1.0) * pow_temp2) / PI;
}
//-----------------------------------------specular--------------------------------------------------------
float calcPhongSpecularFactor(float3 lightToVertexDirection, float3 worldNormal, float3 worldPosition, float3 vertexToCameraDirection)
{
    float3 reflect_dir = reflect(lightToVertexDirection, worldNormal);
    float specular_factor = saturate(dot(reflect_dir, vertexToCameraDirection));
    return specular_factor;
}
float calcBlinnPhongSpecularFactor(float nDotH, float specularExponent)
{
    float specular_factor = pow(nDotH, specularExponent);
    return specular_factor;
}
float calcMicrofacetSepcularBRDF_D_UE4(float roughnessPow4, float nDotH)
{
    float temp = nDotH * nDotH * (roughnessPow4 - 1.0) + 1.0;
    return roughnessPow4 / (PI * temp * temp);
}
float calcMicrofacetSepcularBRDF_D_CookTorrance(float roughnessPow2, float nDotH)
{
    float n_dot_h_pow_2 = nDotH * nDotH;
    return exp((n_dot_h_pow_2 - 1) / (n_dot_h_pow_2 * roughnessPow2)) / (roughnessPow2 * n_dot_h_pow_2 * n_dot_h_pow_2);
}
float calcMicrofacetSepcularBRDF_G_UE4(float roughness, float nDotV, float nDotL)
{
    float k = roughness + 1.0;
    k = k * k;
    k = k / 8.0;

    float g_v = nDotV / (nDotV * (1.0 - k) + k);

    float g_l = nDotL / (nDotL * (1.0 - k) + k);

    return g_v * g_l;
}
float calcMicrofacetSepcularBRDF_G_CookTorrance(float nDotH, float nDotV, float nDotL, float vDotH)
{
    return saturate(2 * nDotH / vDotH * min(nDotV, nDotL));
}
float calcMicrofacetSepcularBRDF_F_UE4(float vDotH)
{
    float f0 = 0.04;
    return f0 + (1.0 - f0) * pow(2.0, (-5.55473 * vDotH - 6.98316) * vDotH);
}
float calcMicrofacetSepcularBRDF_F_CookTorrance(float f0, float vDotH)
{
    float need_pow = 1.0 - vDotH;
    return f0 + (1.0 - f0) * need_pow * need_pow * need_pow * need_pow * need_pow;
}
float calcMicrofacetSepcularBRDF_UE4(float nDotH, float nDotV, float nDotL, float vDotH, float roughness)
{
    float d = calcMicrofacetSepcularBRDF_D_UE4(roughness * roughness * roughness * roughness, nDotH);
    float g = calcMicrofacetSepcularBRDF_G_UE4(roughness, nDotV, nDotL);
    float f = calcMicrofacetSepcularBRDF_F_UE4(vDotH);
    return d * f * g / (4 * nDotL * nDotV);
}
float calcMicrofacetSepcularBRDF_CookTorrance(float nDotH, float nDotV, float nDotL, float vDotH, float roughness, float fresnelF0)
{
    float d = calcMicrofacetSepcularBRDF_D_CookTorrance(roughness * roughness, nDotH);
    float g = calcMicrofacetSepcularBRDF_G_CookTorrance(nDotH, nDotV, nDotL, vDotH);
    float f = calcMicrofacetSepcularBRDF_F_CookTorrance(fresnelF0, vDotH);
    return d * f * g / (4 * nDotL * nDotV);
}
//return 1意味着无衰减，return 0意味着完全衰减
float calcFalloffFactor(float current, float begin, float reciprocalRange)
{
    float factor = saturate((current - begin) * reciprocalRange);
    return 1.0 - factor * factor;
}
float3 encodeNormal(float3 normal)
{
    return normal / getMaxComponment(normal);
}
float2 getQuadPosition(int vertexID)
{
    float2 ret;
    if (0 == vertexID)
        ret = float2(-1.0, 1.0);
    else if (1 == vertexID)
        ret = float2(1.0, 1.0);
    else if (2 == vertexID)
        ret = float2(-1.0, -1.0);
    else
        ret = float2(1.0, -1.0);
    return ret;
}