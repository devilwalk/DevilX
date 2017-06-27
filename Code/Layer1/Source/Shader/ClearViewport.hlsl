#include "Functions.sl"
#include "cbClearViewport.sl"
void vsMain(uint vertexID : SV_VertexID
, out float4 outPosition : SV_Position
)
{
    float depth = gClearDepth;
    outPosition = float4(getQuadPosition(vertexID), depth, 1.0);
}
void psMain(float4 position : SV_Position
, out float4 outColour0 : SV_Target0
, out float4 outColour1 : SV_Target1
, out float4 outColour2 : SV_Target2
, out float4 outColour3 : SV_Target3
, out float4 outColour4 : SV_Target4
, out float4 outColour5 : SV_Target5
, out float4 outColour6 : SV_Target6
, out float4 outColour7 : SV_Target7
)
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