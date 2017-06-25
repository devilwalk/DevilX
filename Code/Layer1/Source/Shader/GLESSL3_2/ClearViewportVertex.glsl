#include "Function.glsl"
cbuffer cbClearViewport
{
    float4 gClearColour0;
    float4 gClearColour1;
    float4 gClearColour2;
    float4 gClearColour3;
    float gClearDepth;
};
void main()
{
    float depth = gClearDepth;
    gl_Position = float4(getQuadPosition(gl_VertexID), depth, 1.0);
}
