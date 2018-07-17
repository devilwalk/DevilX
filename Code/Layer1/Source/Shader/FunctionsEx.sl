#include "Functions.sl"
#include "cbCommon.sl"
float3 getCameraPosition()
{
	return float3(gViewMatrix[0].w,gViewMatrix[1].w,gViewMatrix[2].w);
}
float3 getCameraDirection()
{
	return float3(gViewMatrix[0].z,gViewMatrix[1].z,gViewMatrix[2].z);
}
float3 getCameraUp()
{
	return float3(gViewMatrix[0].y,gViewMatrix[1].y,gViewMatrix[2].y);
}
float3 getCameraRight()
{
	return float3(gViewMatrix[0].x,gViewMatrix[1].x,gViewMatrix[2].x);
}
float3 calcHemisphereAmbientFactor(float3 worldNormal)
{
    float3 factor = calcHemisphereAmbientFactor(-gSkyLightDirection, worldNormal);
	return lerp(gGroundColour,gSkyColour,factor);
}
