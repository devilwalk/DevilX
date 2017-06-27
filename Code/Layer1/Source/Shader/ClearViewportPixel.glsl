#include "cbClearViewport.sl"
#include "Functions.sl"
layout(location=0) out float4 outColour0;
layout(location=1) out float4 outColour1;
layout(location=2) out float4 outColour2;
layout(location=3) out float4 outColour3;
#if GLSL_VERSION>400
layout(location=4) out float4 outColour4;
layout(location=5) out float4 outColour5;
layout(location=6) out float4 outColour6;
layout(location=7) out float4 outColour7;
#endif
void main()
{
    outColour0 = gClearColour0;
    outColour1 = gClearColour1;
    outColour2 = gClearColour2;
    outColour3 = gClearColour3;
#if GLSL_VERSION>400
    outColour4 = gClearColour4;
    outColour5 = gClearColour5;
    outColour6 = gClearColour6;
    outColour7 = gClearColour7;
#endif
}