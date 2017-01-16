#include "Function.hlsl"
cbuffer cbClearViewport
{
    float4 gClearColour : packoffset(c0);
    float gClearDepth : packoffset(c1);
};
#ifndef CLEAR_COLOUR
#define CLEAR_COLOUR 0
#endif
#ifndef CLEAR_DEPTH
#define CLEAR_DEPTH 0
#endif
void vsMain
(uint vertexID : SV_VertexID
, out float4 outPosition : SV_Position
#if CLEAR_COLOUR
, out float4 outColour : COLOR
#endif
)
{
#if CLEAR_DEPTH
    float depth = gClearDepth;
#else
    float depth = 1.0;
#endif
    outPosition = float4(getQuadPosition(vertexID), depth, 1.0);
#if CLEAR_COLOUR
    outColour = gClearColour;
#endif
}
void psMain
(float4 position : SV_Position
#if CLEAR_COLOUR
, float4 colour : COLOR
#endif
, out float4 outColour : SV_Target
)
{
#if CLEAR_COLOUR
    outColour = colour;
#else
    outColour = 0.0;
#endif
}