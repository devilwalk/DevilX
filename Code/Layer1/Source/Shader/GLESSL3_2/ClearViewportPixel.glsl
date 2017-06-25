#include "Function.glsl"
cbuffer cbClearViewport
{
    float4 gClearColour0;
    float4 gClearColour1;
    float4 gClearColour2;
    float4 gClearColour3;
    float gClearDepth;
};
layout(location=0) out float4 outColour0;
layout(location=1) out float4 outColour1;
layout(location=2) out float4 outColour2;
layout(location=3) out float4 outColour3;
void main()
{
    outColour0 = gClearColour0;
    outColour1 = gClearColour1;
    outColour2 = gClearColour2;
    outColour3 = gClearColour3;
}