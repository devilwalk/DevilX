struct SInputPS
{
	float4 mPositionWVP:SV_Position;
	//uint4 mTest0:TEST0;
	//uint4 mTest1:TEST1;
};

struct SOutputPS
{
	float4 mBaseColour:SV_Target0;
};

void main(SInputPS input, out SOutputPS output)
{
	output.mBaseColour = 0.0;
}