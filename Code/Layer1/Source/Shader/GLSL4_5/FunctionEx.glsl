#include "Function.glsl"
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
