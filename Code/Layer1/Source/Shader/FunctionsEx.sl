#include "Functions.sl"
#include "cbCommon.sl"
float3 getCameraPosition()
{
	return getCameraPosition(gViewMatrix);
}
float3 getCameraDirection()
{
	return getCameraDirection(gViewMatrix);
}
float3 getCameraUp()
{
	return getCameraUp(gViewMatrix);
}
float3 getCameraRight()
{
	return getCameraRight(gViewMatrix);
}
float3 calcHemisphereAmbientFactor(float3 worldNormal)
{
	float3 factor=calcHemisphereLightFactor(-gSkyLightDirection,worldNormal);
	return lerp(gGroundColour,gSkyColour,factor);
}
