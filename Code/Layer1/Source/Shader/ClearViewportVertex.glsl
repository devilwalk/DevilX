#include "cbClearViewport.sl"
#include "Functions.sl"
void main()
{
    float depth = gClearDepth;
	gl_Position= float4(getQuadPosition(gl_VertexID), depth, 1.0);
}
