#include "Function.glsl"
cbuffer cbClearViewport
{
    float4 gClearColour0;
    float4 gClearColour1;
    float4 gClearColour2;
    float4 gClearColour3;
    float4 gClearColour4;
    float4 gClearColour5;
    float4 gClearColour6;
    float4 gClearColour7;
    float gClearDepth;
};
layout(location=0) out float4 outColour0;
layout(location=1) out float4 outColour1;
layout(location=2) out float4 outColour2;
layout(location=3) out float4 outColour3;
layout(location=4) out float4 outColour4;
layout(location=5) out float4 outColour5;
layout(location=6) out float4 outColour6;
layout(location=7) out float4 outColour7;
void main()
{
    outColour0 = gClearColour0;
    outColour1 = gClearColour1;
    outColour2 = gClearColour2;
    outColour3 = gClearColour3;
    outColour4 = gClearColour4;
    outColour5 = gClearColour5;
    outColour6 = gClearColour6;
    outColour7 = gClearColour7;
}