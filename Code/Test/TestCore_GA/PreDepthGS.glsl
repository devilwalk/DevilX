struct SInputPS
{
	float4 mPositionWVP:SV_Position;
	//uint4 mTest0:TEST0;
	//uint4 mTest1:TEST1;
};

[maxvertexcount(3)]
void main(triangle SInputPS input[3],inout TriangleStream<SInputPS> output)
{
	output.Append(input[0]);
	output.Append(input[1]);
	output.Append(input[2]);
	output.RestartStrip();
}