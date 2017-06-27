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
float3 calcHemisphereLightColour(float3 worldNormal)
{
	float factor=calcHemisphereLightFactor(-gSkyLightDirection,worldNormal);
	return lerp(gGroundColour,gSkyColour,float3(factor));
}
