#include "Function.glsl"
cbuffer cbClearViewport
{
    float4 gClearColour0 : packoffset(c0);
    float4 gClearColour1 : packoffset(c1);
    float4 gClearColour2 : packoffset(c2);
    float4 gClearColour3 : packoffset(c3);
    float4 gClearColour4 : packoffset(c4);
    float4 gClearColour5 : packoffset(c5);
    float4 gClearColour6 : packoffset(c6);
    float4 gClearColour7 : packoffset(c7);
    float gClearDepth : packoffset(c8);
};
void main()
{
    float depth = gClearDepth;
    gl_Position = float4(getQuadPosition(gl_VertexID), depth, 1.0);
}
